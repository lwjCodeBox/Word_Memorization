// CTab2.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CTab2.h"
#include "afxdialogex.h"

#include "Word_MemorizationDlg.h"

// CTab2 dialog

IMPLEMENT_DYNAMIC(CTab2, CDialogEx)

CTab2::CTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CTab2::~CTab2()
{
}

void CTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListControl);
}

void CTab2::ListInitialize()
{
	// 리스트 초기화 
	m_ListControl.DeleteAllItems();

	//리스트 스타일 설정
	m_ListControl.SetExtendedStyle(LVS_EX_GRIDLINES);

	// 타이틀 삽입 
	m_ListControl.InsertColumn(0, _T("단어"), LVCFMT_LEFT, 200, -1); // 왼쪽 정렬
	m_ListControl.InsertColumn(1, _T("뜻"), LVCFMT_RIGHT, 109, -1); // 오른쪽 정렬
	m_ListControl.InsertColumn(2, _T("발음 기호"), LVCFMT_CENTER, 109, -1); // 가운데 정렬

	// Row 0 
	m_ListControl.InsertItem(0, _T("1."));
	m_ListControl.InsertItem(1, _T("2."));
	m_ListControl.InsertItem(2, _T("3."));
	m_ListControl.InsertItem(3, _T("4."));
	m_ListControl.InsertItem(4, _T("5."));

	int t_Num = m_ListControl.GetItemCount();
	
	m_editFont.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, L"굴림체");
	GetDlgItem(IDC_STATIC)->SetFont(&m_editFont);
	m_editFont.DeleteObject();

	CString str;
	str.Format(L"%d", t_Num);
	SetDlgItemText(IDC_STATIC, str);

	mp_MainDlg = (CWordMemorizationDlg*)::AfxGetMainWnd();
	for (int i = 0; i < 10; i++)
	{
		m_ListControl.SetItem(i, 1, LVIF_TEXT, mp_MainDlg->mp_Libxl->getExcelValue(i+2, 1), 0, 0, 0, NULL);
	}

	for (int i = 0; i < 10; i++)
	{
		m_ListControl.SetItem(i, 2, LVIF_TEXT, mp_MainDlg->mp_Libxl->getExcelValue(i + 2, 2), 0, 0, 0, NULL);
	}
	
/* Sample Example Code
	// 첫번째 인자는 행, 두번째 인자는 열을 의마한다. 
	m_ListControl.SetItem(0, 1, LVIF_TEXT, _T("0행 1열"), 0, 0, 0, NULL);
	m_ListControl.SetItem(1, 1, LVIF_TEXT, _T("1행 1열"), 0, 0, 0, NULL);
	m_ListControl.SetItem(2, 1, LVIF_TEXT, _T("2행 1열"), 0, 0, 0, NULL);
	m_ListControl.SetItem(3, 1, LVIF_TEXT, _T("3행 1열"), 0, 0, 0, NULL);
	m_ListControl.SetItem(4, 1, LVIF_TEXT, _T("4행 1열"), 0, 0, 0, NULL);

	m_ListControl.SetItem(0, 2, LVIF_TEXT, _T("0행 2열"), 0, 0, 0, NULL);
	m_ListControl.SetItem(1, 2, LVIF_TEXT, _T("1행 2열"), 0, 0, 0, NULL);
	m_ListControl.SetItem(2, 2, LVIF_TEXT, _T("2행 2열"), 0, 0, 0, NULL);
	m_ListControl.SetItem(3, 2, LVIF_TEXT, _T("3행 2열"), 0, 0, 0, NULL);
	m_ListControl.SetItem(4, 2, LVIF_TEXT, _T("4행 2열"), 0, 0, 0, NULL);
*/
}


BEGIN_MESSAGE_MAP(CTab2, CDialogEx)
END_MESSAGE_MAP()


// CTab2 message handlers
