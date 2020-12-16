#pragma once

#include "GridCtrl_src_new/GridCtrl.h"
#include "libxl.h"

#define LEditDown_Default_1 WM_USER + 1
#define IDC_LISTCONTROL 10000
#define IDC_GRID		10001

// 그리드 컨트롤 오픈 소스를 찾아서 주석처리한 코드는 필요가 없어짐. 교육용으로 나김.
//#define Edit_and_ListControl_Sample_CODE 

// CForm_DuDefault_1 form view
class _CExcelLib;
class CWordMemorizationDlg;
class CForm_DuDefault_1 : public CFormView
{
	DECLARE_DYNCREATE(CForm_DuDefault_1)

public://protected:
	CForm_DuDefault_1();           // protected constructor used by dynamic creation
	CForm_DuDefault_1(_CExcelLib *a_Libxl);
	virtual ~CForm_DuDefault_1();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_DU_DEFAULT };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	CWordMemorizationDlg *mp_MainDlg;
	CGridCtrl *mp_gridctrl = NULL;

	int m_row, m_column;
	int m_fixedRowCnt, m_fixedColumnCnt;

	// Excel
	_CExcelLib *pExcel; 
	WORD m_port = 0;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT *);
	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT *);

	DECLARE_MESSAGE_MAP()

private:

public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext = NULL);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedDfsDefault1();
	afx_msg void OnBnClickedDfsDefault2();
	virtual BOOL DestroyWindow();	
	afx_msg void OnBnClickedDfsDefault3();
};