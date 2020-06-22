#pragma once

#define LEditDown_Default_1 WM_USER + 1
//#define TEST_CODE

// CForm_DuDefault_1 form view
class CWordMemorizationDlg;
class _CExcelLib;
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
	CEdit **mp_cedit;
	CEdit **mp_fixedRow;
	CEdit **mp_fixedColumn;

	int m_row, m_column;
	int m_fixedRowCnt, m_fixedColumnCnt;

	unsigned char *mp_setPos = NULL;

	//CWordMemorizationDlg *mp_MainDlg;
	_CExcelLib *pExcel;

	// Original Code
	HBRUSH mh_edit_bk_brush = NULL;
	HWND mh_old_focus = NULL;

	// fixed row, column color
	HBRUSH mh_bk_fixed_row_col = NULL;
	// normal row,  column color
	HBRUSH mh_bk_edit_row_col = NULL;
	// 0이면 클릭은 한번도 클릭을 한적이 없다는 의미.
	int m_prev_clicked = 0; 
 
	// du_default 버튼들중에서 어떤 버튼을 클릭했는지 구별하기 위한 변수 1이면 du default1, 2이면 du default2, 3이면 du default3
	int m_flag = 0; 

private:
	void Clear_EditCtrl();
	void Create_EditCtrl(int a_Row, int a_Column);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext = NULL);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedDfsDefault1();
	afx_msg void OnBnClickedDfsDefault2();
	virtual BOOL DestroyWindow();
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);

protected:
	afx_msg LRESULT OnLeditdownDefault1(WPARAM wParam, LPARAM lParam); 
};


