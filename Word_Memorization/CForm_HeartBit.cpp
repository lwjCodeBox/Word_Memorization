// CForm_HeartBit.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CForm_HeartBit.h"

#include <time.h>
#include <Windows.h>

#include "Thread/Multi_Thread.h"

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
	ON_MESSAGE(27001, &CForm_HeartBit::On27001)
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
	
	//Thread_Allstop();

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

		// 글꼴 객체 선언
		CFont font;

		// 원하는 그림을 그리기 위해 DC를 얻는다.
		//CClientDC dc(this);

		// 원하는 속성을 지정하여 글꼴을 생성한다.
		font.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS, L"맑은 고딕");

		// 생성된 글꼴을 사용하여 문자열을 출력하기 위해 해당 글꼴을 DC에 연결한다.
		p_DC->SelectObject(&font);

		//p_DC->FillSolidRect(&fixCaption.r[i], RGB(255, 255, 128)); 
		//p_DC->Draw3dRect(&fixCaption.r[i], RGB(0, 0, 0), RGB(0, 0, 0));
		p_DC->SetTextColor(RGB(0, 255, 255));

		p_DC->DrawText(str, &fixCaption.r[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		// 배경을 이전 모드로 설정한다.
		p_DC->SetBkMode(old_mode);

		// 글꼴 객체를 제거한다.
		font.DeleteObject();
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

				// 글꼴 객체 선언
				CFont font;

				// 원하는 그림을 그리기 위해 DC를 얻는다.
				//CClientDC dc(this);

				// 원하는 속성을 지정하여 글꼴을 생성한다.
				font.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					DEFAULT_PITCH | FF_SWISS, L"맑은 고딕");

				// 생성된 글꼴을 사용하여 문자열을 출력하기 위해 해당 글꼴을 DC에 연결한다.
				p_DC->SelectObject(&font);

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

				// 글꼴 객체를 제거한다.
				font.DeleteObject();
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
				catch (std::out_of_range &e) { 
					str.Format(L"[Catch the std::out_of_range] %s", e.what());
					AfxMessageBox(str); 
				}

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
		// 글꼴 객체 선언
		CFont font;

		// 원하는 그림을 그리기 위해 DC를 얻는다.
		CClientDC dc(this);

		// 원하는 속성을 지정하여 글꼴을 생성한다.
		font.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS, L"맑은 고딕");

		// 생성된 글꼴을 사용하여 문자열을 출력하기 위해 해당 글꼴을 DC에 연결한다.
		dc.SelectObject(&font);

		int old_mode = dc.SetBkMode(TRANSPARENT);
		CString str;
		str.Format(L"%s", caption.HB_BTN_Caption.at(click_HB_BTN).c_str());		

		if (1 == m_HB_ClickedPos[_row][_col]) { // 눌림 -> 안눌림
			m_HB_ClickedPos[_row][_col] = false;

			dc.FillSolidRect(&heartBitBTN.r[click_HB_BTN], RGB(192, 192, 192)); // 안눌림.							
			dc.Draw3dRect(&heartBitBTN.r[click_HB_BTN], RGB(255, 255, 255), RGB(255, 255, 255));
			dc.SetTextColor(RGB(0, 0, 0));

			dc.DrawText(str, &heartBitBTN.r[click_HB_BTN], DT_CENTER | DT_VCENTER | DT_SINGLELINE);		

			Thread_stop();
			//Thread_Allstop();
		}
		else { // 안눌림 -> 눌림
			m_HB_ClickedPos[_row][_col] = true;

			dc.FillSolidRect(&heartBitBTN.r[click_HB_BTN], RGB(0, 50, 128)); // 눌림.
			dc.Draw3dRect(&heartBitBTN.r[click_HB_BTN], RGB(0, 200, 255), RGB(0, 0, 0));
			dc.SetTextColor(RGB(255, 255, 255));

			dc.DrawText(str, (CRect)heartBitBTN.r[click_HB_BTN] + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			Thread_Start();
		}

		// 글꼴 객체를 제거한다.
		font.DeleteObject();

		// 배경을 이전 모드로 설정한다.
		dc.SetBkMode(old_mode);							
	}	

	CFormView::OnLButtonDown(nFlags, point);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_HeartBit::Thread_Start()
{
	//if (m_thread_list.GetCount() > 0) return;
	
	++m_thread_count;

	ThreadData *p = new ThreadData;
	p->h_wnd = m_hWnd;

	// lwj - 2020.11.02
	p->thread_count = m_thread_count;	
	p->port = m_thread_count;
	p->flag = true;

	p->h_kill_event = CreateEvent(NULL, 1, 0, NULL); // 스레드를 위한 이벤트 큐 생성.
	p->h_thread = CreateThread(NULL, 0, SM_Thread_Run, p, 0, &p->thread_id); // 스레드 생성.
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_HeartBit::Thread_stop()
{			
	ThreadData *p = (ThreadData*)GetThreadPtr(m_thread_count);
	if (p->h_thread != NULL) {
		p->flag = false;
		SetEvent(p->h_kill_event); // 스레드가 종료되었다는 이벤트로 설정함.
		
		// 데드락을 피하기 위해 이 작업을 함.
		MSG msg;
		// 27001 이벤트에서 종료한 스레드를 NULL로 만들때 까지 계속 진행하고 
		// 27001 이벤트에서 종료한 스레드를 NULL로 만들었다면 그때 동적할당한 스레드를 파괴한다.
		// 즉, 아래 코드는 스레드가 종료 되었는지 체크하기 위함이다.
		while (p->h_thread != NULL) {
			// PeekMessage >> 메시지가 있는지 없는지 보는 함수이며 메시지가 없으면 이 함수에 걸려 있지 않고 알아서 PeekMessage 함수를 빠져나온다.
			// GetMessage >> 메시지가 있어야지만 빠져 나오는 함수이며 메시지가 없으면 여기에 걸려 있다. 
			//               그래서 메시지가 들어 올때 까지 대기를 타게되서 데드락에 빠질 수 있다.
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	DeleteThreadPtr(m_thread_count);
	m_thread_count--;
	delete p;	
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// lParam >> 어떤 스레드가 종료되었는지를 알 수 있는 스레드 정보를 담고 있다.
afx_msg LRESULT CForm_HeartBit::On27001(WPARAM wParam, LPARAM lParam)
{
	ThreadData *p = (ThreadData *)lParam;
	
	for (int i = 0; i <= m_thread_count; i++) {
		if (GetThreadPtr(i) == p) {
			CloseHandle(p->h_kill_event); // 스레드가 종료되었기 때문에 이벤트도 종료시킴.

			if (wParam == 0) // 스스로 죽은 경우. (이 코드에서는 스스로 죽지 않는다. 이사님 코드 참고) 
				delete p; 
			else 
				p->h_thread = NULL;
			break;
		}
	}

	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_HeartBit::Thread_Allstop()
{
	ThreadData *p;
	int count = m_thread_count;
	for (int i = 0; i <= count; i++) {
		p = (ThreadData *)GetThreadPtr(m_thread_count);
		SetEvent(p->h_kill_event);
	}

	MSG msg;
	while (count) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == 27001) {
				count--;
				msg.wParam = 0;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	m_thread_count = -1;
	TRACE(L"Thread All Stop\n");
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+