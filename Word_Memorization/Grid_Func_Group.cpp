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

	/* 2중 포인터로 할 경우...
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
			if (pSheet != NULL) // 모든 프로토콜이 완성되지 않아서 잠시 이 조건을 걸어 줌.
				bMerge = pSheet->getMerge(row, col, 0, 0, 0, 0);	

			// 병합이 되었다면...
			if (bMerge) {
				if (mergeCol_finish == 0) {
					mergeCol_start = col - 1;
					mergeCol_finish = col - 2;
				}
				mergeCol_finish++;
			}
			// 병합이 안되어 있다면...
			else {
				// 일반 비트 형식 
				if (0 == mergeCol_finish) {}
				// 병합된 크기 만큼 병합.
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

	/* 2중 포인터로 할 경우...
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
			if (pSheet != NULL) // 모든 프로토콜이 완성되지 않아서 잠시 이 조건을 걸어 줌.
				bMerge = pSheet->getMerge(row, col, 0, 0, 0, 0);

			// 병합이 되었다면...
			if (bMerge) {
				mergeCount++;
			}

			// Check Word Fomat
			if (mergeCount == 16) {
				// 엑셀 범위 세팅.
				int t_row_first = a_RowFirst, t_row_last = a_RowLast;
				int t_col_first = a_ColFirst, t_col_last = a_ColLast - 1;

				pSheet->getMerge(row, 2, &t_row_first, &t_row_last, &t_col_first, &t_col_last); // _row, _col, &row_first, &row_last, &col_first, &col_last		
				// 처음 행과 마지막 행을 비교하는 이유는 바이트 형식이면 두 변수(t_row_first, t_row_last)의 값이 같게 되지만 워드 형식이면 두 변수의 값이 다르다.
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

/* 2중 포인터로 할 경우...
	Sheet **ppSheet = NULL;
	ppSheet = &pExcel->m_pDU_Default_1;
	(*ppSheet)->getMerge(5, 2, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last
*/
	Sheet *pSheet = NULL;
	pSheet = mainDlg->mp_Libxl->GetSheet(a_portAddr);

	bool bMerge = false;

	a_ColLast++;

	for (int row = a_RowFirst; row <= a_RowLast; row++) {
		WORD smData = mainDlg->GetDataFromSM(a_portAddr, a_node, (row - 5) / 2); // (WORD a_PortAddr, BYTE a_Node, BYTE a_Word)

		for (int col = a_ColFirst; col <= a_ColLast; col++) {
			if (pSheet != NULL) // 모든 프로토콜이 완성되지 않아서 잠시 이 조건을 걸어 줌.
				bMerge = pSheet->getMerge(row, col, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last	

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
		WORD smData = mainDlg->GetDataFromSM(a_portAddr, a_node, (row - 5) / 2); // (WORD a_PortAddr, BYTE a_Node, BYTE a_Word)

		for (int col = a_ColFirst; col <= a_ColLast + 1; col++) {
			bMerge = pSheet->getMerge(row, col, 0, 0, 0, 0); 	

			// 병합이 되었다면...
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
					// 엑셀 범위 세팅.
					int t_row_first = a_RowFirst, t_row_last = a_RowLast;
					int t_col_first = a_ColFirst, t_col_last = a_ColLast - 1;

					pSheet->getMerge(row, 2, &t_row_first, &t_row_last, &t_col_first, &t_col_last); // _row, _col, &row_first, &row_last, &col_first, &col_last		
					// 처음 행과 마지막 행을 비교하는 이유는 바이트 형식이면 두 변수(t_row_first, t_row_last)의 값이 같게 되지만 워드 형식이면 두 변수의 값이 다르다.
					if (t_row_first != t_row_last) {
						// 워드
						if (0 != smData) {
							ap_grid->SetItemBkColour(startRow, startCol, PINK_COLOR);
						}
						gridText.Format(L"%s >> [%04X] [%d]", GetTextFormExcel(startRow, startCol, pSheet), smData, smData);
						ap_grid->SetItemText(startRow, startCol, gridText);
					}
					else {
						// 바이트
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
					int t_dataCheck = ((int)pow(2, mergeCount)-1) & (t_smData >> move);
					
					if(0 != t_dataCheck)
						ap_grid->SetItemBkColour(startRow, startCol, AQUA_COLOR);

					gridText.Format(L"%s >> [%02X] [%d]", GetTextFormExcel(startRow, startCol, pSheet), t_dataCheck, t_dataCheck);
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

// 나중에 삭제 할 코드임.
void _GFG::_GFG_GetBitDataFormSMTest(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid)
{
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	/* 2중 포인터로 할 경우...
		Sheet **ppSheet = NULL;
		ppSheet = &pExcel->m_pDU_Default_1;
		(*ppSheet)->getMerge(5, 2, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last
	*/
	Sheet *pSheet = NULL;
	pSheet = mainDlg->mp_Libxl->GetSheet(a_portAddr);

	bool bMerge = false;

	a_ColLast++;

	for (int row = a_RowFirst; row <= a_RowLast; row++) {
		WORD smData = mainDlg->GetDataFromSM(a_portAddr, a_node, (row - 5) / 2); // (WORD a_PortAddr, BYTE a_Node, BYTE a_Word)

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

	pSheet = NULL;
	mainDlg = NULL;
}
//--------------------------------------------------------------------------------------------

WORD _GFG::_GFG_SetMergeData(int a_Row, int a_Column, WORD a_SetData, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid)
{
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	Sheet *pSheet = NULL;
	pSheet = mainDlg->mp_Libxl->GetSheet(a_portAddr);

	bool bMerge = false;
	bool oldMerge = false;

	int mergeCount = 0;
	int startCol = 0;
	
	//WORD smData = mainDlg->GetDataFromSM(a_portAddr, a_node, (a_Row - 5) / 2); // (WORD a_PortAddr, BYTE a_Node, BYTE a_Word)
	for (int roop = 0; roop < 2; roop++) {
		for (int col = a_Column + 1; col <= 10; col++) {
			bMerge = pSheet->getMerge(a_Row + 3, col, 0, 0, 0, 0);

			// 병합이 되었다면...
			if (bMerge) {
				oldMerge = true;
				mergeCount++;

				if (mergeCount == 1)
					startCol = col - 1;
			}

			if (oldMerge && !bMerge) {
				CString gridText;

				if (mergeCount == 16) {
					// 엑셀 범위 세팅.
					int t_row_first = a_Row + 3, t_row_last = a_Row + 4;
					int t_col_first = 2, t_col_last = 9;

					pSheet->getMerge(a_Row, 2, &t_row_first, &t_row_last, &t_col_first, &t_col_last); // _row, _col, &row_first, &row_last, &col_first, &col_last		
					// 처음 행과 마지막 행을 비교하는 이유는 바이트 형식이면 두 변수(t_row_first, t_row_last)의 값이 같게 되지만 워드 형식이면 두 변수의 값이 다르다.
					if (t_row_first != t_row_last) {
						// 워드
						if (0 != a_SetData)
							ap_grid->SetItemBkColour(a_Row, startCol, PINK_COLOR);
						else
							ap_grid->SetItemBkColour(a_Row, startCol, WHITE_RGB);

						BYTE wordPos = (a_Row - 2) / 2;
						mainDlg->Set16DataToSM(a_portAddr, a_node, wordPos, a_SetData);

						gridText.Format(L"%s >> [%04X] [%d]", GetTextFormExcel(a_Row, startCol, pSheet), a_SetData, a_SetData);
						ap_grid->SetItemText(a_Row, startCol, gridText);
					}
					else {
						// 바이트
						unsigned char t_HByte = a_SetData >> 8;
						unsigned char t_LByte = a_SetData & 0xFF;

						// 상위 바이트
						if (0 != t_HByte)
							ap_grid->SetItemBkColour(a_Row, startCol, LIGHTYELLOW_COLOR);
						else
							ap_grid->SetItemBkColour(a_Row, startCol, WHITE_RGB);
						
						// 하위 바이트
						if (0 != t_LByte)
							ap_grid->SetItemBkColour(a_Row + 1, startCol, LIGHTYELLOW_COLOR);
						else
							ap_grid->SetItemBkColour(a_Row, startCol, WHITE_RGB);

						// 상위 바이트
						BYTE wordPos = (a_Row - 2) / 2;
						mainDlg->Set08DataToSM(a_portAddr, a_node, wordPos, t_HByte);

						gridText.Format(L"%s >> [%02X] [%d]", GetTextFormExcel(a_Row, startCol, pSheet), t_HByte, t_HByte);
						ap_grid->SetItemText(a_Row, startCol, gridText);

						// 하위 바이트
						wordPos += 1;
						mainDlg->Set08DataToSM(a_portAddr, a_node, wordPos, t_LByte);

						gridText.Format(L"%s >> [%02X] [%d]", GetTextFormExcel(a_Row + 1, startCol, pSheet), t_LByte, t_LByte);
						ap_grid->SetItemText(a_Row + 1, startCol, gridText);
					}

					oldMerge = false;
					mergeCount = 0;
				}
				/*else if (mergeCount >= 2 && mergeCount <= 7) {
					BYTE t_smData = mainDlg->GetByteDataFromSM(a_portAddr, a_node, a_Row);
					char t_bitPos = 8 - startCol;
					int move = t_bitPos - mergeCount + 1;
					int t_dataCheck = ((int)pow(2, mergeCount) - 1) & (t_smData >> move);

					if (0 != t_dataCheck)
						ap_grid->SetItemBkColour(a_Row, startCol, AQUA_COLOR);

					gridText.Format(L"%s >> [%02X] [%d]", GetTextFormExcel(a_Row, startCol, pSheet), t_dataCheck, t_dataCheck);
					ap_grid->SetItemText(a_Row, startCol, gridText);

					oldMerge = false;
					mergeCount = 0;
				}*/
			}
		}
	}

	pSheet = NULL;
	mainDlg = NULL;

	return 7;
}
//--------------------------------------------------------------------------------------------

