// CForm_SetMVB.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CForm_SetMVB.h"

#include "Word_MemorizationDlg.h"

#include "_CExcelLib.h"
#include "DefineOfDev_J.h"

// CForm_SetMVB

IMPLEMENT_DYNCREATE(CForm_SetMVB, CFormView)

CForm_SetMVB::CForm_SetMVB()
	: CFormView(IDD_FORM_SETMVB)
{

}

CForm_SetMVB::~CForm_SetMVB()
{
	// Timer
	/*KillTimer(USER_TIMER_0);
	KillTimer(USER_TIMER_1);
	KillTimer(USER_TIMER_2);
	KillTimer(USER_TIMER_3);*/

}

void CForm_SetMVB::DoDataExchange(CDataExchange *pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SETMVB_ADDR, str_SetAddr);
	DDX_Control(pDX, IDC_SETMVB_WORD, str_SetWord);
	DDX_Control(pDX, IDC_SETMVB_VALUE, str_SetValue);
}

BEGIN_MESSAGE_MAP(CForm_SetMVB, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CForm_SetMVB::OnBnClickedButton1)
	ON_WM_TIMER()

	// mouse click option
	ON_NOTIFY(NM_RCLICK, IDC_GFG_GRID, &CForm_SetMVB::On_GFG_GridClick)

	ON_COMMAND_RANGE(IDC_SETMVB_TM_START_0, IDC_SETMVB_TM_START_3, TiemerStart)
	ON_COMMAND_RANGE(IDC_SETMVB_TM_STOP_0, IDC_SETMVB_TM_STOP_3, TimerStop)
	ON_BN_CLICKED(IDC_BUTTON2, &CForm_SetMVB::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CForm_SetMVB::OnBnClickedButton3)
END_MESSAGE_MAP()


// CForm_SetMVB diagnostics

#ifdef _DEBUG
void CForm_SetMVB::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CForm_SetMVB::Dump(CDumpContext &dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CForm_SetMVB message handlers


BOOL CForm_SetMVB::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext)
{		
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CForm_SetMVB::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}


void CForm_SetMVB::OnBnClickedButton1()
{
	WORD portAddr, word, value;

	CString strPortAddr;
	GetDlgItemText(IDC_SETMVB_ADDR, strPortAddr);
	portAddr = _tcstoul(strPortAddr, NULL, 16); // ���ڿ��� 16������ ��ȯ.

	word = GetDlgItemInt(IDC_SETMVB_WORD);
	word *= 2;

	value = GetDlgItemInt(IDC_SETMVB_VALUE);

	BYTE node;
	node = GetDlgItemInt(IDC_SETMVB_NODE); // 0�̸� myNode�� �ǹ���.

	mp_FormMainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	if (mp_FormMainDlg != NULL) {
		//mp_FormMainDlg->SetMVBValue(node, port, value);

		BYTE l_byte, h_byte;

		_CExcelLib *p_ExcelLib = (_CExcelLib *)mp_FormMainDlg->mp_Libxl;
		
		// 120�� �ǹ̴� myNode�� �� ������ �ǹ� �Ѵ�. ��� ���� ������ ����.
		// int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
		int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
		int t_port = binarySearch(p_ExcelLib->mvb_Addr, dataSize, portAddr);
		
		t_port += p_ExcelLib->m_totalNodeCnt * node;

		h_byte = ((unsigned char *)&value)[1]; // word ����
		l_byte = ((unsigned char *)&value)[0]; // word ����

		memset(&(mp_FormMainDlg->m_pData->data[t_port][word]), h_byte, 1);   // mvb ���� ����Ʈ�� ���� ����
		memset(&(mp_FormMainDlg->m_pData->data[t_port][word+1]), l_byte, 1); // mvb ���� ����Ʈ�� ���� ����

		p_ExcelLib = NULL;
	}

	mp_FormMainDlg = NULL;

}


void CForm_SetMVB::OnTimer(UINT_PTR nIDEvent)
{
	unsigned int port;
	mp_FormMainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	switch (nIDEvent)
	{
	case USER_TIMER_0:
		port = GetDlgItemInt(IDC_SETMVB_TM_PORT0);

		if (m_HeartBit_0 != 0xFFFF) {
			m_HeartBit_0++;

			mp_FormMainDlg->SetMVBHeartBit(port, m_HeartBit_0);
			//memset(&(mp_FormMainDlg->m_pData->data[port][0]), m_HeartBit_0, 2);
		}
		else
			m_HeartBit_0 = 0;

		break;

	case USER_TIMER_1:
		port = GetDlgItemInt(IDC_SETMVB_TM_PORT1);

		if (m_HeartBit_1 != 0xFFFF) {
			m_HeartBit_1++;

			//mp_FormMainDlg->SetMVBHeartBit(port, m_HeartBit_1);
			memset(&(mp_FormMainDlg->m_pData->data[port][0]), m_HeartBit_1, 2);
		}
		else
			m_HeartBit_1 = 0;

		break;

	case USER_TIMER_2:
		port = GetDlgItemInt(IDC_SETMVB_TM_PORT2);

		if (m_HeartBit_2 != 0xFFFF) {
			m_HeartBit_2++;

			mp_FormMainDlg->SetMVBHeartBit(port, m_HeartBit_2);
			//memset(&(mp_FormMainDlg->m_pData->data[port][0]), m_HeartBit_2, 2);
		}
		else
			m_HeartBit_2 = 0;

		break;

	case USER_TIMER_3:
		port = GetDlgItemInt(IDC_SETMVB_TM_PORT3);

		if (m_HeartBit_3 != 0xFFFF) {
			m_HeartBit_3++;

			mp_FormMainDlg->SetMVBHeartBit(port, m_HeartBit_3);
			//memset(&(mp_FormMainDlg->m_pData->data[port][0]), m_HeartBit_3, 2);
		}
		else
			m_HeartBit_3 = 0;

		break;
	}

	mp_FormMainDlg = NULL;

	CFormView::OnTimer(nIDEvent);
}


