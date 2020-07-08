#pragma once

#include "GridCtrl_src_new/GridCtrl.h"

#define LEditDown_Default_1 WM_USER + 1
#define IDC_LISTCONTROL 10000
#define IDC_GRID		10001

// 그리드 컨트롤 오픈 소스를 찾아서 주석처리한 코드는 필요가 없어짐. 교육용으로 나김.
//#define Edit_and_ListControl_Sample_CODE 

// CForm_DuDefault_1 form view
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
	CGridCtrl *mp_gridctrl = NULL;

	int m_row, m_column;
	int m_fixedRowCnt, m_fixedColumnCnt;

	unsigned char *mp_setPos = NULL;

	// Excel
	_CExcelLib *pExcel;

	// 0이면 클릭은 한번도 클릭을 한적이 없다는 의미.
	//unsigned char m_buffer[32][8];
 
	// du_default 버튼들중에서 어떤 버튼을 클릭했는지 구별하기 위한 변수 1이면 du default1, 2이면 du default2, 3이면 du default3
	int m_flag = 0; 
	
#ifdef Edit_and_ListControl_Sample_CODE
private:
	CEdit **mp_cedit;
	CEdit **mp_fixedRow;
	CEdit **mp_fixedColumn;

	// Original Code
	HBRUSH mh_edit_bk_brush = NULL;
	HWND mh_old_focus = NULL;

	// fixed row, column color
	HBRUSH mh_bk_fixed_row_col = NULL;
	// normal row,  column color
	HBRUSH mh_bk_edit_row_col = NULL;

	void Clear_EditCtrl();
	void Create_EditCtrl(int a_Row, int a_Column);

#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT *);
	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT *);

	DECLARE_MESSAGE_MAP()

public:
#ifdef Edit_and_ListControl_Sample_CODE
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	afx_msg void OnCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult);
#endif	

private:
	void CellColorChange(int a_Row, int a_Column);

public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext = NULL);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedDfsDefault1();
	afx_msg void OnBnClickedDfsDefault2();
	virtual BOOL DestroyWindow();	
};


