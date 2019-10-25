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
	// ����Ʈ �ʱ�ȭ 
	m_ListControl.DeleteAllItems();

	//����Ʈ ��Ÿ�� ����
	m_ListControl.SetExtendedStyle(LVS_EX_GRIDLINES);

	// Ÿ��Ʋ ���� 
	m_ListControl.InsertColumn(0, _T("�ܾ�"), LVCFMT_LEFT, 200, -1); // ���� ����
	m_ListControl.InsertColumn(1, _T("��"), LVCFMT_RIGHT, 109, -1); // ������ ����
	m_ListControl.InsertColumn(2, _T("���� ��ȣ"), LVCFMT_CENTER, 109, -1); // ��� ����

	// Row 0 
	m_ListControl.InsertItem(0, _T("1."));
	m_ListControl.InsertItem(1, _T("2."));
	m_ListControl.InsertItem(2, _T("3."));
	m_ListControl.InsertItem(3, _T("4."));
	m_ListControl.InsertItem(4, _T("5."));

	int t_Num = m_ListControl.GetItemCount();
	
	m_editFont.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, L"����ü");
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
	// ù��° ���ڴ� ��, �ι�° ���ڴ� ���� �Ǹ��Ѵ�. 
	m_ListControl.SetItem(0, 1, LVIF_TEXT, _T("0�� 1��"), 0, 0, 0, NULL);
	m_ListControl.SetItem(1, 1, LVIF_TEXT, _T("1�� 1��"), 0, 0, 0, NULL);
	m_ListControl.SetItem(2, 1, LVIF_TEXT, _T("2�� 1��"), 0, 0, 0, NULL);
	m_ListControl.SetItem(3, 1, LVIF_TEXT, _T("3�� 1��"), 0, 0, 0, NULL);
	m_ListControl.SetItem(4, 1, LVIF_TEXT, _T("4�� 1��"), 0, 0, 0, NULL);

	m_ListControl.SetItem(0, 2, LVIF_TEXT, _T("0�� 2��"), 0, 0, 0, NULL);
	m_ListControl.SetItem(1, 2, LVIF_TEXT, _T("1�� 2��"), 0, 0, 0, NULL);
	m_ListControl.SetItem(2, 2, LVIF_TEXT, _T("2�� 2��"), 0, 0, 0, NULL);
	m_ListControl.SetItem(3, 2, LVIF_TEXT, _T("3�� 2��"), 0, 0, 0, NULL);
	m_ListControl.SetItem(4, 2, LVIF_TEXT, _T("4�� 2��"), 0, 0, 0, NULL);
*/
}


BEGIN_MESSAGE_MAP(CTab2, CDialogEx)
END_MESSAGE_MAP()


// CTab2 message handlers
