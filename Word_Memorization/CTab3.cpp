// CTab3.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CTab3.h"
#include "afxdialogex.h"

#include "Word_MemorizationDlg.h"

// CTab3 dialog

IMPLEMENT_DYNAMIC(CTab3, CDialogEx)

CTab3::CTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{
	mp_MainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	//arr[rows][columns]라는 int형 2차원 배열이 있다고 가정하면
	//for (int i = 0; i < rows; i++) {
	//	memset(arr[i], 초기화하고자 하는 값, sizeof(int) * colums);
	//}
	int row = 15, column = 8;
	for (int i = 0; i < row; i++) {
		memset(m_CellClickStatus[i], 0, column * sizeof(unsigned char));
	}
}

CTab3::~CTab3()
{
	
}

void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab3, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CTab3 message handlers


void CTab3::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	
	CPen pen;
	pen.CreatePen(PS_DOT, 3, RGB(128, 128, 128)); 
	CPen *p_OldPen = dc.SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(150, 200, 200));     
	CBrush *p_OldBrush = dc.SelectObject(&brush);
	
	// Test code
	//for (int i = 0; i < 8; i++) {
	//	dc.Rectangle(20 + i * 30 + (i * 30), 130, 20 + (i + 1) * 30 + (i * 30), 190); // 폭 30에 30만큼 떨이진 사격형
	//}

	// Original code
	//for (int i = 0; i < 9; i++) {
	//	dc.Rectangle(20 + i * 150, 60, 20 + (i + 1) * 150, 120); // x좌표 시작점, y좌표 시작점, x좌표 끝지점, y좌표 끝지점
	//}
	
/* Sample Code of Builder XE5
	// Load Protocol Signal Name from Config.xlsx
	int grid_row = 0;
	int t_gap_col = 0; // for merge cell
	int t_gap_row = 0; // Skip... Later...

	for (int i = row_first; i < row_last; i++) {
		for (int j = col_first; j < col_last; j++) {
			tempStr = (wchar_t *)sheet->readStr(i, j, &format);
			p_grid->Cells[j][grid_row + 1] = tempStr;

			bMerge = sheet->getMerge(i, j, &merge_row_first, &merge_row_last, &merge_col_first, &merge_col_last);
			if (bMerge) { // do not handle cells merged more than 1 BYTE.
				t_gap_col = merge_col_last - merge_col_first + 1; // +1 is essential
				p_grid->MergeCells(j, grid_row, t_gap_col, 1);
				p_grid->MergeCells(j, grid_row + 1, t_gap_col, 1);
				j += (t_gap_col - 1);
			}
		}
		grid_row += 2;
	}
*/
	
	// fixed row, col
	int startWidth, endWidht;
	int startHeight, endHeight;
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 17; j++) {
			startWidth = 20 + i * 120; // x좌표 시작점
			endWidht = startWidth + 120;
			startHeight = 35 + j * 35;
			endHeight = startHeight + 35;

			dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 1; j++) {
			startWidth = 20 + i * 120; // x좌표 시작점
			endWidht = startWidth + 120;
			startHeight = 35 + j * 35;
			endHeight = startHeight + 35;

			dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
		}
	}
	dc.SelectObject(p_OldBrush);
	brush.DeleteObject();

	// not fixed row, col
	brush.CreateSolidBrush(RGB(200, 200, 200));
	p_OldBrush = dc.SelectObject(&brush);

	// 전체 초기화
	for (int j = 1; j < 17; j++) {
		for (int i = 1; i < 9; i++) {
			startWidth = 20 + i * 120; // x좌표 시작점
			endWidht = startWidth + 120;
			startHeight = 35 + j * 35;
			endHeight = startHeight + 35;

			dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
		}
	}

	// 병합된 부분만 다시 그림
	int row_first = 0; // user define (행 시작 위치)
	int row_last = 0;
	int col_first = 0; // user define (열 시작 위치)
	int col_last = 0; // user define

	int mergeCount = 0;
	bool bMerge = false;
	int firstMergeCellPos = 0;

	for (int j = 1; j < 17; j++) {
		for (int i = 1; i < 9+1; i++) { // 어디까지 병합이 되었는지 확인해야 하므로 한 칸더 체크를 해야함. 그래서 한 칸더 체크 하기 위해  +1을 함.
			bMerge = mp_MainDlg->mp_Libxl->m_pSheet1->getMerge(j + 1, i + 1, &row_first, &row_last, &col_first, &col_last);

			if (bMerge) {
				if (firstMergeCellPos == 0)
					startWidth = 20 + i * 120; 

				firstMergeCellPos++;
				mergeCount++;
				continue;
			}
			else {
				if (0 == mergeCount) { // 병합이 안돼고 단일 비트 상태 일때.
					startWidth = 20 + i * 120;
				}
				else {
					endWidht = startWidth + (120 * mergeCount); // 원래는 이렇게 생김. >> endWidht = startWidth + 120;
					startHeight = 35 + j * 35;
					endHeight = startHeight + 35;
					
					dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
					
					firstMergeCellPos = 0;
					mergeCount = 0;
				}
			}
		}
	}

	// 일시적으로 색을 변경했기 때문에 원래의 색상으로 되돌리는 것이 다른 시스템
	// 또는 프로그램을 위해 바람직하다.
	dc.SelectObject(p_OldBrush);
	dc.SelectObject(p_OldPen);

	// 팬, 브러쉬 객체 삭제
	pen.DeleteObject();
	brush.DeleteObject();

	PrintInitializeCell(&dc);
	FixedCellText(&dc);
}


