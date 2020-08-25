
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
}
BEGIN_MESSAGE_MAP(CWordMemorizationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND_RANGE(IDC_SELECTED_CAR_0, IDC_SELECTED_CAR_7, SelectedCar)
	ON_COMMAND_RANGE(IDC_SCREEN_PROTOCOL_BTN00, IDC_SCREEN_SETMVB_BNT04, ChangeScreen)	
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

	// Attach to Shared Memory
	int memSize = sizeof(TSharedMemory) * 5;// 488;//sizeof(TSharedMemory) * (mp_Libxl->getTotalNode() + 1); // +1 mean is MyNode. // Original code
	m_sm = new CSharedMemory(memSize);
	m_sm->Init_SharedMemory();
	m_sm->Attach();

	m_pData = (TSharedMemory*)m_sm->GetData();
	
	mp_Libxl->Load_logical_Port_Adrs();

	nodeData.node = 1;
	CreateForm();

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

		CDialogEx::OnClose();
	}
}


void CWordMemorizationDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (mp_Form_Protocol != NULL)
	{
		mp_Form_Protocol->DestroyWindow();
	}

	if (mp_Form_HeartBit != NULL)
	{
		mp_Form_HeartBit->DestroyWindow();
	}

	if (mp_Form_DuDefault_1 != NULL)
	{
		mp_Form_DuDefault_1->DestroyWindow();
	}

	if (mp_Form_SetMVB != NULL)
	{
		mp_Form_SetMVB->DestroyWindow();
	}
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

// 화면 전환
void CWordMemorizationDlg::ChangeScreen(UINT ID)
{
	CString msg = _T("");

	switch (ID - IDC_SCREEN_PROTOCOL_BTN00)
	{
	case 0:
		AfxMessageBox(L"Protocol");
		mp_Form_Protocol->ShowWindow(SW_SHOW);
		mp_Form_HeartBit->ShowWindow(SW_HIDE);
		mp_Form_DuDefault_1->ShowWindow(SW_HIDE);
		mp_Form_SetMVB->ShowWindow(SW_HIDE);
		break;

	case 1:
		AfxMessageBox(L"Heartbit");
		mp_Form_Protocol->ShowWindow(SW_HIDE);
		mp_Form_HeartBit->ShowWindow(SW_SHOW);
		mp_Form_DuDefault_1->ShowWindow(SW_HIDE);
		mp_Form_SetMVB->ShowWindow(SW_HIDE);
		break;

	case 2:
		AfxMessageBox(L"My Node");
		//SetMVBValue(0, 0, 1);
		break;

	case 3:
		mp_Form_Protocol->ShowWindow(SW_HIDE);
		mp_Form_HeartBit->ShowWindow(SW_HIDE);

		mp_Form_DuDefault_1->ShowWindow(SW_SHOW);
		mp_Form_DuDefault_1->OnBnClickedDfsDefault1();
		
		mp_Form_SetMVB->ShowWindow(SW_HIDE);
		break;

	case 4:
		//AfxMessageBox(L"Set MVB");
		mp_Form_Protocol->ShowWindow(SW_HIDE);
		mp_Form_HeartBit->ShowWindow(SW_HIDE);
		mp_Form_DuDefault_1->ShowWindow(SW_HIDE);
		mp_Form_SetMVB->ShowWindow(SW_SHOW);
		break;
	}

	
}

// 차량 선택
void CWordMemorizationDlg::SelectedCar(UINT ID)
{
	CString msg = _T("");

	// aDTC, aMC1 이면 노드가 0인데 여기서는 myNode 계산 때문에 0이면 myNode를 의미 하고 1이면 0번 노드를 말함. (원래 노드에서 +1을 함)
	switch (ID - IDC_SELECTED_CAR_0)
	{
	case 0:
		nodeData.node = 1; 

		msg.Format(L"Car %d Port >> %d", ID - IDC_SELECTED_CAR_0, nodeData.node);
		//AfxMessageBox(msg);

		memset(&(m_pData->data[0][0]), 0x0f, 1);
		break;

	case 1:
		nodeData.node = 1;

		msg.Format(L"Car %d Port >> %d", ID - IDC_SELECTED_CAR_0, nodeData.node);
		//AfxMessageBox(msg);

		memset(&(m_pData->data[0][1]), 0xaa, 1);
		break;

	case 2:
		nodeData.node = 2;

		msg.Format(L"Car %d Port >> %d", ID - IDC_SELECTED_CAR_0, nodeData.node);
		AfxMessageBox(msg);
		break;

	case 3:
		nodeData.node = 2;

		msg.Format(L"Car %d Port >> %d", ID - IDC_SELECTED_CAR_0, nodeData.node);
		AfxMessageBox(msg);
		break;

	case 4:
		nodeData.node = 3;

		msg.Format(L"Car %d Port >> %d", ID - IDC_SELECTED_CAR_0, nodeData.node);
		AfxMessageBox(msg);
		break;

	case 5:
		nodeData.node = 3;

		msg.Format(L"Car %d Port >> %d", ID - IDC_SELECTED_CAR_0, nodeData.node);
		AfxMessageBox(msg);
		break;

	case 6:
		nodeData.node = 4;

		msg.Format(L"Car %d Port >> %d", ID - IDC_SELECTED_CAR_0, nodeData.node);
		AfxMessageBox(msg);
		break;

	case 7:
		nodeData.node = 4;

		msg.Format(L"Car %d Port >> %d", ID - IDC_SELECTED_CAR_0, nodeData.node);
		AfxMessageBox(msg);
		break;
	}
}