void CForm_SetMVB::TiemerStart(UINT ID)
{
	switch (ID - IDC_SETMVB_TM_START_0)
	{
	case 0:
		m_HeartBit_0 = 0;
		SetTimer(USER_TIMER_0, 300, NULL);
		break;

	case 1:
		m_HeartBit_1 = 0;
		SetTimer(USER_TIMER_1, 300, NULL);
		break;

	case 2:
		m_HeartBit_2 = 0;
		SetTimer(USER_TIMER_2, 300, NULL);
		break;

	case 3:
		m_HeartBit_3 = 0;
		SetTimer(USER_TIMER_3, 300, NULL);
		break;
	}
}


void CForm_SetMVB::TimerStop(UINT ID)
{
	switch (ID - IDC_SETMVB_TM_STOP_0)
	{
	case 0:
		KillTimer(USER_TIMER_0);
		break;

	case 1:
		KillTimer(USER_TIMER_1);
		break;

	case 2:
		KillTimer(USER_TIMER_2);
		break;

	case 3:
		KillTimer(USER_TIMER_3);
		break;
	}

}
//--------------------------------------------------------------------------------------------

void CForm_SetMVB::OnBnClickedButton2()
{ 
	WORD portAddr, word, value;

	portAddr = GetDlgItemInt(IDC_SETMVB_ADDR2);

	word = GetDlgItemInt(IDC_SETMVB_WORD);
	word *= 2;

	value = GetDlgItemInt(IDC_SETMVB_VALUE);

	mp_FormMainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	if (mp_FormMainDlg != NULL) {
		//mp_FormMainDlg->SetMVBValue(node, port, value);

		BYTE l_byte, h_byte;

		h_byte = ((unsigned char *)&value)[1]; // word ����
		l_byte = ((unsigned char *)&value)[0]; // word ����

		memset(&(mp_FormMainDlg->m_pData->data[portAddr][word]), h_byte, 1);   // mvb ���� ����Ʈ�� ���� ����
		memset(&(mp_FormMainDlg->m_pData->data[portAddr][word + 1]), l_byte, 1); // mvb ���� ����Ʈ�� ���� ����
	}

	mp_FormMainDlg = NULL;
}
//--------------------------------------------------------------------------------------------

