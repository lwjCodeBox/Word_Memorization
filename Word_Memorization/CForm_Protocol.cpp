// CForm_Protocol.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CForm_Protocol.h"

#include "CDeviceProtocol.h"

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

	fixCaption.yPos = 20;      // y 시작 좌표	
	fixCaption.height = 25;    // 높이
	fixCaption.spacing_H = 0;  // y 좌표 간격
	fixCaption.colCount = 8;

	OnInitFixCaptionButton();

	// Init Protocol Button Pos;	
	protocolBTN.xPos = 65;      // x 시작 좌표	
	protocolBTN.width = 100;    // 폭 사이즈
	protocolBTN.spacing_W = 20; // x 좌표 간격
	protocolBTN.rowCount = 17;

	protocolBTN.yPos = 50;      // y 시작 좌표	
	protocolBTN.height = 30;    // 높이
	protocolBTN.spacing_H = 10;  // y 좌표 간격
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

	for (int rowCnt = 0; rowCnt < protocolBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < protocolBTN.colCount; colCnt++) {
			pos = (protocolBTN.colCount * rowCnt) + colCnt;

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

				if (1 == m_pt_ClickedPos[rowCnt][colCnt]) {
					p_DC->FillSolidRect(&protocolBTN.r[pos], RGB(0, 50, 128)); // 눌림.
					p_DC->Draw3dRect(&protocolBTN.r[pos], RGB(0, 200, 255), RGB(0, 0, 0));
					p_DC->SetTextColor(RGB(255, 255, 255));

					p_DC->DrawText(str, (CRect)protocolBTN.r[pos] + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else {
					p_DC->FillSolidRect(&protocolBTN.r[pos], RGB(192, 192, 192)); // 안눌림.							
					p_DC->Draw3dRect(&protocolBTN.r[pos], RGB(255, 255, 255), RGB(255, 255, 255));
					p_DC->SetTextColor(RGB(0, 0, 0));

					p_DC->DrawText(str, &protocolBTN.r[pos], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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
	unsigned int _col = 0, _row = 0;

	// Protocol button 범위 체크.	
	bool bProtocolBTN = false;
	short click_PT_BTN = -1;
	short pos = 0;

	for (int rowCnt = 0; rowCnt < protocolBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < protocolBTN.colCount; colCnt++) {
			pos = (protocolBTN.colCount * rowCnt) + colCnt;

			if (PtInRect(&protocolBTN.r[pos], point)) {
				CString str;
				str.Format(L"%s", caption.HB_BTN_Caption.at(pos).c_str());
				
				if (!str.Compare(L"*"))	return;

				try {
					_row = rowCnt;
					_col = colCnt;

					bProtocolBTN = true;
					click_PT_BTN = pos;

					int t_map_key = _row * 10 + _col;
					int port = portAddr.used_on_Protocol.find(t_map_key)->second;
					str.Format(L"%s [0x%02X]", str, port);

					// Protocol PopUp
					CDeviceProtocol *pPopUp = new CDeviceProtocol(port);
					pPopUp->Create(IDD_PROTOCOL_EXCEL_DLG);
					pPopUp->SetWindowTextW(str);
					pPopUp->ShowWindow(SW_SHOW);

					break;
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
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+