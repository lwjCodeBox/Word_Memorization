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
	pen.CreatePen(PS_DOT, 3, RGB(0, 0, 128));    // 파란색보다 좀더 찐한 파란색 펜을 생성
	CPen *p_OldPen = dc.SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 100, 200));     // 파란색 채움색을 생성
	CBrush *p_OldBrush = dc.SelectObject(&brush);
	
	// Test code
	//for (int i = 0; i < 8; i++) {
	//	dc.Rectangle(20 + i * 30 + (i * 30), 130, 20 + (i + 1) * 30 + (i * 30), 190); // 폭 30에 30만큼 떨이진 사격형
	//}

	// Original code
	//for (int i = 0; i < 9; i++) {
	//	dc.Rectangle(20 + i * 150, 60, 20 + (i + 1) * 150, 120); // x좌표 시작점, y좌표 시작점, x좌표 끝지점, y좌표 끝지점
	//}

	int startWidth, endWidht;
	int startHeight, endHeight;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 17; j++) {
			startWidth = 20 + i * 250; // x좌표 시작점
			endWidht = startWidth + 250;
			startHeight = 60 + j * 60;
			endHeight = startHeight + 60;

			dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
		}
	}
	
	// 일시적으로 색을 변경했기 때문에 원래의 색상으로 되돌리는 것이 다른 시스템
	// 또는 프로그램을 위해 바람직하다.
	dc.SelectObject(p_OldBrush);
	dc.SelectObject(p_OldPen);

	// 팬, 브러쉬 객체 삭제
	pen.DeleteObject();
	brush.DeleteObject();
}


void CTab3::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CPaintDC dc(this); // device context for painting
	CClientDC dc(this);

	CPen pen;
	pen.CreatePen(PS_DOT, 3, RGB(0, 0, 128));    // 파란색보다 좀더 찐한 파란색 펜을 생성
	CPen *p_OldPen = dc.SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 100, 200));     // 파란색 채움색을 생성
	CBrush *p_OldBrush = dc.SelectObject(&brush);

	//CPaintDC dc2(this); // device context for painting
	CClientDC dc2(this);

	//CPen pen2;
	//pen2.CreatePen(PS_DOT, 3, RGB(0, 0, 128));    // 파란색보다 좀더 찐한 파란색 펜을 생성
	//CPen *p_OldPen2 = dc2.SelectObject(&pen2);

	CBrush brush2;
	brush2.CreateSolidBrush(RGB(0, 255, 0));     // 라임 채움색을 생성
	CBrush *p_OldBrush2 = dc2.SelectObject(&brush2);

	// 250의 의미가 사각형의 폭을 말하며 사각형 폭 넓이 만큼 나눔.
	// 60의 의미가 사각형의 높이를 말하며 사각형 높이 만큼 나눔.
	unsigned int rx = (unsigned int)(point.x - 20) / 250, ry = (unsigned int)(point.y - 60) / 60; 
	int startWidth, endWidht;
	int startHeight, endHeight;

	if ((rx > 0 && rx < 9) && (ry > 0 && ry < 17)) { // 0번째 위치 즉, 맨 앞에 있는 사격형에는 클릭을 해도 색 변경이 없음.
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 17; j++) {
				startWidth = 20 + i * 250; // x좌표 시작점
				endWidht = startWidth + 250;
				startHeight = 60 + j * 60;
				endHeight = startHeight + 60;

				dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
			}
		}
		startWidth = 20 + rx * 250; // x좌표 시작점
		endWidht = startWidth + 250;
		startHeight = 60 + ry * 60;
		endHeight = startHeight + 60;
		
		dc2.Rectangle(startWidth, startHeight, endWidht, endHeight);

		// 열에 8-rx을 해야하는 이유는 맨 앞칸은 라인 번호를 출력하는 곳이기 때문에
		// 실제로 0,0이 되는 위치는 두 번째 칸부터이다. 
		PrintExcelSheet(ry-1, 8-rx); // 행(a_Col),열(a_Row) 
	}
	

	dc.SelectObject(p_OldBrush);
	dc.SelectObject(p_OldPen);
	pen.DeleteObject();
	brush.DeleteObject();

	dc2.SelectObject(p_OldBrush2);
	//dc2.SelectObject(p_OldPen2);
	//pen2.DeleteObject();
	brush2.DeleteObject();
	
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CTab3::PrintExcelSheet(int a_Col, int a_Row)
{
	CClientDC dc(this);
	//////////////// 엑셀에서 텍스트 출력 /////////////
	mp_MainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	CString str;
	str.Format(L"%s", mp_MainDlg->mp_Libxl->getExcelValue(a_Col, a_Row));
	unsigned char strLen = str.GetLength();

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 0, 0));
	//dc.TextOutW( 80 + (a_Row * 60), 20 + (37 - strLen) + (a_Col * 150), str);
	int row = 250 + ((7 - a_Row) * 250 + (strLen + 70));
	int col = 60 + ((a_Col + 1) * 60) + 20;
	dc.TextOutW(row, col, str); // 열, 행 
}