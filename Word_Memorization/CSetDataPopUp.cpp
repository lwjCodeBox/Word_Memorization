// CSetDataPopUp.cpp: 구현 파일
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CSetDataPopUp.h"
#include "afxdialogex.h"


// CSetDataPopUp 대화 상자

IMPLEMENT_DYNAMIC(CSetDataPopUp, CDialogEx)

CSetDataPopUp::CSetDataPopUp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETDATA_POPUP, pParent)
{

}

CSetDataPopUp::CSetDataPopUp(int a_gRow, int a_gCol, WORD a_Port, BYTE a_Node, CGridCtrl *ap_Grid)
	: CDialogEx(IDD_SETDATA_POPUP, nullptr), m_gidRow(a_gRow), m_gridCol(a_gCol), m_addr(a_Port), m_node(a_Node), mp_Grid(ap_Grid)
{
	mp_This = this;
}

CSetDataPopUp::~CSetDataPopUp()
{
	
}

void CSetDataPopUp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetDataPopUp, CDialogEx)
	ON_BN_CLICKED(IDC_POPUP_CANCEL, &CSetDataPopUp::OnBnClickedPopupCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetDataPopUp::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSetDataPopUp 메시지 처리기


void CSetDataPopUp::OnBnClickedPopupCancel()
{
	mp_This->DestroyWindow();
	delete mp_This;
	mp_This = NULL;
}


void CSetDataPopUp::OnBnClickedButton1()
{
	WORD  data = GetDlgItemInt(IDC_POPUP_EDIT);
	_GFG::_GFG_SetMergeData(m_gidRow, m_gridCol, data, m_addr, m_node, mp_Grid);

	OnBnClickedPopupCancel();
}


void CSetDataPopUp::OnOK()
{
	OnBnClickedButton1();
}
