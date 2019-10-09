
// Word_MemorizationDlg.h : header file
//

#pragma once

#include "_CExcelLib.h"

class _CExcelLib;
// CWordMemorizationDlg dialog
class CWordMemorizationDlg : public CDialogEx
{

public:
	_CExcelLib *mp_Libxl;
// Construction
public:
	CWordMemorizationDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORD_MEMORIZATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	
	
	CEdit m_Edit1;	
	CEdit m_Edit2;
};
