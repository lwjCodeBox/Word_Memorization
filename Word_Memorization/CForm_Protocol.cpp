// CForm_Protocol.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CForm_Protocol.h"


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
	fixCaption.xPos = 20;      // x 시작 좌표	
	fixCaption.width = 100;    // 폭 사이즈
	fixCaption.spacing_W = 20; // x 좌표 간격
	fixCaption.rowCount = 1;

	fixCaption.yPos = 20;      // y 시작 좌표	
	fixCaption.height = 25;    // 높이
	fixCaption.spacing_H = 0;  // y 좌표 간격
	fixCaption.colCount = 8;

	OnInitFixCaptionButton();

	// Init protocol Button Pos;	
	protocolBTN.xPos = 20;      // x 시작 좌표	
	protocolBTN.width = 100;    // 폭 사이즈
	protocolBTN.spacing_W = 20; // x 좌표 간격
	protocolBTN.rowCount = 1;

	protocolBTN.yPos = 50;      // y 시작 좌표	
	protocolBTN.height = 25;    // 높이
	protocolBTN.spacing_H = 0;  // y 좌표 간격
	protocolBTN.colCount = 8;

	OnInitProtocolButton();

	m_ClickedPos = new unsigned char *[protocolBTN.rowCount];

	for (int i = 0; i < protocolBTN.rowCount; i++) {
		m_ClickedPos[i] = new unsigned char[protocolBTN.colCount];
		memset(m_ClickedPos[i], 0, sizeof(unsigned char) * protocolBTN.colCount);
		
	} 

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
//--------------------------------------------------------------------------------------------

void CForm_Protocol::OnDestroy()
{
	CFormView::OnDestroy();

	// Protocol Button	
	if (m_ClickedPos != NULL) {
		for (int i = 0; i < protocolBTN.rowCount; i++) {
			delete[] m_ClickedPos[i];
			m_ClickedPos[i] = NULL;
		}
		delete[] m_ClickedPos;
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CForm_Protocol::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
}
//--------------------------------------------------------------------------------------------

void CForm_Protocol::OnPaint()
{
	CPaintDC dc(this);
	CRect r;

	OnDrawFixCaption(&dc, &r);
	OnDrawProtocolButton(&dc, &r);	
}
//--------------------------------------------------------------------------------------------

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
//--------------------------------------------------------------------------------------------

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
//--------------------------------------------------------------------------------------------

void CForm_Protocol::OnDrawFixCaption(CDC *p_DC, CRect *p_R)
{
	for (int i = 0; i < fixCaption.colCount; i++) {
		int old_mode = p_DC->SetBkMode(TRANSPARENT);

		CString str;
		str.Format(L"%s", caption.trainBTN_Caption.at(i).c_str());

		//p_DC->FillSolidRect(&fixCaption.r[i], RGB(255, 255, 128)); 
		//p_DC->Draw3dRect(&fixCaption.r[i], RGB(0, 0, 0), RGB(0, 0, 0));
		p_DC->SetTextColor(RGB(0, 0, 128));

		p_DC->DrawText(str, &fixCaption.r[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		// 배경을 이전 모드로 설정한다.
		p_DC->SetBkMode(old_mode);
	}
}
//--------------------------------------------------------------------------------------------

void CForm_Protocol::OnDrawProtocolButton(CDC *p_DC, CRect *p_R)
{
	int pos = 0;

	for (int rowCnt = 0; rowCnt < protocolBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < protocolBTN.colCount; colCnt++) {
			int old_mode = p_DC->SetBkMode(TRANSPARENT);

			pos = (protocolBTN.colCount * rowCnt) + colCnt;

			CString str;
			str.Format(L"Car0%d", colCnt);

			if (1 == m_ClickedPos[rowCnt][colCnt]) {
				p_DC->FillSolidRect(&protocolBTN.r[pos], RGB(200, 200, 100)); // 연두색
				p_DC->Draw3dRect(&protocolBTN.r[pos], RGB(0, 0, 0), RGB(200, 200, 100));
				p_DC->SetTextColor(RGB(255, 255, 255)); // 흰색

				p_DC->DrawText(str, (CRect)protocolBTN.r[pos] + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else {
				p_DC->FillSolidRect(&protocolBTN.r[pos], RGB(192, 192, 192)); // 회색
				p_DC->Draw3dRect(&protocolBTN.r[pos], RGB(192, 192, 192), RGB(0, 0, 0));
				p_DC->SetTextColor(RGB(0, 0, 0)); // 검정

				p_DC->DrawText(str, &protocolBTN.r[pos], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}

			// 배경을 이전 모드로 설정한다.
			p_DC->SetBkMode(old_mode);
		}
	}
}
//--------------------------------------------------------------------------------------------


void CForm_Protocol::OnLButtonDown(UINT nFlags, CPoint point)
{
	//std::thread t;


	CFormView::OnLButtonDown(nFlags, point);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+