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

void _GFG::_GFG_InitMakeGrid(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, WORD a_portAddr, CGridCtrl *ap_grid)
{
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	/* 2�� �����ͷ� �� ���...
		Sheet **ppSheet = NULL;
		ppSheet = &pExcel->m_pDU_Default_1;
		(*ppSheet)->getMerge(5, 2, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last
	*/
	Sheet *pSheet = NULL;
	pSheet = mainDlg->mp_Libxl->GetSheet(a_portAddr);

	// Grid Setting
	bool bMerge = false;
	int mergeCol_start = 0;
	int mergeCol_finish = 0;

	a_ColLast++;

	for (int row = a_RowFirst; row <= a_RowLast; row++) {
		for (int col = a_ColFirst; col <= a_ColLast; col++) {
			if (pSheet != NULL) // ��� ���������� �ϼ����� �ʾƼ� ��� �� ������ �ɾ� ��.
				bMerge = pSheet->getMerge(row, col, 0, 0, 0, 0);	

			// ������ �Ǿ��ٸ�...
			if (bMerge) {
				if (mergeCol_finish == 0) {
					mergeCol_start = col - 1;
					mergeCol_finish = col - 2;
				}
				mergeCol_finish++;
			}
			// ������ �ȵǾ� �ִٸ�...
			else {
				// �Ϲ� ��Ʈ ���� 
				if (0 == mergeCol_finish) {}
				// ���յ� ũ�� ��ŭ ����.
				else {
					int t_row = row - 3;
					ap_grid->MergeCells(CCellRange(t_row, mergeCol_start, t_row, mergeCol_finish));

					mergeCol_start = 0;
					mergeCol_finish = 0;
				}
			}
		}
	}

	pSheet = NULL;
	mainDlg = NULL;
}
//--------------------------------------------------------------------------------------------

void _GFG::_GFG_SetWordFormatCell(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, WORD a_portAddr, CGridCtrl *ap_grid)
{
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	/* 2�� �����ͷ� �� ���...
		Sheet **ppSheet = NULL;
		ppSheet = &pExcel->m_pDU_Default_1;
		(*ppSheet)->getMerge(5, 2, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last
	*/
	Sheet *pSheet = NULL;
	pSheet = mainDlg->mp_Libxl->GetSheet(a_portAddr);

	// Draw Word Format 
	bool bMerge = false;
	int mergeCount = 0;

	a_ColLast++;

	for (int row = a_RowFirst; row <= a_RowLast; row++) {
		for (int col = a_ColFirst; col <= a_ColLast; col++) {
			if (pSheet != NULL) // ��� ���������� �ϼ����� �ʾƼ� ��� �� ������ �ɾ� ��.
				bMerge = pSheet->getMerge(row, col, 0, 0, 0, 0);

			// ������ �Ǿ��ٸ�...
			if (bMerge) {
				mergeCount++;
			}

			// Check Word Fomat
			if (mergeCount == 16) {
				// ���� ���� ����.
				int t_row_first = a_RowFirst, t_row_last = a_RowLast;
				int t_col_first = a_ColFirst, t_col_last = a_ColLast - 1;

				pSheet->getMerge(row, 2, &t_row_first, &t_row_last, &t_col_first, &t_col_last); // _row, _col, &row_first, &row_last, &col_first, &col_last		
				// ó�� ��� ������ ���� ���ϴ� ������ ����Ʈ �����̸� �� ����(t_row_first, t_row_last)�� ���� ���� ������ ���� �����̸� �� ������ ���� �ٸ���.
				if (t_row_first != t_row_last) {
					int t_row_f = t_row_first - 3;
					int t_row_l = t_row_last - 3;
					ap_grid->MergeCells(CCellRange(t_row_f, 1, t_row_l, 8));
				}
				mergeCount = 0;
			}
		}
	}

	pSheet = NULL;
	mainDlg = NULL;
}
//--------------------------------------------------------------------------------------------

void _GFG::_GFG_SetTextGrid(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, CGridCtrl *ap_grid)
{
	/*for (int row = a_RowFirst; row <= a_RowLast; row++) {
		for (int col = a_ColFirst; col <= a_ColLast; col++) {
			ap_grid->SetItemText(row, 9 - col, pExcel->GetDuDefaultValue(row - 2, col - 1, a_flag));
		}
	}*/
}
//--------------------------------------------------------------------------------------------

