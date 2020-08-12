#include "pch.h"

#include "Grid_Func_Group.h"
#include "DefineOfDev_J.h"

#include "Word_MemorizationDlg.h"
#include "_CExcelLib.h"

//--------------------------------------------------------------------------------------------

void _GFG_InitMakeGrid(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, CGridCtrl *ap_grid)
{
	Sheet **ppSheet = NULL;

	/*_CExcelLib *plibxl;
	if (0x1A4 == a_portAddr)
		ppSheet = &plibxl->m_pDU_Default_1;
	else if (0x1A8 == a_portAddr)
		ppSheet = &plibxl->m_pDU_Default_2;
	else if (0x1AC == a_portAddr)
		ppSheet = &plibxl->m_pDU_Default_3;
	else return;*/

	// Grid Setting
	bool bMerge = false;
	int mergeCol_start = 0;
	int mergeCol_finish = 0;

	a_ColLast++;
	
	// for()���� ���� ���� ������ ������ �о�� ��ġ�� �������� ��� ������
	for (int row = a_RowFirst; row <= a_RowLast; row++) {
		for (int col = a_ColFirst; col <= a_ColLast; col++) {
			//bMerge = (*ppSheet)->getMerge(row, col, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last			

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

	ppSheet = NULL;
}
//--------------------------------------------------------------------------------------------

void _GFG_SetWordFormatCell(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, CGridCtrl *ap_grid)
{
	Sheet **ppSheet = NULL;

	/*_CExcelLib *plibxl;
	if (0x1A4 == a_portAddr)
		ppSheet = &plibxl->m_pDU_Default_1;
	else if (0x1A8 == a_portAddr)
		ppSheet = &plibxl->m_pDU_Default_2;
	else if (0x1AC == a_portAddr)
		ppSheet = &plibxl->m_pDU_Default_3;
	else return;*/

	// Draw Word Format 
	bool bMerge = false;
	int mergeCount = 0;

	a_ColLast++;

	for (int row = a_RowFirst; row <= a_RowLast; row++) {
		for (int col = a_ColFirst; col <= a_ColLast; col++) {
			//bMerge = (*ppSheet)->getMerge(row, col, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last			

			// ������ �Ǿ��ٸ�...
			if (bMerge) {
				mergeCount++;
			}

			// Check Word Fomat
			if (mergeCount == 16) {
				// ���� ���� ����.
				int t_row_first = a_RowFirst, t_row_last = a_RowLast;
				int t_col_first = a_ColFirst, t_col_last = a_ColLast - 1;

				(*ppSheet)->getMerge(row, 2, &t_row_first, &t_row_last, &t_col_first, &t_col_last); // _row, _col, &row_first, &row_last, &col_first, &col_last		
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

	ppSheet = NULL;
}
//--------------------------------------------------------------------------------------------

void _GFG_SetDataCheck(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, WORD a_portAddr, BYTE a_node, CGridCtrl *ap_grid)
{
	Sheet **ppSheet = NULL;
	
	/*_CExcelLib *plibxl;
	if (0x1A4 == a_portAddr)
		ppSheet = &plibxl->m_pDU_Default_1;
	else if (0x1A8 == a_portAddr)
		ppSheet = &plibxl->m_pDU_Default_2;
	else if (0x1AC == a_portAddr)
		ppSheet = &plibxl->m_pDU_Default_3;
	else return;*/

	// Grid Setting
	bool bMerge = false;

	a_ColLast++;

	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();	
	// for()���� ���� ���� ������ ������ �о�� ��ġ�� �������� ��� ������
	for (int row = a_RowFirst; row <= a_RowLast; row++) {
		WORD smData = mainDlg->GetDataFromSM(a_portAddr, a_node, (row - 5) / 2); // (WORD a_PortAddr, BYTE a_Node, BYTE a_Word)

		for (int col = a_ColFirst; col <= a_ColLast; col++) {
			//bMerge = (*ppSheet)->getMerge(row, col, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last			

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

	mainDlg = NULL;
	ppSheet = NULL;
}
//--------------------------------------------------------------------------------------------

void _GFG_SetTextGrid(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, CGridCtrl *ap_grid)
{
	/*for (int row = a_RowFirst; row <= a_RowLast; row++) {
		for (int col = a_ColFirst; col <= a_ColLast; col++) {
			ap_grid->SetItemText(row, 9 - col, pExcel->GetDuDefaultValue(row - 2, col - 1, a_flag));
		}
	}*/
}
//--------------------------------------------------------------------------------------------

void _GFG_InitItemBkColor(int a_rowLast, int a_colLast, CGridCtrl *ap_grid)
{
	for (int row = 2; row <= a_rowLast; row++) {
		for (int col = 1; col <= a_colLast; col++) {
			ap_grid->SetItemBkColour(row, col, DEf_EVEN_WORD);
		}
	}
}
//--------------------------------------------------------------------------------------------