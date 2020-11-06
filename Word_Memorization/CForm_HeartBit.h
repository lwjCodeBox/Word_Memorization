#pragma once

#include <iostream>

#include "DefineOfDev_J.h"
#include "Thread/Multi_Thread.h"

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
		
	//today-del
	//int m_thread_count = -1; // -1의 의미는 스레드를 하나라도 생성하지 않았다는 의미이다.

public: 
	TMVB_Addr_Info portAddr;
	TDataPtr dataPtr;

private:
	void OnInitFixCaptionButton();
	void OnInitHeartBitButton();

	void OnDrawFixCaption(CDC *p_DC, CRect *p_R);
	void OnDrawHeartBitButton(CDC *p_DC, CRect *p_R);

	// thread start, stop
	void Thread_Start(int a_row, int a_col);
	void Thread_stop(int a_row, int a_col);
	void Thread_Allstop();

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


