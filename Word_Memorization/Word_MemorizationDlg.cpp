
// Word_MemorizationDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Word_Memorization.h"
#include "Word_MemorizationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWordMemorizationDlg dialog



CWordMemorizationDlg::CWordMemorizationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WORD_MEMORIZATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWordMemorizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}
BEGIN_MESSAGE_MAP(CWordMemorizationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CWordMemorizationDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CWordMemorizationDlg message handlers

BOOL CWordMemorizationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetDlgItemText(IDC_EDIT2, mp_Libxl->getExcelValue(4, 1));
	SetDlgItemText(IDC_EDIT1, mp_Libxl->getExclSheetName(0)); // 0 is means first Excel Sheet
	
	m_Tab.InsertItem(0, L"탭 1");
	m_Tab.InsertItem(1, L"탭 2");
	m_Tab.InsertItem(2, L"탭 3");

	m_Tab.SetCurSel(0);

	CRect rect;
	m_Tab.GetWindowRect(&rect);
	    
	mp_DlgTab1 = new CTab1;
	mp_DlgTab1->Create(IDD_DIALOG1, &m_Tab);
	mp_DlgTab1->MoveWindow(0, 25, rect.Width(), rect.Height());
	mp_DlgTab1->ShowWindow(SW_SHOW);

	mp_DlgTab2 = new CTab2;
	mp_DlgTab2->Create(IDD_DIALOG2, &m_Tab);
	mp_DlgTab2->MoveWindow(0, 25, rect.Width(), rect.Height());
	mp_DlgTab2->ShowWindow(SW_HIDE);

	mp_DlgTab3 = new CTab3;
	mp_DlgTab3->Create(IDD_DIALOG3, &m_Tab);
	mp_DlgTab3->MoveWindow(0, 25, rect.Width(), rect.Height());
	mp_DlgTab3->ShowWindow(SW_HIDE);

	mp_DlgTab2->ListInitialize();

	// Attach to Shared Memory
	int memSize = sizeof(TSharedMemory) * (mp_Libxl->getTotalNode() + 1); // +1 mean is MyNode.
	m_sm = new CSharedMemory(memSize);
	m_sm->Init_SharedMemory();
	m_sm->Attach();

	m_pData = (TSharedMemory*)m_sm->GetData();
	// Test
	//m_pData->data[0][0] = 0xff;
	//memset(&(m_pData->data[0][0]), 7, 1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWordMemorizationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWordMemorizationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CWordMemorizationDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	mp_Libxl = new _CExcelLib;

	return 0;
}


void CWordMemorizationDlg::OnClose()
{
	int check = MessageBox(L"정말로 종료할거얌??", L"종료 확인 메시지 창", MB_OKCANCEL | MB_ICONEXCLAMATION);
	
	if (IDCANCEL == check) 
		return; // 아니오를 클릭했을 경우 OnClose()를 빠져나옴.
	else {
		// Libxl 객체 파괴
		mp_Libxl->m_Book->release();
		delete mp_Libxl;
		mp_Libxl = NULL;

		// Tab Control 다이얼로그 객체 파괴
		if (mp_DlgTab1 != NULL)	mp_DlgTab1->DestroyWindow();
		if (mp_DlgTab2 != NULL)	mp_DlgTab2->DestroyWindow();
		if (mp_DlgTab3 != NULL) mp_DlgTab3->DestroyWindow();

		CDialogEx::OnClose();
	}
}


void CWordMemorizationDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}


BOOL CWordMemorizationDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_ESCAPE)
		{
			return true; // true면 계속해서 메시지 처리를 하지 않음.
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CWordMemorizationDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	int t_sel = m_Tab.GetCurSel();

	switch (t_sel) {
	case 0:
		mp_DlgTab1->ShowWindow(SW_SHOW);
		mp_DlgTab2->ShowWindow(SW_HIDE);
		mp_DlgTab3->ShowWindow(SW_HIDE);
		break;

	case 1:
		mp_DlgTab1->ShowWindow(SW_HIDE);
		mp_DlgTab2->ShowWindow(SW_SHOW);
		mp_DlgTab3->ShowWindow(SW_HIDE);
		break;

	case 2:
		mp_DlgTab1->ShowWindow(SW_HIDE);
		mp_DlgTab2->ShowWindow(SW_HIDE);
		mp_DlgTab3->ShowWindow(SW_SHOW);
		break;
	}

	*pResult = 0;
}


void CWordMemorizationDlg::PostNcDestroy()
{
	delete mp_DlgTab1;
	mp_DlgTab1 = NULL;

	delete mp_DlgTab2;
	mp_DlgTab2 = NULL;

	delete mp_DlgTab3;
	mp_DlgTab3 = NULL;

	CDialogEx::PostNcDestroy();
}
