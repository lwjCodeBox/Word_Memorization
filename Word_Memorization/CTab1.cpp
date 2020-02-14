// CTab1.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CTab1.h"
#include "afxdialogex.h"


// CTab1 dialog

IMPLEMENT_DYNAMIC(CTab1, CDialogEx)

CTab1::CTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_pBtn = NULL;

	/*m_pBtn = new CButton * [MAX_BTN];

	CString caption = _T("");
	for (int i = 0; i < MAX_BTN; i++)
	{
		m_pBtn[i] = new CButton();
		caption.Format(_T("%d Button"), i);
		m_pBtn[i]->Create(caption, WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, CRect(10, 10 + (50 * i), 100, 50 + (50 * i)), this, BTN_ID_1 + i);
	}*/
	
}

CTab1::~CTab1()
{
	if (m_pBtn != NULL)
	{
		for (int i = 0; i < MAX_BTN; i++)
		{
			delete m_pBtn[i];
			m_pBtn[i] = NULL;
		}
		delete[] m_pBtn;
	}
}

void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab1, CDialogEx)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


void CTab1::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	m_pBtn = new CButton * [MAX_BTN];

	CString caption = _T("");
	for (int i = 0; i < MAX_BTN; i++)
	{
		m_pBtn[i] = new CButton();
		caption.Format(_T("%d Button"), i);
		m_pBtn[i]->Create(caption, WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, CRect(10, 10 + (50 * i), 100, 50 + (50 * i)), this, BTN_ID_1 + i);
	}
}
