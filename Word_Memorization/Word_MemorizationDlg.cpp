
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
	m_trainBTN.xPos = 20;      // x ���� ��ǥ	
	m_trainBTN.width = 100;    // �� ������
	m_trainBTN.spacing_W = 20; // x ��ǥ ����
	m_trainBTN.rowCount = 1;

	m_trainBTN.yPos = 20;      // y ���� ��ǥ	
	m_trainBTN.height = 25;    // ����
	m_trainBTN.spacing_H = 0;  // y ��ǥ ����
	m_trainBTN.colCount = 8;

	OnInitTrainBuutton();

	m_ClickedCarPos = new unsigned char * [m_trainBTN.rowCount];
	
	for (int i = 0; i < m_trainBTN.rowCount; i++) {
		m_ClickedCarPos[i] = new unsigned char[m_trainBTN.colCount];
		memset(m_ClickedCarPos[i], 0, sizeof(unsigned char) * m_trainBTN.colCount);
		//for (int j = 0; j < m_trainBTN.colCount; j++) {
		//	m_ClickedCarPos[i][j] = 0;//i * m_trainBTN.rowCount + j;			
		//}
	}

	//// 2���� �迭 �ʱ�ȭ (double pointer)
	//for (int i = 0; i < m_trainBTN.rowCount; i++) {
	//	// �ʱ�ȭ ��ų �迭, �ʱ�ȭ �� ��, colum����
	//	
	//}
