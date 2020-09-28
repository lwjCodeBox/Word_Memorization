
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
	ON_COMMAND_RANGE(IDC_SCREEN_PROTOCOL_BTN00, IDC_SCREEN_SETMVB_BNT04, ChangeScreen)	
	ON_WM_DRAWITEM()
	ON_WM_LBUTTONDOWN()
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

//--------------------------------------------------------------------------------------------
	// Init Train Button Pos;	
	m_trainBTN.xPos = 40;      // x 시작 좌표	
	m_trainBTN.width = 100;    // 폭 사이즈
	m_trainBTN.spacing_W = 20; // x 좌표 간격
	m_trainBTN.rowCount = 1;

	m_trainBTN.yPos = 20;      // y 시작 좌표	
	m_trainBTN.height = 25;    // 높이
	m_trainBTN.spacing_H = 0;  // y 좌표 간격
	m_trainBTN.colCount = 8;

	OnInitTrainButton();

	m_ClickedCarPos = new unsigned char * [m_trainBTN.rowCount];
	
	for (int i = 0; i < m_trainBTN.rowCount; i++) {
		m_ClickedCarPos[i] = new unsigned char[m_trainBTN.colCount];
		memset(m_ClickedCarPos[i], 0, sizeof(unsigned char) * m_trainBTN.colCount);		
		//for (int j = 0; j < m_trainBTN.colCount; j++)   m_ClickedCarPos[i][j] = 0;
	}	

	// Init Screen Button Pos;
	m_scrBTN.xPos = 1110;      // x 시작 좌표	
	m_scrBTN.width = 100;    // 폭 사이즈
	m_scrBTN.spacing_W = 0; // x 좌표 간격
	m_scrBTN.rowCount = 5;

	m_scrBTN.yPos = 80;      // y 시작 좌표	
	m_scrBTN.height = 25;    // 높이
	m_scrBTN.spacing_H = 5;  // y 좌표 간격
	m_scrBTN.colCount = 1;

	OnInitScreenButton();

	m_ClickedScreenPos = new unsigned char * [m_scrBTN.rowCount];

	for (int i = 0; i < m_scrBTN.rowCount; i++) {
		m_ClickedScreenPos[i] = new unsigned char[m_scrBTN.colCount];
		memset(m_ClickedScreenPos[i], 0, sizeof(unsigned char) * m_scrBTN.colCount);
	}		
