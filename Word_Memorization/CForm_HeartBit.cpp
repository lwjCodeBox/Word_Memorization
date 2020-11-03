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
	fixCaption.xPos = 65;      // x ���� ��ǥ	
	fixCaption.width = 100;    // �� ������
	fixCaption.spacing_W = 20; // x ��ǥ ����
	fixCaption.rowCount = 1;

	fixCaption.yPos = 20;      // y ���� ��ǥ	
	fixCaption.height = 25;    // ����
	fixCaption.spacing_H = 0;  // y ��ǥ ����
	fixCaption.colCount = 8;

	OnInitFixCaptionButton();

	// Init HeartBit Button Pos;	
	heartBitBTN.xPos = 65;      // x ���� ��ǥ	
	heartBitBTN.width = 100;    // �� ������
	heartBitBTN.spacing_W = 20; // x ��ǥ ����
	heartBitBTN.rowCount = 16;

	heartBitBTN.yPos = 50;      // y ���� ��ǥ	
	heartBitBTN.height = 30;    // ����
	heartBitBTN.spacing_H = 10;  // y ��ǥ ����
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

		// �۲� ��ü ����
		CFont font;

		// ���ϴ� �׸��� �׸��� ���� DC�� ��´�.
		//CClientDC dc(this);

		// ���ϴ� �Ӽ��� �����Ͽ� �۲��� �����Ѵ�.
		font.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS, L"���� ���");

		// ������ �۲��� ����Ͽ� ���ڿ��� ����ϱ� ���� �ش� �۲��� DC�� �����Ѵ�.
		p_DC->SelectObject(&font);

		//p_DC->FillSolidRect(&fixCaption.r[i], RGB(255, 255, 128)); 
		//p_DC->Draw3dRect(&fixCaption.r[i], RGB(0, 0, 0), RGB(0, 0, 0));
		p_DC->SetTextColor(RGB(0, 255, 255));

		p_DC->DrawText(str, &fixCaption.r[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		// ����� ���� ���� �����Ѵ�.
		p_DC->SetBkMode(old_mode);

		// �۲� ��ü�� �����Ѵ�.
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

				// �۲� ��ü ����
				CFont font;

				// ���ϴ� �׸��� �׸��� ���� DC�� ��´�.
				//CClientDC dc(this);

				// ���ϴ� �Ӽ��� �����Ͽ� �۲��� �����Ѵ�.
				font.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
					DEFAULT_PITCH | FF_SWISS, L"���� ���");

				// ������ �۲��� ����Ͽ� ���ڿ��� ����ϱ� ���� �ش� �۲��� DC�� �����Ѵ�.
				p_DC->SelectObject(&font);

				if (1 == m_HB_ClickedPos[rowCnt][colCnt]) {
					p_DC->FillSolidRect(&heartBitBTN.r[pos], RGB(0, 50, 128)); // ����.
					p_DC->Draw3dRect(&heartBitBTN.r[pos], RGB(0, 200, 255), RGB(0, 0, 0));
					p_DC->SetTextColor(RGB(255, 255, 255));

					p_DC->DrawText(str, (CRect)heartBitBTN.r[pos] + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else {					
					p_DC->FillSolidRect(&heartBitBTN.r[pos], RGB(192, 192, 192)); // �ȴ���.							
					p_DC->Draw3dRect(&heartBitBTN.r[pos], RGB(255, 255, 255), RGB(255, 255, 255));
					p_DC->SetTextColor(RGB(0, 0, 0));

					p_DC->DrawText(str, &heartBitBTN.r[pos], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

				// ����� ���� ���� �����Ѵ�.
				p_DC->SetBkMode(old_mode);

				// �۲� ��ü�� �����Ѵ�.
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

	// HeartBit button ���� üũ.	
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
		// �۲� ��ü ����
		CFont font;

		// ���ϴ� �׸��� �׸��� ���� DC�� ��´�.
		CClientDC dc(this);

		// ���ϴ� �Ӽ��� �����Ͽ� �۲��� �����Ѵ�.
		font.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_SWISS, L"���� ���");

		// ������ �۲��� ����Ͽ� ���ڿ��� ����ϱ� ���� �ش� �۲��� DC�� �����Ѵ�.
		dc.SelectObject(&font);

		int old_mode = dc.SetBkMode(TRANSPARENT);
		CString str;
		str.Format(L"%s", caption.HB_BTN_Caption.at(click_HB_BTN).c_str());		

		if (1 == m_HB_ClickedPos[_row][_col]) { // ���� -> �ȴ���
			m_HB_ClickedPos[_row][_col] = false;

			dc.FillSolidRect(&heartBitBTN.r[click_HB_BTN], RGB(192, 192, 192)); // �ȴ���.							
			dc.Draw3dRect(&heartBitBTN.r[click_HB_BTN], RGB(255, 255, 255), RGB(255, 255, 255));
			dc.SetTextColor(RGB(0, 0, 0));

			dc.DrawText(str, &heartBitBTN.r[click_HB_BTN], DT_CENTER | DT_VCENTER | DT_SINGLELINE);		

			Thread_stop();
			//Thread_Allstop();
		}
		else { // �ȴ��� -> ����
			m_HB_ClickedPos[_row][_col] = true;

			dc.FillSolidRect(&heartBitBTN.r[click_HB_BTN], RGB(0, 50, 128)); // ����.
			dc.Draw3dRect(&heartBitBTN.r[click_HB_BTN], RGB(0, 200, 255), RGB(0, 0, 0));
			dc.SetTextColor(RGB(255, 255, 255));

			dc.DrawText(str, (CRect)heartBitBTN.r[click_HB_BTN] + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			Thread_Start();
		}

		// �۲� ��ü�� �����Ѵ�.
		font.DeleteObject();

		// ����� ���� ���� �����Ѵ�.
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

	p->h_kill_event = CreateEvent(NULL, 1, 0, NULL); // �����带 ���� �̺�Ʈ ť ����.
	p->h_thread = CreateThread(NULL, 0, SM_Thread_Run, p, 0, &p->thread_id); // ������ ����.
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_HeartBit::Thread_stop()
{			
	ThreadData *p = (ThreadData*)GetThreadPtr(m_thread_count);
	if (p->h_thread != NULL) {
		p->flag = false;
		SetEvent(p->h_kill_event); // �����尡 ����Ǿ��ٴ� �̺�Ʈ�� ������.
		
		// ������� ���ϱ� ���� �� �۾��� ��.
		MSG msg;
		// 27001 �̺�Ʈ���� ������ �����带 NULL�� ���鶧 ���� ��� �����ϰ� 
		// 27001 �̺�Ʈ���� ������ �����带 NULL�� ������ٸ� �׶� �����Ҵ��� �����带 �ı��Ѵ�.
		// ��, �Ʒ� �ڵ�� �����尡 ���� �Ǿ����� üũ�ϱ� �����̴�.
		while (p->h_thread != NULL) {
			// PeekMessage >> �޽����� �ִ��� ������ ���� �Լ��̸� �޽����� ������ �� �Լ��� �ɷ� ���� �ʰ� �˾Ƽ� PeekMessage �Լ��� �������´�.
			// GetMessage >> �޽����� �־������ ���� ������ �Լ��̸� �޽����� ������ ���⿡ �ɷ� �ִ�. 
			//               �׷��� �޽����� ��� �ö� ���� ��⸦ Ÿ�ԵǼ� ������� ���� �� �ִ�.
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

// lParam >> � �����尡 ����Ǿ������� �� �� �ִ� ������ ������ ��� �ִ�.
afx_msg LRESULT CForm_HeartBit::On27001(WPARAM wParam, LPARAM lParam)
{
	ThreadData *p = (ThreadData *)lParam;
	
	for (int i = 0; i <= m_thread_count; i++) {
		if (GetThreadPtr(i) == p) {
			CloseHandle(p->h_kill_event); // �����尡 ����Ǿ��� ������ �̺�Ʈ�� �����Ŵ.

			if (wParam == 0) // ������ ���� ���. (�� �ڵ忡���� ������ ���� �ʴ´�. �̻�� �ڵ� ����) 
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