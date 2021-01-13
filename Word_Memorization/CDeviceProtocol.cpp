// CDeviceProtocol.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CDeviceProtocol.h"
#include "afxdialogex.h"

#include "Grid_Func_Group.h"
#include "CSetDataPopUp.h"
#include "./WJ_String.h"

// CDeviceProtocol dialog

IMPLEMENT_DYNAMIC(CDeviceProtocol, CDialogEx)

CDeviceProtocol::CDeviceProtocol(WJ_String a_device, WJ_String a_caption, int a_port, int a_node, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROTOCOL_POPUP, pParent), m_deviceName(a_device), m_caption(a_caption), m_port(a_port), m_node(a_node)
{
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

CDeviceProtocol::~CDeviceProtocol()
{
	/*if (mp_PT_Grid != NULL) {
		DestroyWindow();
		delete mp_PT_Grid;
	}*/
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDeviceProtocol::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

BEGIN_MESSAGE_MAP(CDeviceProtocol, CDialogEx)
	ON_WM_CLOSE()	
	ON_BN_CLICKED(IDC_PAGE_DOWN_BTN, &CDeviceProtocol::OnBnClickedPageDownBtn)
	ON_BN_CLICKED(IDC_PAGE_UP_BTN, &CDeviceProtocol::OnBnClickedPageUpBtn)

	// mouse click option
	ON_NOTIFY(NM_RCLICK, IDC_PT_GRID, &CDeviceProtocol::OnGridClick)
	ON_NOTIFY(NM_DBLCLK, IDC_PT_GRID, &CDeviceProtocol::OnGridDblClick)	
	ON_BN_CLICKED(IDC_EXIT_BTN, &CDeviceProtocol::OnBnClickedExitBtn)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDeviceProtocol message handlers


BOOL CDeviceProtocol::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetBackgroundColor(RGB(45, 45, 45));

	CreateGrid(m_port, m_node);	

	return TRUE;  
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDeviceProtocol::OnClose()
{
	// 상단 x를 클릭 했을 때. 
	OnBnClickedExitBtn();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDeviceProtocol::CreateGrid(int a_port, int a_node)
{	
	if (NULL != mp_PT_Grid) {
		delete mp_PT_Grid;
		mp_PT_Grid = NULL;
	}

	mp_PT_Grid = new CGridCtrl;
	mp_PT_Grid->Create(CRect(10, 5, 1012, 760), this, IDC_PT_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER); // 10, 5, 1018, 760

	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();	
	Sheet *pSheet = mainDlg->mp_Libxl->sheetMap.find(a_port)->second;

	unsigned short fcode = (unsigned short)pSheet->readNum(3, 10);
	unsigned short rowCount = 2 << fcode;

	mp_PT_Grid->SetRowCount(rowCount + 2);
	mp_PT_Grid->SetColumnCount(8 + 1); // 현시할 column 8개, fixed column 1개

	mp_PT_Grid->SetFixedRowCount(2);
	mp_PT_Grid->SetFixedColumnCount(1);

	mp_PT_Grid->SetFixedBkColor(RGB(200, 200, 200));
	mp_PT_Grid->SetGridLineColor(RGB(128, 128, 255));

	// grid option	
	mp_PT_Grid->SetTrackFocusCell(true);
	mp_PT_Grid->SetEditable(false); // 셀 더블 클릭 하면 내용 수정할 수 없도록 막음.
	mp_PT_Grid->EnableTitleTips(false);

	CString str;

	// Bit 15 ~ 8
	// Bit 7 ~ 0
	for (int col = 1; col < 9; col++) {
		str.Format(L"Bit %02d", 16 - col);
		mp_PT_Grid->SetItemText(0, col, str);

		str.Format(L"Bit %02d", 7 - (col - 1));
		mp_PT_Grid->SetItemText(1, col, str);

		mp_PT_Grid->SetColumnWidth(col, 113); // column width
	}

	// Byte
	for (int i = 2; i < rowCount + 2; i++) {
		int word = (i - 2) / 2;
		str.Format(L"Byte %02d (W %02d)", i - 2, word);
		mp_PT_Grid->SetItemText(i, 0, str);

		if (word % 2 == 0) {
			mp_PT_Grid->SetItemBkColour(i, 0, (RGB(200, 120, 160)));
		}
		else {
			mp_PT_Grid->SetItemBkColour(i, 0, (RGB(130, 130, 200)));
		}
	}

	// 그리드 초기화
	mp_PT_Grid->ClearCells(CCellRange(2, 1, rowCount + 1, 8));
	_GFG::_GFG_InitItemBkColor(rowCount + 1, 8, mp_PT_Grid);

	// 그리드 매핑.
	_GFG::_GFG_InitMakeGrid(fcode, m_port, m_node, mp_PT_Grid);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDeviceProtocol::OnBnClickedPageDownBtn()
{		
	if (L"VAC1" == m_deviceName || L"VAC2" == m_deviceName || L"VAC3" == m_deviceName || L"VAC4" == m_deviceName) {
		// VAC
		short VAC_port_list1[2] = { 0x0B8, 0x0B0 };
		short VAC_port_list2[2] = { 0x0B8, 0x0B4 };
		short VAC_port_list3[2] = { 0x0BC, 0x0F0 };
		short VAC_port_list4[2] = { 0x0BC, 0x0F4 };

		if (m_page == 1) return;

		m_page++;

		if (L"VAC1" == m_deviceName)
			m_port = VAC_port_list1[m_page];
		else if (L"VAC2" == m_deviceName)
			m_port = VAC_port_list2[m_page];
		else if (L"VAC3" == m_deviceName)
			m_port = VAC_port_list3[m_page];
		else
			m_port = VAC_port_list4[m_page];
	}
	else if (L"LDCU1" == m_deviceName || L"RDCU1" == m_deviceName || L"LDCU2" == m_deviceName || L"RDCU2" == m_deviceName) {
		// DCU
		short dcu_port_listL1[3] = { 0x0FC, 0x0D0, 0x0D8 };
		short dcu_port_listL2[3] = { 0x0FC, 0x0E0, 0x0E8 };
		short dcu_port_listR1[3] = { 0x0FC, 0x0D4, 0x0DC };
		short dcu_port_listR2[3] = { 0x0FC, 0x0E4, 0x0EC };

		if (m_page == 2) return;

		m_page++;

		if (L"LDCU1" == m_deviceName)
			m_port = dcu_port_listL1[m_page];
		else if (L"LDCU2" == m_deviceName)
			m_port = dcu_port_listL2[m_page];
		else if (L"RDCU1" == m_deviceName)
			m_port = dcu_port_listR1[m_page];
		else
			m_port = dcu_port_listR2[m_page];
	}	
	else if (L"ECU1" == m_deviceName || L"ECU2" == m_deviceName || L"ECU3" == m_deviceName || L"ECU4" == m_deviceName) {
		// BECU
		short becu_port_list1[4] = { 0x028, 0x038, 0x048, 0x010 };
		short becu_port_list2[4] = { 0x028, 0x038, 0x048, 0x020 };
		short becu_port_list3[4] = { 0x028, 0x038, 0x048, 0x030 };
		short becu_port_list4[4] = { 0x028, 0x038, 0x048, 0x040 };

		if (m_page == 3) return;

		m_page++;

		if(L"ECU1" == m_deviceName)
			m_port = becu_port_list1[m_page];
		else if (L"ECU2" == m_deviceName)
			m_port = becu_port_list2[m_page];
		else if (L"ECU3" == m_deviceName)
			m_port = becu_port_list3[m_page];
		else
			m_port = becu_port_list4[m_page];
	}	
	else if (L"VVVF1" == m_deviceName || L"VVVF2" == m_deviceName || L"VVVF3" == m_deviceName || L"VVVF4" == m_deviceName) {
		// VVVF		
		short vvvf_port_list1[3] = { 0x058, 0x050, 0x054 };
		short vvvf_port_list2[3] = { 0x058, 0x060, 0x064 };
		short vvvf_port_list3[3] = { 0x058, 0x070, 0x074 };
		short vvvf_port_list4[3] = { 0x058, 0x080, 0x084 };

		if (m_page == 2) return;

		m_page++;

		if (L"VVVF1" == m_deviceName)
			m_port = vvvf_port_list1[m_page];
		else if (L"VVVF2" == m_deviceName)
			m_port = vvvf_port_list2[m_page];
		else if (L"VVVF3" == m_deviceName)
			m_port = vvvf_port_list3[m_page];
		else
			m_port = vvvf_port_list4[m_page];
	}
	else
		return;

	WJ_String _str;
	_str.Format(L"%s [port : 0x%02X] [node : %d]", m_deviceName, m_port, m_node);
	SetWindowTextW(_str.GetString());

	CreateGrid(m_port, m_node);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDeviceProtocol::OnBnClickedPageUpBtn()
{
	if (L"VAC1" == m_deviceName || L"VAC2" == m_deviceName || L"VAC3" == m_deviceName || L"VAC4" == m_deviceName) {
		// VAC
		short VAC_port_list1[2] = { 0x0B8, 0x0B0 };
		short VAC_port_list2[2] = { 0x0B8, 0x0B4 };
		short VAC_port_list3[2] = { 0x0BC, 0x0F0 };
		short VAC_port_list4[2] = { 0x0BC, 0x0F4 };

		if (m_page == 0) return;

		m_page--;

		if (L"VAC1" == m_deviceName)
			m_port = VAC_port_list1[m_page];
		else if (L"VAC2" == m_deviceName)
			m_port = VAC_port_list2[m_page];
		else if (L"VAC3" == m_deviceName)
			m_port = VAC_port_list3[m_page];
		else
			m_port = VAC_port_list4[m_page];
	}
	else if (L"LDCU1" == m_deviceName || L"RDCU1" == m_deviceName || L"LDCU2" == m_deviceName || L"RDCU2" == m_deviceName) {
		// DCU
		short dcu_port_listL1[3] = { 0x0FC, 0x0D0, 0x0D8 };
		short dcu_port_listL2[3] = { 0x0FC, 0x0E0, 0x0E8 };
		short dcu_port_listR1[3] = { 0x0FC, 0x0D4, 0x0DC };
		short dcu_port_listR2[3] = { 0x0FC, 0x0E4, 0x0EC };

		if (m_page == 0) return;

		m_page--;

		if (L"LDCU1" == m_deviceName)
			m_port = dcu_port_listL1[m_page];
		else if (L"LDCU2" == m_deviceName)
			m_port = dcu_port_listL2[m_page];
		else if (L"RDCU1" == m_deviceName)
			m_port = dcu_port_listR1[m_page];
		else
			m_port = dcu_port_listR2[m_page];
	}
	else if (L"ECU1" == m_deviceName || L"ECU2" == m_deviceName || L"ECU3" == m_deviceName || L"ECU4" == m_deviceName) {
		// BECU
		short becu_port_list1[4] = { 0x028, 0x038, 0x048, 0x010 };
		short becu_port_list2[4] = { 0x028, 0x038, 0x048, 0x020 };
		short becu_port_list3[4] = { 0x028, 0x038, 0x048, 0x030 };
		short becu_port_list4[4] = { 0x028, 0x038, 0x048, 0x040 };

		if (m_page == 0) return;

		m_page--;

		if (L"ECU1" == m_deviceName)
			m_port = becu_port_list1[m_page];
		else if (L"ECU2" == m_deviceName)
			m_port = becu_port_list2[m_page];
		else if (L"ECU3" == m_deviceName)
			m_port = becu_port_list3[m_page];
		else
			m_port = becu_port_list4[m_page];
	}
	else if (L"VVVF1" == m_deviceName || L"VVVF2" == m_deviceName || L"VVVF3" == m_deviceName || L"VVVF4" == m_deviceName) {
		// VVVF		
		short vvvf_port_list1[3] = { 0x058, 0x050, 0x054 };
		short vvvf_port_list2[3] = { 0x058, 0x060, 0x064 };
		short vvvf_port_list3[3] = { 0x058, 0x070, 0x074 };
		short vvvf_port_list4[3] = { 0x058, 0x080, 0x084 };

		if (m_page == 0) return;

		m_page--;

		if (L"VVVF1" == m_deviceName)
			m_port = vvvf_port_list1[m_page];
		else if (L"VVVF2" == m_deviceName)
			m_port = vvvf_port_list2[m_page];
		else if (L"VVVF3" == m_deviceName)
			m_port = vvvf_port_list3[m_page];
		else
			m_port = vvvf_port_list4[m_page];
	}
	else
		return;

	WJ_String _str;
	_str.Format(L"%s [port : 0x%02X] [node : %d]", m_deviceName, m_port, m_node);
	SetWindowTextW(_str.GetString());

	CreateGrid(m_port, m_node);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// Bit format
void CDeviceProtocol::OnGridClick(NMHDR *pNotifyStruct, LRESULT * /*pResult*/)
{
	NM_GRIDVIEW *pItem = (NM_GRIDVIEW *)pNotifyStruct;
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();
	Sheet *pSheet = _CExcelLib::sheetMap.find(m_port)->second;
	
	if (pItem->iRow == 0 || pItem->iRow == 1) return; // fix cells
	if (pItem->iColumn == 0 || pItem->iColumn == 9) return; // Unused cells in column.	
	if (pSheet->getMerge(pItem->iRow + 3, pItem->iColumn + 1, 0, 0, 0, 0)) return; // 병합된 셀인지 체크.
	
	int mvbIndex = binarySearch(_CExcelLib::mvb_Addr, 120, m_port);
	mvbIndex += _CExcelLib::m_totalNodeCnt * m_node;
	
	// 공유 메모리에서 데이터 가져옴.
	unsigned char data_8bit;
	memcpy(&data_8bit, &mainDlg->m_pData->data[mvbIndex][pItem->iRow - 2], 1);
	
	// 공유 메모리에 데이터 세팅.
	unsigned char x = 7 - (pItem->iColumn - 1);
	data_8bit ^= 0x1 << x;
	memset(&mainDlg->m_pData->data[mvbIndex][pItem->iRow - 2], data_8bit, 1);
		
	// 셀색 변경.
	if ((data_8bit >> x) & 0x1)	
		mp_PT_Grid->SetItemBkColour(pItem->iRow, pItem->iColumn, RCLICK_RGB);
	else 
		mp_PT_Grid->SetItemBkColour(pItem->iRow, pItem->iColumn, WHITE_RGB);	
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// Merge Cell
void CDeviceProtocol::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT * /*pResult*/)
{
	NM_GRIDVIEW *pItem = (NM_GRIDVIEW *)pNotifyStruct;
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();
	Sheet *pSheet = _CExcelLib::sheetMap.find(m_port)->second;

	if (pItem->iRow == 0 || pItem->iRow == 1) return; // fix cells
	if (pItem->iColumn == 0 || pItem->iColumn == 9) return; // Unused cells in column.
	if (!pSheet->getMerge(pItem->iRow + 3, pItem->iColumn + 1, 0, 0, 0, 0)) return; // 병합된 셀인지 체크.

	CSetDataPopUp *pDataPopUp;
	pDataPopUp = new CSetDataPopUp(pItem->iRow, pItem->iColumn, m_port, m_node, mp_PT_Grid);
	pDataPopUp->Create(IDD_SETDATA_POPUP, this);
	pDataPopUp->ShowWindow(5); // 5 is SH_SHOWS		
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDeviceProtocol::OnBnClickedExitBtn()
{	
	int key = m_map_key;
	// GetParent()->PostMessage(27000, 0, 0);
	::PostMessage(h_handle, 27000, key, 0);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+