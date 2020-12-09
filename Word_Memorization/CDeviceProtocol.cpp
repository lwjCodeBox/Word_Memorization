// CDeviceProtocol.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CDeviceProtocol.h"
#include "afxdialogex.h"

#include "Grid_Func_Group.h"

// CDeviceProtocol dialog

IMPLEMENT_DYNAMIC(CDeviceProtocol, CDialogEx)

CDeviceProtocol::CDeviceProtocol(CString a_device, int a_port, int a_node, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROTOCOL_EXCEL_DLG, pParent), m_deviceName(a_device), m_port(a_port), m_node(a_node)
{
	
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

CDeviceProtocol::~CDeviceProtocol()
{
	
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDeviceProtocol::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

BEGIN_MESSAGE_MAP(CDeviceProtocol, CDialogEx)
	ON_WM_CLOSE()	
	ON_BN_CLICKED(IDC_PAGE_DOWN_BTN, &CDeviceProtocol::OnBnClickedPageDownBtn)
	ON_BN_CLICKED(IDC_PAGE_UP_BTN, &CDeviceProtocol::OnBnClickedPageUpBtn)
END_MESSAGE_MAP()


// CDeviceProtocol message handlers


BOOL CDeviceProtocol::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CreateGrid(m_port, m_node);	

	return TRUE;  
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDeviceProtocol::OnClose()
{
	DestroyWindow();
	
	delete mp_PT_Grid;

	CDialogEx::OnClose();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

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
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDeviceProtocol::OnBnClickedPageDownBtn()
{		
	// DCU
	int dcu_port_list[9] =  { 0x0FC, 0x0D0, 0x0D4, 0x0D8, 0x0DC, 0x0E0, 0x0E4, 0x0E8, 0x0EC };
	
	// BECU
	int becu_port_list1[4] = { 0x028, 0x038, 0x048, 0x010 };
	int becu_port_list2[4] = { 0x028, 0x038, 0x048, 0x020 };
	int becu_port_list3[4] = { 0x028, 0x038, 0x048, 0x030 };
	int becu_port_list4[4] = { 0x028, 0x038, 0x048, 0x040 };
	
	// VVVF		
	int vvvf_port_list1[3] = { 0x058, 0x050, 0x054 };
	int vvvf_port_list2[3] = { 0x058, 0x060, 0x064 };
	int vvvf_port_list3[3] = { 0x058, 0x070, 0x074 };
	int vvvf_port_list4[3] = { 0x058, 0x080, 0x084 };
	
		
	if (L"LDCU1" == m_deviceName || L"RDCU1" == m_deviceName || L"LDCU2" == m_deviceName || L"RDCU2" == m_deviceName) {
		return;
	}	
	else if (L"ECU1" == m_deviceName || L"ECU2" == m_deviceName || L"ECU3" == m_deviceName || L"ECU4" == m_deviceName) {
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

	wchar_t *p_wchar = DbgLogW_P(L"%s [port : 0x%02X] [node : %d]", m_deviceName, m_port, m_node);
	SetWindowTextW(p_wchar);
	free(p_wchar);

	CreateGrid(m_port, m_node);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDeviceProtocol::OnBnClickedPageUpBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+