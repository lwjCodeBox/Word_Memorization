#pragma once

// ********* Timer **********
#define USER_TIMER_0 30000
#define USER_TIMER_1 30001
#define USER_TIMER_2 30002
#define USER_TIMER_3 30003
// **************************

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
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext = NULL);
	virtual void OnInitialUpdate();

private:
	CEdit str_SetNode;
	CEdit str_SetWord;
	CEdit str_SetValue;

	CWordMemorizationDlg *mp_FormMainDlg;

	unsigned short m_HeartBit_0, m_HeartBit_1, m_HeartBit_2, m_HeartBit_3;

private:
	void TiemerStart(UINT ID);
	void TimerStop(UINT ID);

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);


};