//--------------------------------------------------------------------------------------------

	return TRUE;  // return TRUE  unless you set the focus to a control
}
//--------------------------------------------------------------------------------------------

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
		CPaintDC dc(this);
		CRect r;

		OnDrawTrainButton(&dc, &r);
		OnDrawScreenButton(&dc, &r);

		//CDialogEx::OnPaint();
	}
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::OnInitTrainButton()
{	
	m_trainBTN.r.clear();

	RECT r;
	for (int rowCnt = 0; rowCnt < m_trainBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < m_trainBTN.colCount; colCnt++) {
			r.left = m_trainBTN.xPos + colCnt * (m_trainBTN.width + m_trainBTN.spacing_W);
			r.right = r.left + m_trainBTN.width;
			r.top = m_trainBTN.yPos + rowCnt * (m_trainBTN.height + m_trainBTN.spacing_H);
			r.bottom = r.top + m_trainBTN.height;

			m_trainBTN.r.push_back(r);			
		}
	}
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::OnInitScreenButton()
{
	m_scrBTN.r.clear();

	RECT r;
	for (int rowCnt = 0; rowCnt < m_scrBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < m_scrBTN.colCount; colCnt++) {			
			r.left = m_scrBTN.xPos + colCnt * (m_scrBTN.width + m_scrBTN.spacing_W);
			r.right = r.left + m_scrBTN.width;
			r.top = m_scrBTN.yPos + rowCnt * (m_scrBTN.height + m_scrBTN.spacing_H);
			r.bottom = r.top + m_scrBTN.height;

			m_scrBTN.r.push_back(r);					
		}
	}
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::OnDrawTrainButton(CDC *p_DC, CRect *p_R)
{
	int pos = 0;

	for (int rowCnt = 0; rowCnt < m_trainBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < m_trainBTN.colCount; colCnt++) {
			int old_mode = p_DC->SetBkMode(TRANSPARENT);
						
			pos = (m_trainBTN.colCount * rowCnt) + colCnt;
			
			CString str;
			str.Format(L"Car0%d (%s)", colCnt, caption.trainBTN_Caption.at(colCnt).c_str());

			if (1 == m_ClickedCarPos[rowCnt][colCnt]) {
				p_DC->FillSolidRect(&m_trainBTN.r[pos], RGB(200, 200, 100)); // 연두색
				p_DC->Draw3dRect(&m_trainBTN.r[pos], RGB(0, 0, 0), RGB(200, 200, 100));
				p_DC->SetTextColor(RGB(255, 255, 255)); // 흰색

				p_DC->DrawText(str, (CRect)m_trainBTN.r[pos] + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else {				
				p_DC->FillSolidRect(&m_trainBTN.r[pos], RGB(192, 192, 192)); // 회색
				p_DC->Draw3dRect(&m_trainBTN.r[pos], RGB(192, 192, 192), RGB(0, 0, 0));
				p_DC->SetTextColor(RGB(0, 0, 0)); // 검정

				p_DC->DrawText(str, &m_trainBTN.r[pos], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}

			// 배경을 이전 모드로 설정한다.
			p_DC->SetBkMode(old_mode);
		}
	}	
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::OnDrawScreenButton(CDC *p_DC, CRect *p_R)
{
	int pos = 0;

	for (int rowCnt = 0; rowCnt < m_scrBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < m_scrBTN.colCount; colCnt++) {
			int old_mode = p_DC->SetBkMode(TRANSPARENT);
			
			CString str;
			str.Format(L"%s", caption.srcBTN_Caption.at(rowCnt).c_str());			

			pos = (m_scrBTN.colCount * rowCnt) + colCnt;

			if (1 == m_ClickedScreenPos[rowCnt][colCnt]) {
				p_DC->FillSolidRect(&m_scrBTN.r[pos], RGB(200, 200, 100)); // 연두색
				p_DC->Draw3dRect(&m_scrBTN.r[pos], RGB(0, 0, 0), RGB(200, 200, 100));
				p_DC->SetTextColor(RGB(255, 255, 255)); // 흰색

				p_DC->DrawText(str, (CRect)m_scrBTN.r[pos] + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else {
				p_DC->FillSolidRect(&m_scrBTN.r[pos], RGB(192, 192, 192)); // 회색
				p_DC->Draw3dRect(&m_scrBTN.r[pos], RGB(192, 192, 192), RGB(0, 0, 0));
				p_DC->SetTextColor(RGB(0, 0, 0)); // 검정

				p_DC->DrawText(str, &m_scrBTN.r[pos], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}

			// 배경을 이전 모드로 설정한다.
			p_DC->SetBkMode(old_mode);
		}
	}
}
//--------------------------------------------------------------------------------------------

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
//--------------------------------------------------------------------------------------------

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
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// Train Button	
	if (m_ClickedCarPos != NULL) {
		for (int i = 0; i < m_trainBTN.rowCount; i++) {			
			delete[] m_ClickedCarPos[i];
			m_ClickedCarPos[i] = NULL;
		}
		delete[] m_ClickedCarPos;		
	}
	
	// Screen Button
	if (m_ClickedScreenPos != NULL) {
		for (int i = 0; i < m_scrBTN.rowCount; i++) {
			delete[] m_ClickedScreenPos[i];
			m_ClickedScreenPos[i] = NULL;
		}
		delete[] m_ClickedScreenPos;
	}

	m_trainBTN.r.clear();
	m_scrBTN.r.clear();

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
//--------------------------------------------------------------------------------------------

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
//--------------------------------------------------------------------------------------------

// 화면 전환
void CWordMemorizationDlg::ChangeScreen(UINT ID)
{
	CString msg = _T("");

	switch (ID)
	{
	case 0: // Protocol
		mp_Form_Protocol->ShowWindow(SW_SHOW);
		mp_Form_HeartBit->ShowWindow(SW_HIDE);
		mp_Form_DuDefault_1->ShowWindow(SW_HIDE);
		mp_Form_SetMVB->ShowWindow(SW_HIDE);
		break;

	case 1: // Heartbit
		mp_Form_Protocol->ShowWindow(SW_HIDE);
		mp_Form_HeartBit->ShowWindow(SW_SHOW);
		mp_Form_DuDefault_1->ShowWindow(SW_HIDE);
		mp_Form_SetMVB->ShowWindow(SW_HIDE);
		break;

	case 2: // DU Default
		mp_Form_Protocol->ShowWindow(SW_HIDE);
		mp_Form_HeartBit->ShowWindow(SW_HIDE);

		mp_Form_DuDefault_1->ShowWindow(SW_SHOW);
		mp_Form_DuDefault_1->OnBnClickedDfsDefault1();

		mp_Form_SetMVB->ShowWindow(SW_HIDE);
		break;

	case 3: // My Node
		//SetMVBValue(0, 0, 1);
		break;

	case 4: // Set MVB
		mp_Form_Protocol->ShowWindow(SW_HIDE);
		mp_Form_HeartBit->ShowWindow(SW_HIDE);
		mp_Form_DuDefault_1->ShowWindow(SW_HIDE);
		mp_Form_SetMVB->ShowWindow(SW_SHOW);
		break;
	}

	
}
//--------------------------------------------------------------------------------------------

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

void CWordMemorizationDlg::SetMVBHeartBit15(unsigned int a_Port, unsigned int a_Value)
{
	memset(&(m_pData->data[a_Port][30]), a_Value, 2);
}
//--------------------------------------------------------------------------------------------

WORD CWordMemorizationDlg::GetWordDataFromSM(WORD a_PortAddr, BYTE a_Node, BYTE a_WordPos)
{
	WORD data = 0;

	int port = binarySearch(mp_Libxl->mvb_Addr, 120, a_PortAddr); // 120의 의미는 myNode의 총 갯수를 의미 한다. 계산 법은 다음과 같다. // int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
	port += mp_Libxl->m_totalNodeCnt * a_Node;
	memcpy(&data, &(m_pData->data[port][a_WordPos * 2]), 2);

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
		
	if (!a_Pos) // 0이면 상위(false), 1이면 하위(true) 		
		memset(&(m_pData->data[port][a_Word * 2]), a_Data, 1); // 상위
	else 
		memset(&(m_pData->data[port][a_Word * 2 + 1]), a_Data, 1); // 하위
}
//--------------------------------------------------------------------------------------------


void CWordMemorizationDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=645
	
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

/* 동적으로 직접 버튼을 생성할 경우는 이 부분이 꼭 필요하다.
		https://mutaont.tistory.com/entry/MFC-%EB%B2%84%ED%8A%BC-%EC%83%89%EC%83%81-%EB%B3%80%EA%B2%BD
	UINT uStyle = DFCS_BUTTONPUSH;
	if (lpDrawItemStruct->itemState & ODS_SELECTED)	uStyle |= DFCS_PUSHED;
	::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, DFC_BUTTON, uStyle);*/

/*
// Button
pDC->DrawFrameControl(m_oldRect, DFC_BUTTON, DFCS_BUTTONPUSH);
// CheckBox
pDC->DrawFrameControl(m_oldRect, DFC_BUTTON, DFCS_BUTTONCHECK);
// RadioButton
pDC->DrawFrameControl(m_oldRect, DFC_BUTTON, DFCS_BUTTONRADIO);
// EditBox
그냥 사각형으로 ?
// ComboBox
사각형 + pDC->DrawFrameControl(m_oldRect, DFC_SCROLL, DFCS_SCROLLCOMBOBOX);

버튼 위에 글쓸때 투명하게...
pDC->SetBkMode(TRANSPARENT);


출처: https://elkeipy.tistory.com/entry/DrawFrameControl [케이피's 불량블로그!]
*/

void CWordMemorizationDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	unsigned int _col = 0, _row = 0;
	
	// train button 범위 체크.	
	bool bTrainBTN = false;	
	char selectTrainBTN = -1;
	for (int i = 0; i < m_trainBTN.colCount; i++) {
		if (PtInRect(&m_trainBTN.r[i], point)/*m_trainBTN.r[i].PtInRect(point)*/) {
			bTrainBTN = true;
			selectTrainBTN = i;
			break;
		}
	}
	
	// screen button 범위 체크.
	bool bScrBTN = false;
	char selectScrBTN = -1;
	for (int i = 0; i < m_scrBTN.rowCount; i++) {
		if (PtInRect(&m_scrBTN.r[i], point)/*m_scrBTN.r[i].PtInRect(point)*/) {			
			bScrBTN = true;
			selectScrBTN = i;
			break;
		}		
	}

	// train button
	if (bTrainBTN) {
		CClientDC dc(this);

		int old_mode = dc.SetBkMode(TRANSPARENT);
		CString str;
		str.Format(L"Car0%d (%s)", selectTrainBTN, caption.trainBTN_Caption.at(selectTrainBTN).c_str());

		if (1 == m_ClickedCarPos[_row][selectTrainBTN]) {
			m_ClickedCarPos[_row][selectTrainBTN] = 0;

			dc.FillSolidRect(&m_trainBTN.r[selectTrainBTN], RGB(192, 192, 192)); // 회색
			dc.Draw3dRect(&m_trainBTN.r[selectTrainBTN], RGB(192, 192, 192), RGB(0, 0, 0));
			dc.SetTextColor(RGB(0, 0, 0)); // 검정
			dc.DrawText(str, &m_trainBTN.r[selectTrainBTN], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else {
			// 이전에 클릭했던 버튼이 있다면...
			if (m_oldClickedCarBTN != -1) {
				int t_old_mode = dc.SetBkMode(TRANSPARENT);
				
				CString t_str;
				t_str.Format(L"Car0%d (%s)", m_oldClickedCarBTN, caption.trainBTN_Caption.at(m_oldClickedCarBTN).c_str());

				m_ClickedCarPos[_row][m_oldClickedCarBTN] = 0;

				dc.FillSolidRect(&m_trainBTN.r[m_oldClickedCarBTN], RGB(192, 192, 192)); // 회색
				dc.Draw3dRect(&m_trainBTN.r[m_oldClickedCarBTN], RGB(192, 192, 192), RGB(0, 0, 0));
				dc.SetTextColor(RGB(0, 0, 0)); // 검정
				dc.DrawText(t_str, &m_trainBTN.r[m_oldClickedCarBTN], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				dc.SetBkMode(t_old_mode);
			}

			m_ClickedCarPos[0][selectTrainBTN] = 1;

			dc.FillSolidRect(&m_trainBTN.r[selectTrainBTN], RGB(100, 200, 200)); // 하늘색
			dc.Draw3dRect(&m_trainBTN.r[selectTrainBTN], RGB(0, 0, 0), RGB(100, 200, 200));
			dc.SetTextColor(RGB(255, 255, 255)); // 흰색
			dc.DrawText(str, (CRect)m_trainBTN.r[selectTrainBTN] + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			
			m_oldClickedCarBTN = selectTrainBTN;
		}

		// 배경을 이전 모드로 설정한다.
		dc.SetBkMode(old_mode);		
	}
	else if (bScrBTN) {
		CClientDC dc(this);

		int old_mode = dc.SetBkMode(TRANSPARENT);
		
		CString str;
		str.Format(L"%s", caption.srcBTN_Caption.at(selectScrBTN).c_str());

		if (1 == m_ClickedScreenPos[selectScrBTN][_col]) {
			m_ClickedScreenPos[selectScrBTN][_col] = 0;

			dc.FillSolidRect(&m_scrBTN.r[selectScrBTN], RGB(192, 192, 192)); // 회색
			dc.Draw3dRect(&m_scrBTN.r[selectScrBTN], RGB(192, 192, 192), RGB(0, 0, 0));
			dc.SetTextColor(RGB(0, 0, 0)); // 검정
			dc.DrawText(str, &m_scrBTN.r[selectScrBTN], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else {
			// 이전에 클릭했던 버튼이 있다면...
			if (m_oldClickedScrBTN != -1) {
				int t_old_mode = dc.SetBkMode(TRANSPARENT);

				CString t_str;
				t_str.Format(L"%s", caption.srcBTN_Caption.at(m_oldClickedScrBTN).c_str());

				m_ClickedScreenPos[m_oldClickedScrBTN][_col] = 0;

				dc.FillSolidRect(&m_scrBTN.r[m_oldClickedScrBTN], RGB(192, 192, 192)); // 회색
				dc.Draw3dRect(&m_scrBTN.r[m_oldClickedScrBTN], RGB(192, 192, 192), RGB(0, 0, 0));
				dc.SetTextColor(RGB(0, 0, 0)); // 검정
				dc.DrawText(t_str, &m_scrBTN.r[m_oldClickedScrBTN], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				dc.SetBkMode(t_old_mode);
			}

			m_ClickedScreenPos[selectScrBTN][_col] = 1;

			dc.FillSolidRect(&m_scrBTN.r[selectScrBTN], RGB(100, 200, 200)); // 하늘색
			dc.Draw3dRect(&m_scrBTN.r[selectScrBTN], RGB(0, 0, 0), RGB(100, 200, 200));
			dc.SetTextColor(RGB(255, 255, 255)); // 흰색
			dc.DrawText(str, (CRect)m_scrBTN.r[selectScrBTN] + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			m_oldClickedScrBTN = selectScrBTN;

			ChangeScreen(selectScrBTN);
		}

		// 배경을 이전 모드로 설정한다.
		dc.SetBkMode(old_mode);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}
//--------------------------------------------------------------------------------------------