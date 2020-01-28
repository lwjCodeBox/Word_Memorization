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

	m_pBtn = new CButton * [MAX_BTN];

	for (int i = 0; i < MAX_BTN; i++)
		m_pBtn[i] = new CButton();

	CString caption = _T("");
	for (int i = 0; i < MAX_BTN; i++)
	{
		caption.Format(_T("%d Button"), i);
		m_pBtn[i]->Create(caption, WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, CRect(100, 10 + (50 * i), 100, 50 + (50 * i)), this, BTN_ID_1 + i);
	}
}

CTab1::~CTab1()
{
}

void CTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab1, CDialogEx)
END_MESSAGE_MAP()