void _GFG::_GFG_GetBitDataFormSM(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid)
{
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

/* 2�� �����ͷ� �� ���...
	Sheet **ppSheet = NULL;
	ppSheet = &pExcel->m_pDU_Default_1;
	(*ppSheet)->getMerge(5, 2, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last
*/
	Sheet *pSheet = NULL;
	pSheet = mainDlg->mp_Libxl->GetSheet(a_portAddr);

	bool bMerge = false;

	a_ColLast++;

	for (int row = a_RowFirst; row <= a_RowLast; row++) {
		WORD smData = mainDlg->GetWordDataFromSM(a_portAddr, a_node, (row - 5) / 2); // (WORD a_PortAddr, BYTE a_Node, BYTE a_Word)

		for (int col = a_ColFirst; col <= a_ColLast; col++) {
			if (pSheet != NULL) // ��� ���������� �ϼ����� �ʾƼ� ��� �� ������ �ɾ� ��.
				bMerge = pSheet->getMerge(row, col, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last	

			// ������ �ȵǾ� �ִٸ�...
			if (!bMerge && col < 10) {
				// ��Ʈ üũ.
				BYTE bitPos = 7 - (col - 2); // 2 ~ 10

				BYTE rowPos = row - 3; // 5 ~ 36
				if (rowPos % 2 == 0) bitPos += 8;

				BYTE colPos = col - 1;

				// �׸��忡 ���� ����.
				if (IsBitCheck16(smData, bitPos)) {
					ap_grid->SetItemBkColour(rowPos, colPos, RCLICK_RGB);
				}
			}
		}
	}

	pSheet = NULL;
	mainDlg = NULL;
}
//--------------------------------------------------------------------------------------------

void _GFG::_GFG_GetMoreThanTwoBitsOfDataFormSM(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid)
{
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	Sheet *pSheet = NULL;
	pSheet = mainDlg->mp_Libxl->GetSheet(a_portAddr);

	bool bMerge = false;
	bool oldMerge = false;

	int mergeCount = 0;
	int startRow = 0, startCol = 0;
	int row = a_RowFirst;

	while (row <= a_RowLast) {
		WORD smData = mainDlg->GetWordDataFromSM(a_portAddr, a_node, (row - 5) / 2); // (WORD a_PortAddr, BYTE a_Node, BYTE a_Word)

		for (int col = a_ColFirst; col <= a_ColLast + 1; col++) {
			bMerge = pSheet->getMerge(row, col, 0, 0, 0, 0); 	

			// ������ �Ǿ��ٸ�...
			if (bMerge) {
				oldMerge = true;
				mergeCount++;

				if (mergeCount == 1) {
					startRow = row - 3;
					startCol = col - 1;
				}
			}

			if (oldMerge && !bMerge) {
				CString gridText;

				if (mergeCount == 16) {
					// ���� ���� ����.
					int t_row_first = a_RowFirst, t_row_last = a_RowLast;
					int t_col_first = a_ColFirst, t_col_last = a_ColLast - 1;

					pSheet->getMerge(row, 2, &t_row_first, &t_row_last, &t_col_first, &t_col_last); // _row, _col, &row_first, &row_last, &col_first, &col_last		
					// ó�� ��� ������ ���� ���ϴ� ������ ����Ʈ �����̸� �� ����(t_row_first, t_row_last)�� ���� ���� ������ ���� �����̸� �� ������ ���� �ٸ���.
					if (t_row_first != t_row_last) {
						// ����
						if (0 != smData) {
							ap_grid->SetItemBkColour(startRow, startCol, PINK_COLOR);
						}
						gridText.Format(L"%s >> [%04X] [%d]", GetTextFormExcel(startRow, startCol, pSheet), smData, smData);
						ap_grid->SetItemText(startRow, startCol, gridText);
					}
					else {
						// ����Ʈ
						unsigned char t_HByte = smData >> 8;
						unsigned char t_LByte = smData & 0xFF;

						if (0 != t_HByte)
							ap_grid->SetItemBkColour(startRow, startCol, LIGHTYELLOW_COLOR);
						if (0 != t_LByte)
							ap_grid->SetItemBkColour(startRow + 1, startCol, LIGHTYELLOW_COLOR);

						gridText.Format(L"%s >> [%02X] [%d]", GetTextFormExcel(startRow, startCol, pSheet), t_HByte, t_HByte);
						ap_grid->SetItemText(startRow, startCol, gridText);
						
						gridText.Format(L"%s >> [%02X] [%d]", GetTextFormExcel(startRow + 1, startCol, pSheet), t_LByte, t_LByte);
						ap_grid->SetItemText(startRow + 1, startCol, gridText);
					}

					oldMerge = false;
					mergeCount = 0;
				}
				else if (mergeCount >= 2 && mergeCount <= 7){
					BYTE t_smData = mainDlg->GetByteDataFromSM(a_portAddr, a_node, row - 5);
					char t_bitPos = 8 - startCol;
					
					int move = t_bitPos - mergeCount + 1;
					int t_datacheck = ((int)pow(2, mergeCount)-1) & (t_smData >> move);
					
					if(0 != t_datacheck)
						ap_grid->SetItemBkColour(startRow, startCol, AQUA_COLOR);

					gridText.Format(L"%s >> [%02X] [%d]", GetTextFormExcel(startRow, startCol, pSheet), t_datacheck, t_datacheck);
					ap_grid->SetItemText(startRow, startCol, gridText);

					oldMerge = false;
					mergeCount = 0;
				}
			}
		}
		row++;
	}

	pSheet = NULL;
	mainDlg = NULL;
}
//--------------------------------------------------------------------------------------------

// ���߿� ���� �� �ڵ���.
void _GFG::_GFG_GetBitDataFormSMTest(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid)
{
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	/* 2�� �����ͷ� �� ���...
		Sheet **ppSheet = NULL;
		ppSheet = &pExcel->m_pDU_Default_1;
		(*ppSheet)->getMerge(5, 2, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last
	*/
	Sheet *pSheet = NULL;
	pSheet = mainDlg->mp_Libxl->GetSheet(a_portAddr);

	bool bMerge = false;

	a_ColLast++;

	for (int row = a_RowFirst; row <= a_RowLast; row++) {
		WORD smData = mainDlg->GetWordDataFromSM(a_portAddr, a_node, (row - 5) / 2); // (WORD a_PortAddr, BYTE a_Node, BYTE a_Word)

		for (int col = a_ColFirst; col <= a_ColLast; col++) {

			// ������ �ȵǾ� �ִٸ�...
			if (!bMerge && col < 10) {
				// ��Ʈ üũ.
				BYTE bitPos = 7 - (col - 2); // 2 ~ 10

				BYTE rowPos = row - 3; // 5 ~ 36
				if (rowPos % 2 == 0) bitPos += 8;

				BYTE colPos = col - 1;

				// �׸��忡 ���� ����.
				if (IsBitCheck16(smData, bitPos)) {
					ap_grid->SetItemBkColour(rowPos, colPos, RCLICK_RGB);
				}
			}
		}
	}

	pSheet = NULL;
	mainDlg = NULL;
}
//--------------------------------------------------------------------------------------------

void _GFG::_GFG_SetMergeData(int a_GridRow, int a_GridColumn, WORD a_SetData, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid)
{
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	Sheet *pSheet = NULL;
	pSheet = mainDlg->mp_Libxl->GetSheet(a_portAddr);

	int mergeCount = _GFG_GetMergeCheck(a_GridRow, a_GridColumn, a_portAddr);

	CString gridText;
	BYTE wordPos = (a_GridRow - 2) / 2;

	if (16 == mergeCount) {			
		//����
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
		bool checkUpDonw = a_GridRow % 2; // 0�̸� ����(false), 1�̸� ����(true)

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
				
		bool checkUpDonw = a_GridRow % 2; // 0�̸� ���� 1�̸� ����
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
	pSheet = mainDlg->mp_Libxl->GetSheet(a_portAddr);

	int row_first = 5, row_last = 36;
	int col_first = 2, col_last = 9;

	bool bMerge = false;
	int mergeCount = 0;

	col_last++;

	for (int col = a_Column + 1; col <= col_last; col++) {
		bMerge = pSheet->getMerge(a_Row + 3, col, 0, 0, 0, 0);

		// ������ �Ǿ��ٸ�...
		if (bMerge) mergeCount++;
		else {
			pSheet = NULL;
			return mergeCount;
		}

		// Check Word Fomat
		if (mergeCount == 8) {
			// ¦���� ������ ���� ������ �а� Ȧ���� ������ Ŭ���� ��ġ�� ���� ���� ���� ���´� üũ ���� �ʴ´�.
			// �׷��� Ŭ���� ���� ����Ʈ ���� ���� ���� ���� ���� �� �� �ִ�.
			unsigned char rowPos = a_Row % 2;

			col_last--; // ���� ������ ���߱� ���ؼ� �ٽ� �ϳ� ���ҽ�Ų��. 

			pSheet->getMerge(a_Row + 4, 2, &row_first, &row_last, &col_first, &col_last); // +4�� �ϴ� ������ Ŭ���� ���� �Ʒ� �࿡ ��ġ�� ������ �о� ���� �����̴�.
			// ó�� ��� ������ ���� ���ϴ� ������ ����Ʈ �����̸� �� ����(t_row_first, t_row_last)�� ���� ���� ������ ���� �����̸� �� ������ ���� �ٸ���.
			if ((row_first != row_last) && (rowPos == 0)) {
				return 16; // ���� ����
			}
			else {
				pSheet = NULL;
				return mergeCount;
			}
		}
	}

	// ���ǿ� ���� �ʰ� �����ߴٸ� �Ʒ� �ڵ带 Ÿ�Ե�.
	pSheet = NULL;
	return -1;	
}
//--------------------------------------------------------------------------------------------