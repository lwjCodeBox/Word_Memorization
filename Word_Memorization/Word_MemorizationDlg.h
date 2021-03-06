
// Word_MemorizationDlg.h : header file
//

#pragma once

#include "CTab1.h"
#include "CTab2.h"
#include "CTab3.h"

#include "_CExcelLib.h"

#include "CSharedMemory.h"

class _CExcelLib;

// CWordMemorizationDlg dialog
class CWordMemorizationDlg : public CDialogEx
{

public:
	CTab1* mp_DlgTab1;
	CTab2* mp_DlgTab2;
	CTab3* mp_DlgTab3;
	
	_CExcelLib *mp_Libxl;

	// Shared Memory
	CSharedMemory* m_sm; // For Allocating Shared Memory (Realtime Protocol)
	TSharedMemory* m_pData; // Pointer of Shared Memory (Realtime Protocol)

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
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CTabCtrl m_Tab;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void PostNcDestroy();
};