//--------------------------------------------------------------------------------------------

	// Init Screen Button Pos;
	//m_scrBTN.xPos = 0;     // x ���� ��ǥ	
	//m_scrBTN.width = 0;   // �� ������
	//m_scrBTN.spacing_W = 5; // x ��ǥ ����

	//m_scrBTN.yPos = 0;    // y ���� ��ǥ	
	//m_scrBTN.Height = 0; // ����
	//m_scrBTN.spacing_H = 0;   // y ��ǥ ����

	//for (int i = 0; i < m_trainBTN.rowCount; i++) {
	//	// �ʱ�ȭ ��ų �迭, �ʱ�ȭ �� ��, colum����
	//	memset(m_ClickedCarPos[i], 0, m_trainBTN.colCount * sizeof(unsigned char));
	//}

	
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
		//OnDrawScreenButton(&dc, &r);

		//CDialogEx::OnPaint();
	}
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::OnInitTrainBuutton()
{	
	m_trainBTN.r.clear();

	RECT r;
	for (int rowCnt = 0; rowCnt < m_trainBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < m_trainBTN.colCount; colCnt++) {
			r.left = m_trainBTN.xPos + colCnt * (m_trainBTN.width + m_trainBTN.spacing_W);
			r.right = r.left + m_trainBTN.width;
			r.top = m_trainBTN.yPos + rowCnt * m_trainBTN.spacing_H;
			r.bottom = r.top + m_trainBTN.height;

			m_trainBTN.r.push_back(r);			
		}
	}
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::OnDrawTrainButton(CDC *p_DC, CRect *p_R)
{
	for (int rowCnt = 0; rowCnt < m_trainBTN.rowCount; rowCnt++) {
		for (int colCnt = 0; colCnt < m_trainBTN.colCount; colCnt++) {

			int old_mode = p_DC->SetBkMode(TRANSPARENT);
			CString str;
			str.Format(L"Car0%d", colCnt);

			if (1 == m_ClickedCarPos[rowCnt][colCnt]) {
				p_DC->FillSolidRect(&m_trainBTN.r[colCnt], RGB(200, 200, 100)); // ���λ�
				p_DC->Draw3dRect(&m_trainBTN.r[colCnt], RGB(0, 0, 0), RGB(200, 200, 100));
				p_DC->SetTextColor(RGB(255, 255, 255)); // ���

				p_DC->DrawText(str, (CRect)m_trainBTN.r[colCnt] + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else {
				p_DC->FillSolidRect(&m_trainBTN.r[colCnt], RGB(192, 192, 192)); // ȸ��
				p_DC->Draw3dRect(&m_trainBTN.r[colCnt], RGB(192, 192, 192), RGB(0, 0, 0));
				p_DC->SetTextColor(RGB(0, 0, 0)); // ����

				p_DC->DrawText(str, &m_trainBTN.r[colCnt], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			}

			// ����� ���� ���� �����Ѵ�.
			p_DC->SetBkMode(old_mode);
		}
	}

	//// train button ��ǥ ���� ����.
	//m_CarButtonRange_StartX = m_trainBTN.xPos;
	//m_CarButtonRange_EndX = p_R->right;
	//m_CarButtonRange_StartY = m_trainBTN.yPos;
	//m_CarButtonRange_EndY = p_R->bottom;
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::OnDrawScreenButton(CDC *p_DC, CRect *p_R)
{
	int startWidth, endWidht;
	int startHeight, endHeight;

	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 6; j++) {
			startWidth = 1200 + i * 130; // x��ǥ ������, 10��ŭ ������ ���� �׸�.
			endWidht = startWidth + 120;
			startHeight = 35 + j * 40; // 10��ŭ ������ ���� �׸�.
			endHeight = startHeight + 35;

			p_R->left = startWidth;
			p_R->right = endWidht;
			p_R->top = startHeight;
			p_R->bottom = endHeight;

			int old_mode = p_DC->SetBkMode(TRANSPARENT);
			CString str;
			str.Format(L"Screen0%d", j);

			if (1 == m_ClickedScreenPos[j]) { // ���� ȸ������ ä��
				p_DC->FillSolidRect(p_R, RGB(100, 200, 200)); // // �ϴû�
				p_DC->Draw3dRect(p_R, RGB(0, 0, 0), RGB(100, 200, 200));
				p_DC->SetTextColor(RGB(255, 255, 255)); // ���

				p_DC->DrawText(str, *p_R + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			}
			else {
				p_DC->FillSolidRect(p_R, RGB(192, 192, 192)); // ȸ��
				p_DC->Draw3dRect(p_R, RGB(192, 192, 192), RGB(0, 0, 0));
				p_DC->SetTextColor(RGB(0, 0, 0)); // ����

				p_DC->DrawText(str, p_R, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}

			// ����� ���� ���� �����Ѵ�.
			p_DC->SetBkMode(old_mode);
		}
	}

	// screen button ��ư ��ǥ ���� ����.
	m_ScreenButtonRange_StartX = 1200;
	m_ScreenButtonRange_EndX = endWidht;
	m_ScreenButtonRange_StartY = 35;
	m_ScreenButtonRange_EndY = endHeight;
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
	int check = MessageBox(L"������ �����Ұž�??", L"���� Ȯ�� �޽��� â", MB_OKCANCEL | MB_ICONEXCLAMATION);
	
	if (IDCANCEL == check) 
		return; // �ƴϿ��� Ŭ������ ��� OnClose()�� ��������.
	else {
		// Libxl ��ü �ı�
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
	
	m_trainBTN.r.clear();
	//m_trainBTN.r.~vector();

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
			return true; // true�� ����ؼ� �޽��� ó���� ���� ����.
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
//--------------------------------------------------------------------------------------------

// ȭ�� ��ȯ
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
		//AfxMessageBox(L"Heartbit");
		mp_Form_Protocol->ShowWindow(SW_HIDE);
		mp_Form_HeartBit->ShowWindow(SW_SHOW);
		mp_Form_DuDefault_1->ShowWindow(SW_HIDE);
		mp_Form_SetMVB->ShowWindow(SW_HIDE);
		break;

	case 2:
		//AfxMessageBox(L"My Node");
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

	int port = binarySearch(mp_Libxl->mvb_Addr, 120, a_PortAddr); // 120�� �ǹ̴� myNode�� �� ������ �ǹ� �Ѵ�. ��� ���� ������ ����. // int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
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

	int port = binarySearch(mp_Libxl->mvb_Addr, 120, a_PortAddr); // 120�� �ǹ̴� myNode�� �� ������ �ǹ� �Ѵ�. ��� ���� ������ ����. // int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
	port += mp_Libxl->m_totalNodeCnt * a_Node;
	memcpy(&data, &(m_pData->data[port][a_Byte]), 1);

	return data;
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::SetBitDataToSM(WORD a_PortAddr, BYTE a_Node, BYTE a_Word, BYTE a_ColPos, WORD a_Data)
{
	int port = binarySearch(mp_Libxl->mvb_Addr, 120, a_PortAddr); // 120�� �ǹ̴� myNode�� �� ������ �ǹ� �Ѵ�. ��� ���� ������ ����. // int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
	port += mp_Libxl->m_totalNodeCnt * a_Node;

	WORD lsh = 0x01 << a_ColPos;
	WORD data = a_Data;
	data = data ^ lsh;

	m_pData->data[port][a_Word * 2    ] = data >> 8;   // ����
	m_pData->data[port][a_Word * 2 + 1] = data & 0xFF; // ����

	//WORD result;
	//((unsigned char *)&result)[1] = m_pData->data[port][a_Word * 2];     // ����
	//((unsigned char *)&result)[0] = m_pData->data[port][a_Word * 2 + 1]; // ����
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::Set16DataToSM(WORD a_PortAddr, BYTE a_Node, BYTE a_Word, WORD a_Data)
{
	int port = binarySearch(mp_Libxl->mvb_Addr, 120, a_PortAddr); // 120�� �ǹ̴� myNode�� �� ������ �ǹ� �Ѵ�. ��� ���� ������ ����. // int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
	port += mp_Libxl->m_totalNodeCnt * a_Node;

	memset(&(m_pData->data[port][a_Word * 2]), a_Data >> 8, 1); // ����
	memset(&(m_pData->data[port][a_Word * 2 + 1]), a_Data & 0xFF, 1); // ����
}
//--------------------------------------------------------------------------------------------

void CWordMemorizationDlg::Set08DataToSM(WORD a_PortAddr, BYTE a_Node, BYTE a_Word, bool a_Pos, BYTE a_Data)
{
	int port = binarySearch(mp_Libxl->mvb_Addr, 120, a_PortAddr); // 120�� �ǹ̴� myNode�� �� ������ �ǹ� �Ѵ�. ��� ���� ������ ����. // int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
	port += mp_Libxl->m_totalNodeCnt * a_Node;
	
	if (!a_Pos)
		memset(&(m_pData->data[port][a_Word * 2]), a_Data, 1);
	else
		memset(&(m_pData->data[port][a_Word * 2 + 1]), a_Data, 1);
}
//--------------------------------------------------------------------------------------------


void CWordMemorizationDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=645
	
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

/* �������� ���� ��ư�� ������ ���� �� �κ��� �� �ʿ��ϴ�.
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
�׳� �簢������ ?
// ComboBox
�簢�� + pDC->DrawFrameControl(m_oldRect, DFC_SCROLL, DFCS_SCROLLCOMBOBOX);

��ư ���� �۾��� �����ϰ�...
pDC->SetBkMode(TRANSPARENT);


��ó: https://elkeipy.tistory.com/entry/DrawFrameControl [������'s �ҷ���α�!]
*/

void CWordMemorizationDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	unsigned int _col, _row;

	if ((point.x > 20 && point.x < 120 && point.y > 20 && point.y < 45) ||
		(point.x > 140 && point.x < 240 && point.y > 20 && point.y < 45) ||
		(point.x > 260 && point.x < 360 && point.y > 20 && point.y < 45) ||
		(point.x > 380 && point.x < 480 && point.y > 20 && point.y < 45) ||
		(point.x > 500 && point.x < 600 && point.y > 20 && point.y < 45) ||
		(point.x > 620 && point.x < 720 && point.y > 20 && point.y < 45) ||
		(point.x > 740 && point.x < 840 && point.y > 20 && point.y < 45) ||
		(point.x > 860 && point.x < 960 && point.y > 20 && point.y < 45) ) { // car

		MessageBox(L"ok");
		_col = 0;
	
		CClientDC dc(this);
		CRect r;

		//r.left r.right r.top r.bottom
		
		// train button
		//if ((_col < 8) && (_row == 0)) {
		//	int old_mode = dc.SetBkMode(TRANSPARENT);
		//	CString str;
		//	str.Format(L"Car0%d", _col);

		//	if (1 == m_ClickedCarPos[_row][_col]) { // ���� ȸ������ ä��
		//		m_ClickedCarPos[_row][_col] = 0;

		//		dc.FillSolidRect(r, RGB(192, 192, 192)); // ȸ��
		//		dc.Draw3dRect(r, RGB(192, 192, 192), RGB(0, 0, 0));
		//		dc.SetTextColor(RGB(0, 0, 0)); // ����
		//		dc.DrawText(str, r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		//	}
		//	else {
		//		m_ClickedCarPos[0][_col] = 1;

		//		dc.FillSolidRect(r, RGB(100, 200, 200)); // // �ϴû�
		//		dc.Draw3dRect(r, RGB(0, 0, 0), RGB(100, 200, 200));
		//		dc.SetTextColor(RGB(255, 255, 255)); // ���
		//		dc.DrawText(str, r + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		//	}

		//	// ����� ���� ���� �����Ѵ�.
		//	dc.SetBkMode(old_mode);
		//}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}