void CWordMemorizationDlg::CreateForm()
{
	CCreateContext context;
	ZeroMemory(&context, sizeof(context));

	CRect panelArea;

	GetDlgItem(IDC_STATIC_NOTEBOOKSCREEN)->GetWindowRect(&panelArea);
	ScreenToClient(&panelArea);
	
	mp_Form_Protocol = new CForm_Protocol();
	mp_Form_Protocol->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, panelArea, this, IDC_SCREEN_PROTOCOL_BTN00, &context);
	mp_Form_Protocol->OnInitialUpdate();
	mp_Form_Protocol->ShowWindow(SW_SHOW);

	mp_Form_HeartBit = new CForm_HeartBit();
	mp_Form_HeartBit->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, panelArea, this, IDC_SCREEN_HEARTBIT_BTN01, &context);
	mp_Form_HeartBit->OnInitialUpdate();
	mp_Form_HeartBit->ShowWindow(SW_HIDE);

	mp_Form_DuDefault_1 = new CForm_DuDefault_1(mp_Libxl);
	mp_Form_DuDefault_1->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, panelArea, this, IDC_SCREEN_DUDEFAULT_BTN03, &context);
	mp_Form_DuDefault_1->OnInitialUpdate();
	mp_Form_DuDefault_1->ShowWindow(SW_HIDE);

	mp_Form_SetMVB = new CForm_SetMVB();
	mp_Form_SetMVB->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, panelArea, this, IDC_SCREEN_SETMVB_BNT04, &context);
	//mp_Form_SetMVB->OnInitialUpdate();
	mp_Form_SetMVB->ShowWindow(SW_HIDE);
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::SetMVBValue(unsigned int a_Node, unsigned int a_Port, unsigned int a_Value)
{
	memset(&(m_pData->data[a_Node][a_Port]), a_Value, 1);
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::SetMVBHeartBit(unsigned int a_Port, unsigned int a_Value)
{
	memset(&(m_pData->data[a_Port][0]), a_Value, 2);
}
//--------------------------------------------------------------------------------------------

WORD CWordMemorizationDlg::GetWordDataFromSM(WORD a_PortAddr, BYTE a_Node, BYTE a_Word)
{
	WORD data = 0;

	int port = binarySearch(mp_Libxl->mvb_Addr, 120, a_PortAddr); // 120의 의미는 myNode의 총 갯수를 의미 한다. 계산 법은 다음과 같다. // int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
	port += mp_Libxl->m_totalNodeCnt * a_Node;
	memcpy(&data, &(m_pData->data[port][a_Word * 2]), 2);

	WORD result;
	((unsigned char *)&result)[0] = data >> 8;
	((unsigned char *)&result)[1] = data & 0xFF;
	
	return result;
}
//--------------------------------------------------------------------------------------------

BYTE CWordMemorizationDlg::GetByteDataFromSM(WORD a_PortAddr, BYTE a_Node, BYTE a_Byte)
{
	BYTE data = 0;

	int port = binarySearch(mp_Libxl->mvb_Addr, 120, a_PortAddr); // 120의 의미는 myNode의 총 갯수를 의미 한다. 계산 법은 다음과 같다. // int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
	port += mp_Libxl->m_totalNodeCnt * a_Node;
	memcpy(&data, &(m_pData->data[port][a_Byte]), 1);

	return data;
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::SetBitDataToSM(WORD a_PortAddr, BYTE a_Node, BYTE a_Word, BYTE a_ColPos, WORD a_Data)
{
	int port = binarySearch(mp_Libxl->mvb_Addr, 120, a_PortAddr); // 120의 의미는 myNode의 총 갯수를 의미 한다. 계산 법은 다음과 같다. // int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
	port += mp_Libxl->m_totalNodeCnt * a_Node;

	WORD lsh = 0x01 << a_ColPos;
	WORD data = a_Data;
	data = data ^ lsh;

	m_pData->data[port][a_Word * 2    ] = data >> 8;   // 상위
	m_pData->data[port][a_Word * 2 + 1] = data & 0xFF; // 하위

	//WORD result;
	//((unsigned char *)&result)[1] = m_pData->data[port][a_Word * 2];     // 상위
	//((unsigned char *)&result)[0] = m_pData->data[port][a_Word * 2 + 1]; // 하위
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::Set16DataToSM(WORD a_PortAddr, BYTE a_Node, BYTE a_Word, WORD a_Data)
{
	int port = binarySearch(mp_Libxl->mvb_Addr, 120, a_PortAddr); // 120의 의미는 myNode의 총 갯수를 의미 한다. 계산 법은 다음과 같다. // int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
	port += mp_Libxl->m_totalNodeCnt * a_Node;

	memset(&(m_pData->data[port][a_Word * 2]), a_Data >> 8, 1); // 상위
	memset(&(m_pData->data[port][a_Word * 2 + 1]), a_Data & 0xFF, 1); // 하위
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::Set08DataToSM(WORD a_PortAddr, BYTE a_Node, BYTE a_Word, bool a_Pos, BYTE a_Data)
{
	int port = binarySearch(mp_Libxl->mvb_Addr, 120, a_PortAddr); // 120의 의미는 myNode의 총 갯수를 의미 한다. 계산 법은 다음과 같다. // int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
	port += mp_Libxl->m_totalNodeCnt * a_Node;
	
	if (!a_Pos)
		memset(&(m_pData->data[port][a_Word * 2]), a_Data, 1);
	else
		memset(&(m_pData->data[port][a_Word * 2 + 1]), a_Data, 1);
}
//--------------------------------------------------------------------------------------------

