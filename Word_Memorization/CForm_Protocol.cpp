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
	// TODO: Add your specialized code here and/or call the base class

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CForm_Protocol::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}