void CTab3::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CPaintDC dc(this); // device context for painting
	CClientDC dc(this);

	CPen pen;
	pen.CreatePen(PS_DOT, 3, RGB(128, 128, 128));   
	CPen *p_OldPen = dc.SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(200, 200, 200));    
	CBrush *p_OldBrush = dc.SelectObject(&brush);

	//CPaintDC dc2(this); // device context for painting
	CClientDC dc2(this);

	CPen pen2;
	pen2.CreatePen(PS_DOT, 3, RGB(128, 128, 128));
	CPen *p_OldPen2 = dc2.SelectObject(&pen2);

	CBrush brush2;
	brush2.CreateSolidBrush(RGB(0, 200, 0));     // 라임 채움색을 생성
	CBrush *p_OldBrush2 = dc2.SelectObject(&brush2);

	// 120의 의미가 사각형의 폭을 말하며 사각형 폭 넓이 만큼 나눔.
	// 35의 의미가 사각형의 높이를 말하며 사각형 높이 만큼 나눔.
	unsigned int rx = (unsigned int)(point.x - 20) / 120, ry = (unsigned int)(point.y - 35) / 35; 

	int startWidth, endWidht;
	int startHeight, endHeight;

	unsigned char textPos_rx, textPos_ry;

	if ((rx > 0 && rx < 9) && (ry > 0 && ry < 17)) { // 0번째 위치 즉, 맨 앞에 있는 사격형에는 클릭을 해도 색 변경이 없음.
		// 모두다 그리기.
		//for (int i = 0; i < 9; i++) {
		//	for (int j = 0; j < 17; j++) {
		//		startWidth = 20 + i * 250; // x좌표 시작점
		//		endWidht = startWidth + 250;
		//		startHeight = 60 + j * 60;
		//		endHeight = startHeight + 60;
		//
		//		dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
		//	}
		//}
		

		startWidth = 20 + rx * 120; // x좌표 시작점
		endWidht = startWidth + 120;
		startHeight = 35 + ry * 35;
		endHeight = startHeight + 35;
		
		// 클릭을 했었는지 안했었는지 판단.
		if (1 == m_CellClickStatus[ry - 1][8 - rx]) { // 셀을 회색으로 채움
			int row_first = 0; // user define (행 시작 위치)
			int row_last = 0;
			int col_first = 0; // user define (열 시작 위치)
			int col_last = 0; // user define

			int mergeCount = 0;
			bool bMerge = false;
			int firstMergeCellPos = 0;

			bMerge = mp_MainDlg->mp_Libxl->m_pSheet1->getMerge(ry + 1, rx + 1, &row_first, &row_last, &col_first, &col_last);
			if (bMerge) {
				// 이 반복문을 통해 셀이 머지된곳 중 가장 첫번째 위치를 가리키게 함.
				while (1) {
					if (!bMerge) {
						textPos_rx = rx;
						textPos_ry = ry;
						break;
					}

					rx--;
					bMerge = mp_MainDlg->mp_Libxl->m_pSheet1->getMerge(ry + 1, rx + 1, &row_first, &row_last, &col_first, &col_last);
				}

				// 병합이 시작된 부분 부터 병합이 끝난 지점까지 반복문을 돌림.
				for (int i = rx + 1; i < 9 + 1; i++) { // 어디까지 병합이 되었는지 확인해야 하므로 한 칸더 체크를 해야함. 그래서 한 칸더 체크 하기 위해  +1을 함.
					bMerge = mp_MainDlg->mp_Libxl->m_pSheet1->getMerge(ry + 1, i + 1, &row_first, &row_last, &col_first, &col_last);

					if (bMerge) {
						if (firstMergeCellPos == 0)
							startWidth = 20 + i * 120;

						m_CellClickStatus[ry - 1][8 - i] = 0;

						firstMergeCellPos++;
						mergeCount++;
					}
					else {
						if (bMerge == false) { // 병합이 된부분이 끝났지점 일때 이 조건을 탐.
							endWidht = startWidth + (120 * mergeCount); // 원래는 이렇게 생김. >> endWidht = startWidth + 120;
							startHeight = 35 + ry * 35;
							endHeight = startHeight + 35;

							dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
							PrintSelectedCell(ry - 1, 8 - (rx + 1)); // 행(a_Row),열(a_Col)
							break;
						}
					}
				}
			}
			else {
				m_CellClickStatus[ry - 1][8 - rx] = 0;
				dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
				PrintSelectedCell(ry - 1, 8 - rx); // 행(a_Row),열(a_Col)
			}			
		}
		else { // 셀을 초록색으로 채움
			int row_first = 0; // user define (행 시작 위치)
			int row_last = 0;
			int col_first = 0; // user define (열 시작 위치)
			int col_last = 0; // user define

			int mergeCount = 0;
			bool bMerge = false;
			int firstMergeCellPos = 0;
			
			bMerge = mp_MainDlg->mp_Libxl->m_pSheet1->getMerge(ry + 1, rx + 1, &row_first, &row_last, &col_first, &col_last);
			if(bMerge) {
				// 이 반복문을 통해 셀이 머지된곳 중 가장 첫번째 위치를 가리키게 함.
				while (1) {
					if (!bMerge) {
						break;
					}
					
					rx--; 			
					bMerge = mp_MainDlg->mp_Libxl->m_pSheet1->getMerge(ry + 1, rx + 1, &row_first, &row_last, &col_first, &col_last);
				}

				// 병합이 시작된 부분 부터 병합이 끝난 지점까지 반복문을 돌림.
				for (int i = rx+1; i < 9 + 1; i++) { // 어디까지 병합이 되었는지 확인해야 하므로 한 칸더 체크를 해야함. 그래서 한 칸더 체크 하기 위해  +1을 함.
					bMerge = mp_MainDlg->mp_Libxl->m_pSheet1->getMerge(ry + 1, i + 1, &row_first, &row_last, &col_first, &col_last);

					if (bMerge) {
						if (firstMergeCellPos == 0) {
							startWidth = 20 + i * 120;
						}

						m_CellClickStatus[ry - 1][8 - i] = 1;

						firstMergeCellPos++;
						mergeCount++;
					}
					else {
						if (bMerge == false) { // 병합이 된부분이 끝났지점 일때 이 조건을 탐.
							endWidht = startWidth + (120 * mergeCount); // 원래는 이렇게 생김. >> endWidht = startWidth + 120;
							startHeight = 35 + ry * 35;
							endHeight = startHeight + 35;

							dc2.Rectangle(startWidth, startHeight, endWidht, endHeight);
							PrintSelectedCell(ry - 1, 8 - (rx+1)); // 행(a_Row),열(a_Col)
							break;
						}
					}
				}
			}
			else {
				m_CellClickStatus[ry - 1][8 - rx] = 1;
				dc2.Rectangle(startWidth, startHeight, endWidht, endHeight);
				PrintSelectedCell(ry - 1, 8 - rx); // 행(a_Row),열(a_Col)
			}
			
		}

		dc.SelectObject(p_OldBrush);
		dc.SelectObject(p_OldPen);
		pen.DeleteObject();
		brush.DeleteObject();

		dc2.SelectObject(p_OldBrush2);
		dc2.SelectObject(p_OldPen2);
		pen2.DeleteObject();
		brush2.DeleteObject();

		// 열에 8-rx을 해야하는 이유는 맨 앞칸은 라인 번호를 출력하는 곳이기 때문에
		// 실제로 0,0이 되는 위치는 두 번째 칸부터이다. 
		//PrintSelectedCell(ry - 1, 8 - rx); // 행(a_Row),열(a_Col) 	
	}
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CTab3::PrintSelectedCell(int a_Col, int a_Row)
{
	CClientDC dc(this);

	//////////////// 엑셀에서 텍스트 출력 /////////////
	CString str;
	str.Format(L"%s", mp_MainDlg->mp_Libxl->getExcelValue(a_Col, a_Row));
	unsigned char strLen = str.GetLength();

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 0, 0));
	
	int row = 120 + ((7 - a_Row) * 120 + (strLen + 60));
	int col = 25 + ((a_Col + 1) * 35) + 20;
	dc.TextOutW(row, col, str); // 행, 열 
}

