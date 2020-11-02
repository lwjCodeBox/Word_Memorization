#pragma once

#include "DefineOfDev_J.h"

#include <iostream>
#include <thread>

// CForm_HeartBit form view

class CForm_HeartBit : public CFormView
{
	DECLARE_DYNCREATE(CForm_HeartBit)

public://protected:
	CForm_HeartBit();           // protected constructor used by dynamic creation
	virtual ~CForm_HeartBit();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_HEARTBIT };
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
	unsigned char **m_HB_ClickedPos = NULL;
	
	TCaption caption;

	TButtonRect fixCaption;
	TButtonRect heartBitBTN;

	int m_thread_count = 0;

private:
	void OnInitFixCaptionButton();
	void OnInitHeartBitButton();

	void OnDrawFixCaption(CDC *p_DC, CRect *p_R);
	void OnDrawHeartBitButton(CDC *p_DC, CRect *p_R);

	// thread start, stop
	void Thread_Start();
	void Thread_stop();

public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext = NULL);
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

protected:
	afx_msg LRESULT On27001(WPARAM wParam, LPARAM lParam);
};


