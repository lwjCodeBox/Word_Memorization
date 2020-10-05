// CForm_HeartBit.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CForm_HeartBit.h"

#include <time.h>
#include <Windows.h>

#define MAXTHREAD 5

// CForm_HeartBit

IMPLEMENT_DYNCREATE(CForm_HeartBit, CFormView)

CForm_HeartBit::CForm_HeartBit()
	: CFormView(IDD_FORM_HEARTBIT)
{

}

CForm_HeartBit::~CForm_HeartBit()
{
	
}

void CForm_HeartBit::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CForm_HeartBit, CFormView)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CForm_HeartBit diagnostics

#ifdef _DEBUG
void CForm_HeartBit::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CForm_HeartBit::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CForm_HeartBit message handlers


BOOL CForm_HeartBit::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext)
{
	// fix Caption
	fixCaption.xPos = 65;      // x 시작 좌표	
	fixCaption.width = 100;    // 폭 사이즈
	fixCaption.spacing_W = 20; // x 좌표 간격
	fixCaption.rowCount = 1;

	fixCaption.yPos = 20;      // y 시작 좌표	
	fixCaption.height = 25;    // 높이
	fixCaption.spacing_H = 0;  // y 좌표 간격
	fixCaption.colCount = 8;

	OnInitFixCaptionButton();

	// Init HeartBit Button Pos;	
	heartBitBTN.xPos = 65;      // x 시작 좌표	
	heartBitBTN.width = 100;    // 폭 사이즈
	heartBitBTN.spacing_W = 20; // x 좌표 간격
	heartBitBTN.rowCount = 16;

	heartBitBTN.yPos = 50;      // y 시작 좌표	
	heartBitBTN.height = 30;    // 높이
	heartBitBTN.spacing_H = 10;  // y 좌표 간격
	heartBitBTN.colCount = 8;

	OnInitHeartBitButton();

	m_HB_ClickedPos = new unsigned char * [heartBitBTN.rowCount];

	for (int i = 0; i < heartBitBTN.rowCount; i++) {
		m_HB_ClickedPos[i] = new unsigned char[heartBitBTN.colCount];
		memset(m_HB_ClickedPos[i], 0, sizeof(unsigned char) * heartBitBTN.colCount);
	}
	

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_HeartBit::OnDestroy()
{
	CFormView::OnDestroy();
	
	// HeartBit Button	
	if (m_HB_ClickedPos != NULL) {
		for (int i = 0; i < heartBitBTN.rowCount; i++) {
			delete[] m_HB_ClickedPos[i];
			m_HB_ClickedPos[i] = NULL;
		}
		delete[] m_HB_ClickedPos;
	}

	fixCaption.r.clear();
	heartBitBTN.r.clear();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_HeartBit::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_HeartBit::OnPaint()
{
	CPaintDC dc(this);
	CRect r;

	OnDrawFixCaption(&dc, &r);
	OnDrawHeartBitButton(&dc, &r);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_HeartBit::OnInitFixCaptionButton()
{
	fixCaption.r.clear();

	RECT r;
	for (int rowCnt = 0; rowCnt < fixCaption.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < fixCaption.colCount; colCnt++) {
			r.left = fixCaption.xPos + colCnt * (fixCaption.width + fixCaption.spacing_W);
			r.right = r.left + fixCaption.width;
			r.top = fixCaption.yPos + rowCnt * (fixCaption.height + fixCaption.spacing_H);
			r.bottom = r.top + fixCaption.height;

			fixCaption.r.push_back(r);
		}
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_HeartBit::OnInitHeartBitButton()
{
	heartBitBTN.r.clear();

	RECT r;
	for (int rowCnt = 0; rowCnt < heartBitBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < heartBitBTN.colCount; colCnt++) {
			r.left = heartBitBTN.xPos + colCnt * (heartBitBTN.width + heartBitBTN.spacing_W);
			r.right = r.left + heartBitBTN.width;
			r.top = heartBitBTN.yPos + rowCnt * (heartBitBTN.height + heartBitBTN.spacing_H);
			r.bottom = r.top + heartBitBTN.height;

			heartBitBTN.r.push_back(r);
		}
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_HeartBit::OnDrawFixCaption(CDC *p_DC, CRect *p_R)
{
	for (int i = 0; i < fixCaption.colCount; i++) {
		int old_mode = p_DC->SetBkMode(TRANSPARENT);

		CString str;
		str.Format(L"%s", caption.trainBTN_Caption.at(i).c_str());

		//p_DC->FillSolidRect(&fixCaption.r[i], RGB(255, 255, 128)); 
		//p_DC->Draw3dRect(&fixCaption.r[i], RGB(0, 0, 0), RGB(0, 0, 0));
		p_DC->SetTextColor(RGB(0, 255, 255));

		p_DC->DrawText(str, &fixCaption.r[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		// 배경을 이전 모드로 설정한다.
		p_DC->SetBkMode(old_mode);
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_HeartBit::OnDrawHeartBitButton(CDC *p_DC, CRect *p_R)
{
	int pos = 0;

	for (int rowCnt = 0; rowCnt < heartBitBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < heartBitBTN.colCount; colCnt++) {		
			pos = (heartBitBTN.colCount * rowCnt) + colCnt;

			CString str;
			str.Format(L"%s", caption.HB_BTN_Caption.at(pos).c_str());			
			if (!str.Compare(L"*")) {
				// empth
			}
			else {
				int old_mode = p_DC->SetBkMode(TRANSPARENT);

				if (1 == m_HB_ClickedPos[rowCnt][colCnt]) {
					p_DC->FillSolidRect(&heartBitBTN.r[pos], RGB(0, 50, 128)); // 눌림.
					p_DC->Draw3dRect(&heartBitBTN.r[pos], RGB(0, 200, 255), RGB(0, 0, 0));
					p_DC->SetTextColor(RGB(255, 255, 255));

					p_DC->DrawText(str, (CRect)heartBitBTN.r[pos] + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else {					
					p_DC->FillSolidRect(&heartBitBTN.r[pos], RGB(192, 192, 192)); // 안눌림.							
					p_DC->Draw3dRect(&heartBitBTN.r[pos], RGB(255, 255, 255), RGB(255, 255, 255));
					p_DC->SetTextColor(RGB(0, 0, 0));

					p_DC->DrawText(str, &heartBitBTN.r[pos], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

				// 배경을 이전 모드로 설정한다.
				p_DC->SetBkMode(old_mode);
			}
		}
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

BOOL CForm_HeartBit::OnEraseBkgnd(CDC *pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(0, 0, 0));
	pDC->Draw3dRect(rect, RGB(0, 0, 0), RGB(0, 0, 0));

	return true;	
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

DWORD WINAPI ThreadFunc(LPVOID n)
{
	for (int i = 0; i < 1000000000; i++) {
		3 + 5 + 8 * 24;
	}
	return 0;
}

void CForm_HeartBit::OnLButtonDown(UINT nFlags, CPoint point)
{
	unsigned int _col = 0, _row = 0;

	// HeartBit button 범위 체크.	
	bool bHeartBitBTN = false;
	short click_HB_BTN = -1;
	short pos = 0;

	for (int rowCnt = 0; rowCnt < heartBitBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < heartBitBTN.colCount; colCnt++) {	
			pos = (heartBitBTN.colCount * rowCnt) + colCnt;
			
			if (PtInRect(&heartBitBTN.r[pos], point)) {
				CString str;
				try { str.Format(L"%s", caption.HB_BTN_Caption.at(pos).c_str()); }
				catch (std::out_of_range &e) { AfxMessageBox(L"Catch the std::out_of_range"); }

				if (!str.Compare(L"*")) return;				
				
				_row = rowCnt;
				_col = colCnt;

				bHeartBitBTN = true;
				click_HB_BTN = pos;								
			}			
		}
	}
	
	// HeartBit button
	if (bHeartBitBTN) {
		CClientDC dc(this);

		int old_mode = dc.SetBkMode(TRANSPARENT);
		CString str;
		str.Format(L"%s", caption.HB_BTN_Caption.at(click_HB_BTN).c_str());
		
		if (1 == m_HB_ClickedPos[_row][_col]) {
			m_HB_ClickedPos[_row][_col] = false;

			dc.FillSolidRect(&heartBitBTN.r[click_HB_BTN], RGB(192, 192, 192)); // 안눌림.							
			dc.Draw3dRect(&heartBitBTN.r[click_HB_BTN], RGB(255, 255, 255), RGB(255, 255, 255));
			dc.SetTextColor(RGB(0, 0, 0));

			dc.DrawText(str, &heartBitBTN.r[click_HB_BTN], DT_CENTER | DT_VCENTER | DT_SINGLELINE);		

			// add 2020.10.05
			// main 쓰레드가 종료하면 워커쓰레드도 종료하므로 무한 대기하게 한다
			WaitForSingleObject(hThread, INFINITE);
		}
		else {		
			m_HB_ClickedPos[_row][_col] = true;

			dc.FillSolidRect(&heartBitBTN.r[click_HB_BTN], RGB(0, 50, 128)); // 눌림.
			dc.Draw3dRect(&heartBitBTN.r[click_HB_BTN], RGB(0, 200, 255), RGB(0, 0, 0));
			dc.SetTextColor(RGB(255, 255, 255));

			dc.DrawText(str, (CRect)heartBitBTN.r[click_HB_BTN] + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			// add 2020.10.05
			//AfxBeginThread(WorkerThread, this);
						
			_beginthreadex(NULL, 0, WorkerThread, NULL, 0, (unsigned *)&dwThreadID);
			
			if (hThread == 0) TRACE("_beginthreadex Error\n\n");

		
		}

		// 배경을 이전 모드로 설정한다.
		dc.SetBkMode(old_mode);

		//// add 2020.10.05
		//clock_t start, finish;
		//double duration;
		//DWORD threadId;
		//HANDLE hThrd[MAXTHREAD];

		//int i;
		//start = clock();//현재 시간 반환

		//for (i = 0; i < MAXTHREAD; i++) {
		//	hThrd[i] = CreateThread(NULL,
		//		0,
		//		ThreadFunc,
		//		(LPVOID)i,
		//		0,
		//		&threadId
		//	);
		//}
		//WaitForMultipleObjects(MAXTHREAD, hThrd, TRUE, INFINITE);
		//for (i = 0; i < MAXTHREAD; i++) {
		//	CloseHandle(hThrd[i]);
		//}
		////종료
		//finish = clock();
		//duration = (double)(finish - start) / CLOCKS_PER_SEC;

		//CString threadSTR;
		//threadSTR.Format(L"%f 초입니다", duration);
		//AfxMessageBox(threadSTR);
		////printf("%f 초입니다\n", duration);
		//return;
	}	

	CFormView::OnLButtonDown(nFlags, point);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+