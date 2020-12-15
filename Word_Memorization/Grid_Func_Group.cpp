#include "pch.h"

#include "Grid_Func_Group.h"
#include "DefineOfDev_J.h"

#include "Word_MemorizationDlg.h"
#include "_CExcelLib.h"

#include <math.h>

//--------------------------------------------------------------------------------------------

void _GFG::_GFG_InitItemBkColor(int a_rowLast, int a_colLast, CGridCtrl *ap_grid)
{
	for (int row = 2; row <= a_rowLast; row++) {
		for (int col = 1; col <= a_colLast; col++) {
			ap_grid->SetItemBkColour(row, col, WHITE_RGB);
		}
	}
}
//--------------------------------------------------------------------------------------------

void _GFG::_GFG_InitMakeGrid(unsigned short a_fcode, WORD a_portAddr, WORD a_node, CGridCtrl *ap_grid)
{
	/* 2중 포인터로 할 경우...
		Sheet **ppSheet = NULL;
		ppSheet = &pExcel->m_pDU_Default_1;
		(*ppSheet)->getMerge(5, 2, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last
	*/
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();
	_CExcelLib *p_ExcelLib = (_CExcelLib *)mainDlg->mp_Libxl;
	Sheet *pSheet = NULL;
	pSheet = mainDlg->mp_Libxl->sheetMap.find(a_portAddr)->second;

	if (pSheet == NULL) {
		AfxMessageBox(L"Do not found Excel sheet (_GFG_InitMakeGrid() - m_InitSheetMap())");
		return;
	}

	// Grid Setting	
	int mergeCol_start = 0;
	int mergeCol_finish = 0;
	unsigned short rowLast = (2 << a_fcode) + 5; // 엑셀 읽어오는 시작 지점이 5이기 때문에 +5를 함.
	bool bMerge = false;

	CString gridBuf;

	for (int row = 5; row < rowLast; NULL) {
		int gridRow = row - 3;
		int mergeSize = (int)pSheet->readNum(row, 10);

		int mvbIndex = binarySearch(p_ExcelLib->mvb_Addr, 120, a_portAddr);
		mvbIndex += p_ExcelLib->m_totalNodeCnt * a_node;
		
		if (mergeSize) { // 1바이트 이상 병합이된 경우.
			// 공유 메모리에서 데이터 가져옴.
			int smData = 0;
			memcpy(&smData, &mainDlg->m_pData->data[mvbIndex][gridRow - 2], mergeSize);

			// ((BYTE *)&smData)[0] 0번째 부터 한 바이트 씩 데이터가 저장되는데 4바이트(int) 자료형에 
			// 넣기 때문에 1바이트짜리 데이터를 현시하려면 32만큼 오른쪽 시프트를 해야한다.
			int rShift = 8 << (4 - mergeSize);
			smData = smData >> rShift;

			// 엑셀 10열에 표기한 숫자 만큼 병합. (more than 1 byte)
			ap_grid->MergeCells(CCellRange(gridRow, 1, gridRow + mergeSize - 1, 8));

			// 값이 0이면 흰색, 값이 0이 아니라면 연한 노랑색.
			if (smData) ap_grid->SetItemBkColour(gridRow, 1, ORANGE_COLOR);
			else ap_grid->SetItemBkColour(gridRow, 1, WHITE_RGB);
						
			// 엑셀에서 가져온 문자열을 그리드 컨트롤에 세팅.
			gridBuf.Format(L"%s >> [0x%04X][%d]", pSheet->readStr(row, 2), smData, smData);
			ap_grid->SetItemText(gridRow, 1, gridBuf);

			// 다음 행으로 넘어감.
			row += mergeSize;							
		}
		else { 
			// 공유 메모리에서 데이터 가져옴.
			unsigned char smData = 0;
			memcpy(&smData, &mainDlg->m_pData->data[mvbIndex][gridRow - 2], 1);

			int mergeCnt;
			// 병합된 사이즈 만큼 다음 col 값 증가.
			for (int col = 2; col < 10; col += mergeCnt) {
				int gridCol = col - 1;
				mergeCnt = 0;
				
				// 병합된 사이즈 측정.
				while (pSheet->readBlank(row, col + 1 + mergeCnt, NULL)) {
					mergeCnt++;					
				}
					
				// 그리드 컨트롤 병합.
				ap_grid->MergeCells(CCellRange(gridRow, gridCol, gridRow, gridCol + mergeCnt));

				// 병합이 되지 않은 경우.				
				if (0 == mergeCnt) {					
					BYTE rShift = 9 - col;
					// 값이 0이면 흰색, 값이 0이 아니라면 연한 노랑색.					
					if ((smData >> rShift) & 0x01)
						ap_grid->SetItemBkColour(gridRow, gridCol, RCLICK_RGB);
					else
						ap_grid->SetItemBkColour(gridRow, gridCol, WHITE_RGB);	

					// 엑셀에서 가져온 문자열을 그리드 컨트롤에 세팅.
					ap_grid->SetItemText(gridRow, gridCol, pSheet->readStr(row, col));
				}
				// 병합된 경우.
				else {
					BYTE _rShift = 9 - (col + mergeCnt);//9 - col + mergeCnt;
					BYTE bitSet = 0;

					for (int i = 0; i <= mergeCnt; i++) {
						bitSet = bitSet | (1 << i);
					}

					BYTE data = smData >> _rShift;
					data &= bitSet;
					if (data)
						ap_grid->SetItemBkColour(gridRow, gridCol, LIGHTYELLOW_COLOR);
					else 
						ap_grid->SetItemBkColour(gridRow, gridCol, WHITE_RGB);					

					// 엑셀에서 가져온 문자열을 그리드 컨트롤에 세팅.
					CString str;
					str.Format(L"%s >> [0x%02X][%d]", pSheet->readStr(row, col), data, data);
					ap_grid->SetItemText(gridRow, gridCol, str);
				}

				// col 증가.
				col++;								
			}
			row++;
		}		
	}	
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// 나중에 삭제 할 코드임.
void _GFG::_GFG_GetBitDataFormSMTest(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid)
{
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	/* 2중 포인터로 할 경우...
		Sheet **ppSheet = NULL;
		ppSheet = &pExcel->m_pDU_Default_1;
		(*ppSheet)->getMerge(5, 2, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last
	*/
	
	bool bMerge = false;

	a_ColLast++;

	for (int row = a_RowFirst; row <= a_RowLast; row++) {
		WORD smData = mainDlg->GetWordDataFromSM(a_portAddr, a_node, (row - 5) / 2); // (WORD a_PortAddr, BYTE a_Node, BYTE a_Word)

		for (int col = a_ColFirst; col <= a_ColLast; col++) {

			// 병합이 안되어 있다면...
			if (!bMerge && col < 10) {
				// 비트 체크.
				BYTE bitPos = 7 - (col - 2); // 2 ~ 10

				BYTE rowPos = row - 3; // 5 ~ 36
				if (rowPos % 2 == 0) bitPos += 8;

				BYTE colPos = col - 1;

				// 그리드에 색상 적용.
				if (IsBitCheck16(smData, bitPos)) {
					ap_grid->SetItemBkColour(rowPos, colPos, RCLICK_RGB);
				}
			}
		}
	}	
}
//--------------------------------------------------------------------------------------------

void _GFG::_GFG_SetMergeData(int a_GridRow, int a_GridColumn, WORD a_SetData, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid)
{
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	Sheet *pSheet = NULL;
	pSheet = mainDlg->mp_Libxl->sheetMap.find(a_portAddr)->second;

	int mergeCount = _GFG_GetMergeCheck(a_GridRow, a_GridColumn, a_portAddr);

	CString gridText;
	BYTE wordPos = (a_GridRow - 2) / 2;

	if (16 == mergeCount) {			
		//워드
		if (0 != a_SetData)
			ap_grid->SetItemBkColour(a_GridRow, a_GridColumn, PINK_COLOR);
		else
			ap_grid->SetItemBkColour(a_GridRow, a_GridColumn, WHITE_RGB);
		
		mainDlg->Set16DataToSM(a_portAddr, a_node, wordPos, a_SetData);

		gridText.Format(L"%s >> [%04X] [%d]", GetTextFormExcel(a_GridRow, a_GridColumn, pSheet), a_SetData, a_SetData);
		ap_grid->SetItemText(a_GridRow, a_GridColumn, gridText);
		
		//ap_grid->RedrawCell(a_GridRow, a_GridColumn);
	}
	else if (8 == mergeCount) {
		unsigned char data = (unsigned char)a_SetData;		
		bool checkUpDonw = a_GridRow % 2; // 0이면 상위(false), 1이면 하위(true)

		if (0 != data)		
			ap_grid->SetItemBkColour(a_GridRow, a_GridColumn, LIGHTYELLOW_COLOR);
		else
			ap_grid->SetItemBkColour(a_GridRow, a_GridColumn, WHITE_RGB);
		
		mainDlg->Set08DataToSM(a_portAddr, a_node, wordPos, checkUpDonw, data);

		gridText.Format(L"%s >> [%02X] [%d]", GetTextFormExcel(a_GridRow, a_GridColumn, pSheet), data, data);
		ap_grid->SetItemText(a_GridRow, a_GridColumn, gridText);				
	}
	else if (mergeCount >= 2 && mergeCount <= 7) {
		BYTE smData = mainDlg->GetByteDataFromSM(a_portAddr, a_node, a_GridRow - 2);
		unsigned char data = (unsigned char)a_SetData;

		if (mergeCount == 2 && data >= 4) {
			data = 3;
		}
		else if (mergeCount == 3 && data >= 8) {
			data = 7;
		}
		else if (mergeCount == 4 && data >= 16) {
			data = 15;
		}
		else if (mergeCount == 5 && data >= 32) {
			data = 31;
		}
		else if (mergeCount == 6 && data >= 64) {
			data = 63;
		}
		else if (mergeCount == 7 && data >= 128) {
			data = 127;
		}
				
		bool checkUpDonw = a_GridRow % 2; // 0이면 상위 1이면 하위
		char colPos = 8 - a_GridColumn;

		unsigned char move = colPos - mergeCount + 1;

		unsigned char headData = smData >> (colPos + move);
		unsigned char bodyData = data;
		unsigned char tailData = smData & ((int)pow(2, move) - 1);

		smData = (headData << (colPos + move)) | (bodyData << move) | tailData;
				
		if (0 != data)
			ap_grid->SetItemBkColour(a_GridRow, a_GridColumn, AQUA_COLOR);
		else
			ap_grid->SetItemBkColour(a_GridRow, a_GridColumn, WHITE_RGB);

		mainDlg->Set08DataToSM(a_portAddr, a_node, wordPos, checkUpDonw, smData);

		gridText.Format(L"%s >> [%02X] [%d]", GetTextFormExcel(a_GridRow, a_GridColumn, pSheet), data, data);
		ap_grid->SetItemText(a_GridRow, a_GridColumn, gridText);
	}
	
	ap_grid->RedrawCell(a_GridRow, a_GridColumn);

	pSheet = NULL;
	mainDlg = NULL;
}
//--------------------------------------------------------------------------------------------

WORD _GFG::_GFG_GetMergeCheck(int a_Row, int a_Column, WORD a_portAddr)
{
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	Sheet *pSheet = NULL;
	pSheet = mainDlg->mp_Libxl->sheetMap.find(a_portAddr)->second;

	int row_first = 5, row_last = 36;
	int col_first = 2, col_last = 9;

	bool bMerge = false;
	int mergeCount = 0;

	col_last++;

	for (int col = a_Column + 1; col <= col_last; col++) {
		bMerge = pSheet->getMerge(a_Row + 3, col, 0, 0, 0, 0);

		// 병합이 되었다면...
		if (bMerge) mergeCount++;
		else {
			pSheet = NULL;
			return mergeCount;
		}

		// Check Word Fomat
		if (mergeCount == 8) {
			// 짝수가 나오면 워드 단위로 읽고 홀수가 나오면 클릭한 위치의 다음 행의 병합 상태는 체크 하지 않는다.
			// 그래야 클릭한 셀이 바이트 단위 인지 워드 단위 인지 알 수 있다.
			unsigned char rowPos = a_Row % 2;

			col_last--; // 엑셀 범위를 맞추기 위해서 다시 하나 감소시킨다. 

			pSheet->getMerge(a_Row + 4, 2, &row_first, &row_last, &col_first, &col_last); // +4를 하는 이유는 클릭한 행의 아래 행에 위치한 엑셀을 읽어 오기 위함이다.
			// 처음 행과 마지막 행을 비교하는 이유는 바이트 형식이면 두 변수(t_row_first, t_row_last)의 값이 같게 되지만 워드 형식이면 두 변수의 값이 다르다.
			if ((row_first != row_last) && (rowPos == 0)) {
				return 16; // 워드 포멧
			}
			else {
				pSheet = NULL;
				return mergeCount;
			}
		}
	}

	// 조건에 맞지 않게 동작했다면 아래 코드를 타게됨.
	pSheet = NULL;
	return -1;	
}
//--------------------------------------------------------------------------------------------