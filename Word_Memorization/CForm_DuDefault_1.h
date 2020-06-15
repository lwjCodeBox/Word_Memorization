#pragma once




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

	//CWordMemorizationDlg *mp_MainDlg;
	_CExcelLib *pExcel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext = NULL);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedDfsDefault1();
	afx_msg void OnBnClickedDfsDefault2();
	virtual BOOL DestroyWindow();
};


