// CForm_Protocol.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CForm_Protocol.h"

#include "CDeviceProtocol.h"
#include "./WJ_String.h"

// CForm_Protocol

IMPLEMENT_DYNCREATE(CForm_Protocol, CFormView)

CForm_Protocol::CForm_Protocol()
	: CFormView(IDD_FORM_PROTOCOL)
{

}

CForm_Protocol::~CForm_Protocol()
{
}

void CForm_Protocol::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CForm_Protocol, CFormView)

	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(27000, &CForm_Protocol::On27000)
END_MESSAGE_MAP()


// CForm_Protocol diagnostics

#ifdef _DEBUG
void CForm_Protocol::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CForm_Protocol::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CForm_Protocol message handlers


BOOL CForm_Protocol::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext)
{		
	// fix Caption
	fixCaption.xPos = 65;      // x 시작 좌표	
	fixCaption.width = 100;    // 폭 사이즈
	fixCaption.spacing_W = 20; // x 좌표 간격
	fixCaption.rowCount = 1;

	fixCaption.yPos = 5;      // y 시작 좌표	
	fixCaption.height = 25;    // 높이
	fixCaption.spacing_H = 0;  // y 좌표 간격
	fixCaption.colCount = 8;

	OnInitFixCaptionButton();

	// Init Protocol Button Pos;	
	protocolBTN.xPos = 65;      // x 시작 좌표	
	protocolBTN.width = 100;    // 폭 사이즈
	protocolBTN.spacing_W = 20; // x 좌표 간격
	protocolBTN.rowCount = 20;

	protocolBTN.yPos = 35;      // y 시작 좌표	
	protocolBTN.height = 30;    // 높이
	protocolBTN.spacing_H = 5;  // y 좌표 간격
	protocolBTN.colCount = 8;

	OnInitProtocolButton();

	m_pt_ClickedPos = new unsigned char *[protocolBTN.rowCount];

	for (int i = 0; i < protocolBTN.rowCount; i++) {
		m_pt_ClickedPos[i] = new unsigned char[protocolBTN.colCount];
		memset(m_pt_ClickedPos[i], 0, sizeof(unsigned char) * protocolBTN.colCount);
	}

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_Protocol::OnDestroy()
{
	CFormView::OnDestroy();	

	// Protocol Button	
	if (m_pt_ClickedPos != NULL) {
		for (int i = 0; i < protocolBTN.rowCount; i++) {
			delete[] m_pt_ClickedPos[i];
			m_pt_ClickedPos[i] = NULL;
		}
		delete[] m_pt_ClickedPos;
	}

	// PopUp Dlg
	while (0 != m_popupPtr.size()) {
		int pos = m_popupPtr.begin()->first;
		mp_PopUp = m_popupPtr.find(pos)->second;
		mp_PopUp->DestroyWindow();
		delete mp_PopUp;
		mp_PopUp = nullptr;

		m_popupPtr.erase(pos);		
	}	
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_Protocol::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_Protocol::OnPaint()
{
	CPaintDC dc(this);
	CRect r;

	OnDrawFixCaption(&dc, &r);
	OnDrawProtocolButton(&dc, &r);	
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_Protocol::OnInitFixCaptionButton()
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

void CForm_Protocol::OnInitProtocolButton()
{
	protocolBTN.r.clear();

	RECT r;
	for (int rowCnt = 0; rowCnt < protocolBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < protocolBTN.colCount; colCnt++) {
			r.left = protocolBTN.xPos + colCnt * (protocolBTN.width + protocolBTN.spacing_W);
			r.right = r.left + protocolBTN.width;
			r.top = protocolBTN.yPos + rowCnt * (protocolBTN.height + protocolBTN.spacing_H);
			r.bottom = r.top + protocolBTN.height;

			protocolBTN.r.push_back(r);
		}
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_Protocol::OnDrawFixCaption(CDC *p_DC, CRect *p_R)
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

void CForm_Protocol::OnDrawProtocolButton(CDC *p_DC, CRect *p_R)
{
	int pos = 0;
	int recPos = 0;

	for (int rowCnt = 0; rowCnt < protocolBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < protocolBTN.colCount; colCnt++) {
			pos = (10 * rowCnt) + colCnt;
			recPos = (protocolBTN.colCount * rowCnt) + colCnt;

			CString str;
			str.Format(L"%s", caption.HB_BTN_Caption.at(pos).c_str());
		
			if (!str.Compare(L"*")) continue;
			
			BYTE status = m_pt_ClickedPos[rowCnt][colCnt];
			CClientDC dc(this);
			recPos = (protocolBTN.colCount * rowCnt) + colCnt;
			Set_Protocol_OnOffcolor(status, str.GetBuffer(), protocolBTN.r[recPos], &dc);			
		}
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

BOOL CForm_Protocol::OnEraseBkgnd(CDC *pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect, RGB(0, 0, 0));
	pDC->Draw3dRect(rect, RGB(0, 0, 0), RGB(0, 0, 0));

	return true;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_Protocol::OnLButtonDown(UINT nFlags, CPoint point)
{	
	int port = 0;
	int node = 0;
	
	short pos = 0;
	short recPos = 0;
	
	for (int rowCnt = 0; rowCnt < protocolBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < protocolBTN.colCount; colCnt++) {
			recPos = (protocolBTN.colCount * rowCnt) + colCnt;

			if (PtInRect(&protocolBTN.r[recPos], point)) {
				pos = (10 * rowCnt) + colCnt;
				CString str;
				str.Format(L"%s", caption.HB_BTN_Caption.at(pos).c_str());
				
				if (!str.Compare(L"*"))	return;

				try {
					m_row = rowCnt;
					m_col = colCnt;

					try {
						int t_map_key = m_row * 10 + m_col;
						port = portAddr.used_on_Protocol.at(t_map_key); // find(t_map_key)->second;
						node = (m_col + 2) / 2;
						
						if (0 == m_pt_ClickedPos[m_row][m_col]) {
							m_pt_ClickedPos[m_row][m_col] = 1;

							CClientDC dc(this);	
							Set_Protocol_OnOffcolor(1, str.GetBuffer(), protocolBTN.r[recPos], &dc);

							str.Format(L"%s [port : 0x%02X] [node : %d]", str, port, node);

							// Create Protocol PopUp					
							mp_PopUp = new CDeviceProtocol(caption.HB_BTN_Caption.at(pos).c_str(), str.GetBuffer(), port, node);
							mp_PopUp->Create(IDD_PROTOCOL_POPUP, this);
							mp_PopUp->SetHWND(GetSafeHwnd());
							mp_PopUp->SetMapKey(t_map_key);
							mp_PopUp->SetWindowTextW(str.GetBuffer());
							
							m_popupPtr.insert(std::make_pair(t_map_key, mp_PopUp));
						}
						return;
					}
					catch (std::out_of_range &e) {
						str.Format(L"Do not found Excel sheet [%s]", e.what());
						AfxMessageBox(str);
						return;
					}																				
				}
				catch (std::out_of_range &e) {
					str.Format(L"[Catch the std::out_of_range] %s", e.what());
					AfxMessageBox(str); 
				}						
			}
		}
	}
		
	CFormView::OnLButtonDown(nFlags, point);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

afx_msg LRESULT CForm_Protocol::On27000(WPARAM wParam, LPARAM lParam)
{	
	mp_PopUp = m_popupPtr.find(wParam)->second;
	mp_PopUp->DestroyWindow();
	delete mp_PopUp;
	mp_PopUp = nullptr;

	m_popupPtr.erase(wParam);
	
	int row = wParam / 10;
	int col = wParam % 10;
	m_pt_ClickedPos[row][col] = 0;

	Invalidate();

	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+