void CForm_SetMVB::OnBnClickedButton3()
{
	CString strPortAddr;
	GetDlgItemText(IDC_SETMVB_GRID_ADDR, strPortAddr);
	WORD portAddr = _tcstoul(strPortAddr, NULL, 16); // ���ڿ��� 16������ ��ȯ.

	BYTE node;
	node = GetDlgItemInt(IDC_SETMVB_GRID_NODE); // 0�̸� myNode�� �ǹ���.

	if (strPortAddr == L"" || node >= 5)
		return;

	
	if (mp_ScrSetMVB_Grid == NULL) {
		mp_ScrSetMVB_Grid = new CGridCtrl;
		mp_ScrSetMVB_Grid->Create(CRect(10, 310, 1020, 1065), this, IDC_GFG_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER);
	
		mp_ScrSetMVB_Grid->SetRowCount(32 + 2);
		mp_ScrSetMVB_Grid->SetColumnCount(8 + 1); // ������ column 8��, fixed column 1��

		mp_ScrSetMVB_Grid->SetFixedRowCount(2);
		mp_ScrSetMVB_Grid->SetFixedColumnCount(1);

		mp_ScrSetMVB_Grid->SetFixedBkColor(RGB(200, 200, 200));

		// grid option
		mp_ScrSetMVB_Grid->SetGridLineColor(RGB(128, 128, 255));
		mp_ScrSetMVB_Grid->SetTrackFocusCell(true);
		mp_ScrSetMVB_Grid->SetEditable(true);

		mp_ScrSetMVB_Grid->EnableTitleTips(false);
	
		CString str;

		// Bit 7 ~ 0
		for (int i = 1; i < 9; i++) {
			str.Format(L"Bit %02d", 7 - (i - 1));
			mp_ScrSetMVB_Grid->SetItemText(1, i, str);
		}
		// Bit 15 ~ 8
		for (int i = 1; i < 9; i++) {
			str.Format(L"Bit %02d", 16 - i);
			mp_ScrSetMVB_Grid->SetItemText(0, i, str);
		}
		// Byte
		for (int i = 2; i < 34; i++) {
			int word = (i - 2) / 2;
			str.Format(L"Byte %02d (W %02d)", i - 2, word);
			mp_ScrSetMVB_Grid->SetItemText(i, 0, str);
		}

		// column width
		for (int col = 1; col < 9; col++) {
			mp_ScrSetMVB_Grid->SetColumnWidth(col, 114);
		}
	}

	// �׸��� �ʱ�ȭ
	mp_ScrSetMVB_Grid->ClearCells(CCellRange(2, 1, 33, 8));
	_GFG::_GFG_InitItemBkColor(33, 8, mp_ScrSetMVB_Grid);

	// �Ű� ���� ������ ������ ���� �����̴�.
	//_GFG::_GFG_InitMakeGrid(5, 36, 2, 9, portAddr, mp_ScrSetMVB_Grid); // ��Ʈ �������� ������ �������� üũ.
	//_GFG::_GFG_SetWordFormatCell(5, 36, 2, 9, portAddr, mp_ScrSetMVB_Grid); // ������ �����̸� ������ ��翡 �°� �׸��忡 �׸���.

	//_GFG::_GFG_GetBitDataFormSM(5, 36, 2, 9, portAddr, node, mp_ScrSetMVB_Grid); // ������ üũ�� �ؼ� 0�� �ƴ� ���� ������ �׸��� �� �� ���� - ��Ʈ ����
	_GFG::_GFG_GetBitDataFormSMTest(5, 36, 2, 9, portAddr, node, mp_ScrSetMVB_Grid); // ������ üũ�� �ؼ� 0�� �ƴ� ���� ������ �׸��� �� �� ���� - ��Ʈ ����
	//_GFG::_GFG_GetMoreThanTwoBitsOfDataFormSM(5, 36, 2, 9, 0x1A4, 0, mp_ScrSetMVB_Grid); // ������ üũ�� �ؼ� 0�� �ƴ� ���� ������ �׸��� �� �� ���� - ���յ� ����.

	//_GFG::_GFG_SetTextGrid();
}
//--------------------------------------------------------------------------------------------

BOOL CForm_SetMVB::DestroyWindow()
{
	if (NULL != mp_ScrSetMVB_Grid) {
		delete mp_ScrSetMVB_Grid;
		mp_ScrSetMVB_Grid = NULL;
	}

	return CFormView::DestroyWindow();
}
//--------------------------------------------------------------------------------------------

// bit format
void CForm_SetMVB::On_GFG_GridClick(NMHDR *pNotifyStruct, LRESULT * /*pResult*/)
{
	NM_GRIDVIEW *pItem = (NM_GRIDVIEW *)pNotifyStruct;

	if (pItem->iRow == 0 || pItem->iRow == 1 || pItem->iColumn == 0) return; // fix cells

	//  0�� �ƴ϶�� ���յ� ���� �ǹ� �ϱ� ������ ���յ� ������ ��Ŭ���� �� ��� �� �Լ��� ������ ������. 
	//if (IsMergeCheck(pItem->iRow, pItem->iColumn, m_flag) != 0) return;

	CString strPortAddr;
	GetDlgItemText(IDC_SETMVB_GRID_ADDR, strPortAddr);
	WORD portAddr = _tcstoul(strPortAddr, NULL, 16); // ���ڿ��� 16������ ��ȯ.

	BYTE node;
	node = GetDlgItemInt(IDC_SETMVB_GRID_NODE); // 0�̸� myNode�� �ǹ���.

	if (strPortAddr == L"" || node >= 5)
		return;

	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();
	_CExcelLib *p_ExcelLib = (_CExcelLib *)mainDlg->mp_Libxl;

	// 120�� �ǹ̴� myNode�� �� ������ �ǹ� �Ѵ�. ��� ���� ������ ����.
	// int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
	int t_port = binarySearch(p_ExcelLib->mvb_Addr, 120, portAddr);
	WORD t_WordPos = (pItem->iRow - 2) / 2;
	WORD smData = mainDlg->GetWordDataFromSM(portAddr, node, t_WordPos); // (WORD a_PortAddr, BYTE a_Node, BYTE a_Word)

	BYTE colPos = 7 - (pItem->iColumn - 1);
	if (pItem->iRow % 2 == 0) colPos += 8;

	mainDlg->SetBitDataToSM(portAddr, node, t_WordPos, colPos, smData);

	// Returns cell background color
	if (mp_ScrSetMVB_Grid->GetCell(pItem->iRow, pItem->iColumn)->GetBackClr() != RCLICK_RGB) {
		mp_ScrSetMVB_Grid->SetItemBkColour(pItem->iRow, pItem->iColumn, RCLICK_RGB);
	}
	else
		mp_ScrSetMVB_Grid->SetItemBkColour(pItem->iRow, pItem->iColumn, WHITE_RGB);

	mp_ScrSetMVB_Grid->RedrawCell(pItem->iRow, pItem->iColumn);

	p_ExcelLib = NULL;
	mainDlg = NULL;
}
//--------------------------------------------------------------------------------------------