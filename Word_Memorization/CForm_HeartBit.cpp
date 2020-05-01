// CForm_HeartBit.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CForm_HeartBit.h"


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
	// TODO: Add your specialized code here and/or call the base class

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CForm_HeartBit::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}
