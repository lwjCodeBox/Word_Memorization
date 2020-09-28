#pragma once

#include "DefineOfDev_J.h"

#include <iostream>
#include <thread>

// CForm_Protocol form view

class CForm_Protocol : public CFormView
{
	DECLARE_DYNCREATE(CForm_Protocol)

public://protected:
	CForm_Protocol();           // protected constructor used by dynamic creation
	virtual ~CForm_Protocol();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_PROTOCOL };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:	
	// 어떤 버튼을 클릭 했는지 정보를 담고 있는 변수
	unsigned char **m_ClickedPos = NULL;

	TCaption caption;
	
	TButtonRect fixCaption;
	TButtonRect protocolBTN;

private:
	void OnInitFixCaptionButton();
	void OnInitProtocolButton();

	void OnDrawFixCaption(CDC *p_DC, CRect *p_R);
	void OnDrawProtocolButton(CDC *p_DC, CRect *p_R);

public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext = NULL);
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};


