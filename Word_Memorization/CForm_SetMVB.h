#pragma once

#include "GridCtrl_src_new/GridCtrl.h"

// ********* Timer **********
#define USER_TIMER_0 30000
#define USER_TIMER_1 30001
#define USER_TIMER_2 30002
#define USER_TIMER_3 30003
// **************************

#define IDC_GFG_GRID 10002

// CForm_SetMVB form view
class CWordMemorizationDlg;
class CForm_SetMVB : public CFormView
{
	DECLARE_DYNCREATE(CForm_SetMVB)

public://protected:
	CForm_SetMVB();           // protected constructor used by dynamic creation
	virtual ~CForm_SetMVB();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_SETMVB };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext &dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	afx_msg void On_GFG_GridClick(NMHDR *pNotifyStruct, LRESULT *);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext = NULL);
	virtual void OnInitialUpdate();

private:
	CEdit str_SetAddr;
	CEdit str_SetWord;
	CEdit str_SetValue;

	CWordMemorizationDlg *mp_FormMainDlg;

	CGridCtrl *mp_ScrSetMVB_Grid = NULL;

	unsigned short m_HeartBit_0, m_HeartBit_1, m_HeartBit_2, m_HeartBit_3;


	// Timer value
	WORD number_00;
	WORD hb_00 = 0;

	WORD number_01;
	WORD hb_01 = 0;

	WORD number_02;
	WORD hb_02 = 0;

	WORD number_03;
	WORD hb_03 = 0;

private:
	void TiemerStart(UINT ID);
	void TimerStop(UINT ID);

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);


	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
};


