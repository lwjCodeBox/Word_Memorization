#pragma once

#include "GridCtrl_src_new/GridCtrl.h"
#include "Grid_Func_Group.h"

// CSetDataPopUp 대화 상자

class CSetDataPopUp : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDataPopUp)

public:
	CSetDataPopUp(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	CSetDataPopUp(int a_gRow, int a_gCol, WORD a_Port, BYTE a_Node, CGridCtrl *ap_Grid);   // 내가 만든 생성자입니다.

	virtual ~CSetDataPopUp();


public:
	int m_gidRow, m_gridCol;
	WORD m_addr;
	BYTE m_node;
	CGridCtrl *mp_Grid;
	CSetDataPopUp *mp_This;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETDATA_POPUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPopupCancel();
	afx_msg void OnBnClickedButton1();
	virtual void OnOK();
};
