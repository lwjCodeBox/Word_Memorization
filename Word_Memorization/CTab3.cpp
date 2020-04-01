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

	m_pBtn = NULL;

	m_pEdit = NULL;
}

CTab3::~CTab3()
{
	// Button
	if (m_pBtn != NULL)
	{
		for (int i = 0; i < MAX_BTN; i++)
		{
			delete m_pBtn[i];
			m_pBtn[i] = NULL;
		}
		delete[] m_pBtn;
	}

	// Edit
	if (m_pEdit != NULL) 
	{
		for (int i = 0; i < MAX_EDIT; i++)
		{
			delete m_pEdit[i];
			m_pEdit[i] = NULL;
		}
		delete[] m_pEdit;
	}

	// Timer
	KillTimer(USER_TIMER_0);
}

void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab3, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_SHOWWINDOW()
	ON_COMMAND_RANGE(BTN_ID_1, BTN_ID_10, CTab3::OnButtonEvent)
	ON_WM_TIMER()
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

void CTab3::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// Create Button
	m_pBtn = new CButton * [MAX_BTN];
	CString caption = _T("");
	for (int i = 0; i < MAX_BTN; i++)
	{
		m_pBtn[i] = new CButton();
		caption.Format(_T("Car %d"), i);
		m_pBtn[i]->Create(caption, WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, CRect(20 + (101*i), 700, 120 + (101 * i), 750), this, BTN_ID_1 + i);
		// 20 (x좌표 시작지점이 20이고) + 101 (1씩 간격을 둠), 
		// 700 (y 좌표 시작 지점이 700이고), 
		// 120 (x좌표 20 지점에서 100만큼 떨어진 위치 즉, 폭이 100인 사각형을 만들겠다는 의미) + 101 (마찬가지로 1씩 간격을 둠), 
		// 750 (y좌표 700 지점에서 50만큼 떨어진 위치 즉, 높이가 50인 사격형을 만들겠다는 의미)

	}
	
	//http://www.tipssoft.com/bulletin/board.php?bo_table=update&wr_id=69&sca=&sfl=wr_subject%7C%7Cwr_content&stx=%B9%F6%C6%B0&sop=and&page=6
	m_pBtn[10] = new CButton();
	caption.Format(_T("Setting"));
	m_pBtn[10]->Create(caption, WS_CHILD | WS_VISIBLE |
		BS_PUSHBUTTON, CRect(1000, 800, 1200, 850), this, BTN_SEND);

	// Create Edit
	m_pEdit = new CEdit * [MAX_EDIT];
	for (int i = 0; i < MAX_EDIT; i++)
	{
		m_pEdit[i] = new CEdit();
		m_pEdit[i]->Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER, CRect(20 + (i*330), 800, 320 + (i * 330), 850), this, EDIT_ID_1 + 1);
		m_pEdit[i]->SetFont(GetFont());
	}

}


void CTab3::OnButtonEvent(UINT ID)
{
	CString msg = _T("");
	if (20000 == ID) 
	{
		// Set Directly
		CString getPort, getNode, getInputValue;
		m_pEdit[0]->GetWindowTextW(getPort);
		m_pEdit[1]->GetWindowTextW(getNode);
		m_pEdit[2]->GetWindowTextW(getInputValue);

		int smArrPos1 = _ttoi(getPort);
		int smArrPos2 = _ttoi(getNode);
		int smArrPos3 = _ttoi(getInputValue);

		//memset(mp_MainDlg->m_pData->data, 6, SM_DATA_MAX_COUNT*5);

		memset(&(mp_MainDlg->m_pData->data[smArrPos1][smArrPos2]), smArrPos3, 1);

		memset(&(mp_MainDlg->m_pData->data[80][smArrPos2]), smArrPos3, 1);
		
		m_HeartBit = 0;
		SetTimer(USER_TIMER_0, 300, NULL);

		//msg.Format(_T("%04x, %d"), mp_MainDlg->m_pData->data[smArrPos1][smArrPos2], smArrPos3);
	}
	else 
	{
		msg.Format(_T("%d MY BUTTON!"), ID - BTN_ID_1);
	}

	AfxMessageBox(msg);
}



void CTab3::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case USER_TIMER_0:
		if (m_HeartBit != 0xFFFF) {
			m_HeartBit++;
			
			//memset(&(mp_MainDlg->m_pData->data[19/*smArrPos1*/][0]), m_HeartBit, 2);
			//memset(&(mp_MainDlg->m_pData->data[11/*smArrPos1*/][0]), m_HeartBit, 2);

			//memset(&(mp_MainDlg->m_pData->data[119/*smArrPos1*/][0]), m_HeartBit, 2);
			//memset(&(mp_MainDlg->m_pData->data[219/*smArrPos1*/][0]), m_HeartBit, 2);

			//EBCU
			memset(&(mp_MainDlg->m_pData->data[0/*smArrPos1*/][0]), m_HeartBit, 2);
			memset(&(mp_MainDlg->m_pData->data[6/*smArrPos1*/][0]), m_HeartBit, 2);

			memset(&(mp_MainDlg->m_pData->data[100/*smArrPos1*/][0]), m_HeartBit, 2);
			memset(&(mp_MainDlg->m_pData->data[106/*smArrPos1*/][0]), m_HeartBit, 2);
		}
		else m_HeartBit = 0; 
		break;

	
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}