void CTab3::PrintInitializeCell(CPaintDC *a_DC)
{
	CString str;
	
	for (int col = 0; col < 15 + 1; col++) { // 열(col)
		for (int row = 0; row < 7 + 1; row++) { // 행(row)
			str.Format(L"%s", mp_MainDlg->mp_Libxl->getExcelValue(col, row)); // 행(col), 열(row) 
			unsigned char strLen = str.GetLength();

			a_DC->SetBkMode(TRANSPARENT);
			a_DC->SetTextColor(RGB(0, 0, 0));
			120 + ((7 - row) * 120 + (strLen + 60));
			int t_row = 120 + ((7 - row) * 120 + (strLen + 60));
			int t_col = 25 + ((col + 1) * 35) + 20;
			a_DC->TextOutW(t_row, t_col, str); // 행, 열
		}
	}
}

void CTab3::FixedCellText(CPaintDC *a_DC)
{
	CString str;

	// 열(row)
	for (int row = 0; row < 7 + 1; row++) { 
		unsigned char strLen = str.GetLength();

		a_DC->SetBkMode(TRANSPARENT);
		a_DC->SetTextColor(RGB(140, 0, 255));
			
		int t_row = 120 + ((7 - row) * 120 + (strLen + 60));
		int t_col = 45; //25 + ((col + 1) * 35) + 20;

		str.Format(L"Bit %d", row);
		a_DC->TextOutW(t_row, t_col, str); // 열, 행 
	}
	// 행(col)
	for (int col = 0; col < 15 + 1; col++) { 
		unsigned char strLen = str.GetLength();

		a_DC->SetBkMode(TRANSPARENT);
		a_DC->SetTextColor(RGB(140, 0, 255));

		int t_row = strLen + 60 ; //120 + ((7 - row) * 120 + (strLen + 60));
		int t_col = 25 + ((col + 1) * 35) + 20;

		str.Format(L"Byte %d", col);
		a_DC->TextOutW(t_row, t_col, str); // 열, 행 
	}
}