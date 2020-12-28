// CForm_DuDefault_1.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CForm_DuDefault_1.h"

#include "Word_MemorizationDlg.h"
#include "_CExcelLib.h"
#include "DefineOfDev_J.h"

#include "CSharedMemory.h"
#include "CSetDataPopUp.h"

// CForm_DuDefault_1

IMPLEMENT_DYNCREATE(CForm_DuDefault_1, CFormView)

CForm_DuDefault_1::CForm_DuDefault_1()
	: CFormView(IDD_FORM_DU_DEFAULT)
{

}

CForm_DuDefault_1::CForm_DuDefault_1(_CExcelLib *a_Libxl)
	: CFormView(IDD_FORM_DU_DEFAULT), pExcel(a_Libxl)
{
	mp_MainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();
}

CForm_DuDefault_1::~CForm_DuDefault_1()
{
}

void CForm_DuDefault_1::DoDataExchange(CDataExchange *pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CForm_DuDefault_1, CFormView)
#ifdef Edit_and_ListControl_Sample_CODE	
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LISTCONTROL, &CForm_DuDefault_1::OnCustomdrawList)
	ON_NOTIFY(NM_CLICK, IDC_LISTCONTROL, &CForm_DuDefault_1::OnNMClickList)
#endif
	ON_BN_CLICKED(IDC_DFS_DEFAULT_1, &CForm_DuDefault_1::OnBnClickedDfsDefault1)
	ON_BN_CLICKED(IDC_DFS_DEFAULT_2, &CForm_DuDefault_1::OnBnClickedDfsDefault2)
	ON_BN_CLICKED(IDC_DFS_DEFAULT_3, &CForm_DuDefault_1::OnBnClickedDfsDefault3)
	
	// mouse click option
	ON_NOTIFY(NM_RCLICK, IDC_GRID, &CForm_DuDefault_1::OnGridClick)
	ON_NOTIFY(NM_DBLCLK, IDC_GRID, &CForm_DuDefault_1::OnGridDblClick)
END_MESSAGE_MAP()

// CForm_DuDefault_1 diagnostics

#ifdef _DEBUG
void CForm_DuDefault_1::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CForm_DuDefault_1::Dump(CDumpContext &dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CForm_DuDefault_1 message handlers

BOOL CForm_DuDefault_1::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CForm_DuDefault_1::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}
//--------------------------------------------------------------------------------------------

void CForm_DuDefault_1::OnBnClickedDfsDefault1()
{	
	if (0x1A4 == m_port) return;
	m_port = 0x1A4;

	//memset(clicked, 0, sizeof(clicked));

	if (mp_gridctrl == NULL) {
		mp_gridctrl = new CGridCtrl;
		mp_gridctrl->Create(CRect(10, 45, 1018, 800), this, IDC_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER);
	}
	else {
		delete mp_gridctrl;
		mp_gridctrl = NULL;

		mp_gridctrl = new CGridCtrl;
		mp_gridctrl->Create(CRect(10, 45, 1018, 800), this, IDC_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER);
	}
	
	unsigned short fcode = 4;
	unsigned short rowCount = 2 << fcode;

	mp_gridctrl->SetRowCount(rowCount + 2);
	mp_gridctrl->SetColumnCount(8 + 1); // 현시할 column 8개, fixed column 1개
	
	mp_gridctrl->SetFixedRowCount(2);
	mp_gridctrl->SetFixedColumnCount(1);

	mp_gridctrl->SetFixedBkColor(RGB(200, 200, 200));

	mp_gridctrl->SetGridLineColor(RGB(128, 128, 255));
	
	// grid option	
	mp_gridctrl->SetTrackFocusCell(true);
	mp_gridctrl->SetEditable(false); // 셀 더블 클릭 하면 내용 수정할 수 없도록 막음.
	mp_gridctrl->EnableTitleTips(false);

	CString str;

	// Bit 15 ~ 8
	// Bit 7 ~ 0
	for (int col = 1; col < 9; col++) {
		str.Format(L"Bit %02d", 16 - col);
		mp_gridctrl->SetItemText(0, col, str);

		str.Format(L"Bit %02d", 7 - (col - 1));
		mp_gridctrl->SetItemText(1, col, str);

		mp_gridctrl->SetColumnWidth(col, 113); // column width
	}

	// Byte
	for (int i = 2; i < rowCount + 2; i++) {
		int word = (i - 2) / 2;
		str.Format(L"Byte %02d (W %02d)", i - 2, word);
		mp_gridctrl->SetItemText(i, 0, str);
		
		if (word % 2 == 0) {
			mp_gridctrl->SetItemBkColour(i, 0, (RGB(200, 120, 160)));
		}
		else {
			mp_gridctrl->SetItemBkColour(i, 0, (RGB(130, 130, 200)));
		}
	}
		
	// 그리드 초기화
	mp_gridctrl->ClearCells(CCellRange(2, 1, rowCount + 1, 8));
	_GFG::_GFG_InitItemBkColor(rowCount + 1, 8, mp_gridctrl);
	
	// 그리드 매핑.
	_GFG::_GFG_InitMakeGrid(fcode, 0x1A4, 0, mp_gridctrl);
		
	//mp_gridctrl->SetFocusCell(3, 1);	
	//mp_gridctrl->set(true);
}
//--------------------------------------------------------------------------------------------

void CForm_DuDefault_1::OnBnClickedDfsDefault2()
{		
	if (0x1A8 == m_port) return;
	m_port = 0x1A8;

	if (mp_gridctrl != NULL) {
		delete mp_gridctrl;
		mp_gridctrl = NULL;

		mp_gridctrl = new CGridCtrl;
		mp_gridctrl->Create(CRect(10, 45, 1018, 800), this, IDC_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER);
	}
	
	unsigned short fcode = 4;
	unsigned short rowCount = 2 << fcode;

	mp_gridctrl->SetRowCount(rowCount + 2);
	mp_gridctrl->SetColumnCount(8 + 1); // 현시할 column 8개, fixed column 1개

	mp_gridctrl->SetFixedRowCount(2);
	mp_gridctrl->SetFixedColumnCount(1);

	mp_gridctrl->SetFixedBkColor(RGB(200, 200, 200));
	mp_gridctrl->SetGridLineColor(RGB(128, 128, 255));
	
	// grid option	
	mp_gridctrl->SetTrackFocusCell(true);
	mp_gridctrl->SetEditable(false); // 셀 더블 클릭 하면 내용 수정할 수 없도록 막음.
	mp_gridctrl->EnableTitleTips(false);

	CString str;

	// Bit 15 ~ 8
	// Bit 7 ~ 0
	for (int col = 1; col < 9; col++) {
		str.Format(L"Bit %02d", 16 - col);
		mp_gridctrl->SetItemText(0, col, str);

		str.Format(L"Bit %02d", 7 - (col - 1));
		mp_gridctrl->SetItemText(1, col, str);

		mp_gridctrl->SetColumnWidth(col, 113); // column width
	}

	// Byte
	for (int i = 2; i < rowCount + 2; i++) {
		int word = (i - 2) / 2;
		str.Format(L"Byte %02d (W %02d)", i - 2, word);
		mp_gridctrl->SetItemText(i, 0, str);

		if (word % 2 == 0) {
			mp_gridctrl->SetItemBkColour(i, 0, (RGB(200, 120, 160)));
		}
		else {
			mp_gridctrl->SetItemBkColour(i, 0, (RGB(130, 130, 200)));
		}
	}

	// 그리드 초기화
	mp_gridctrl->ClearCells(CCellRange(2, 1, rowCount + 1, 8));
	_GFG::_GFG_InitItemBkColor(rowCount + 1, 8, mp_gridctrl);

	// 그리드 매핑.
	_GFG::_GFG_InitMakeGrid(fcode, 0x1A8, 0, mp_gridctrl);	
}
//--------------------------------------------------------------------------------------------

void CForm_DuDefault_1::OnBnClickedDfsDefault3()
{
	if (0x1AC == m_port) return;
	m_port = 0x1AC;

	if (mp_gridctrl != NULL) {
		delete mp_gridctrl;
		mp_gridctrl = NULL;

		mp_gridctrl = new CGridCtrl;
		mp_gridctrl->Create(CRect(10, 45, 1018, 800), this, IDC_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER);
	}

	unsigned short fcode = 4;
	unsigned short rowCount = 2 << fcode;

	mp_gridctrl->SetRowCount(rowCount + 2);
	mp_gridctrl->SetColumnCount(8 + 1); // 현시할 column 8개, fixed column 1개

	mp_gridctrl->SetFixedRowCount(2);
	mp_gridctrl->SetFixedColumnCount(1);

	mp_gridctrl->SetFixedBkColor(RGB(200, 200, 200));
	mp_gridctrl->SetGridLineColor(RGB(128, 128, 255));

	// grid option	
	mp_gridctrl->SetTrackFocusCell(true);
	mp_gridctrl->SetEditable(false); // 셀 더블 클릭 하면 내용 수정할 수 없도록 막음.
	mp_gridctrl->EnableTitleTips(false);

	CString str;

	// Bit 15 ~ 8
	// Bit 7 ~ 0
	for (int col = 1; col < 9; col++) {
		str.Format(L"Bit %02d", 16 - col);
		mp_gridctrl->SetItemText(0, col, str);

		str.Format(L"Bit %02d", 7 - (col - 1));
		mp_gridctrl->SetItemText(1, col, str);

		mp_gridctrl->SetColumnWidth(col, 113); // column width
	}

	// Byte
	for (int i = 2; i < rowCount + 2; i++) {
		int word = (i - 2) / 2;
		str.Format(L"Byte %02d (W %02d)", i - 2, word);
		mp_gridctrl->SetItemText(i, 0, str);

		if (word % 2 == 0) {
			mp_gridctrl->SetItemBkColour(i, 0, (RGB(200, 120, 160)));
		}
		else {
			mp_gridctrl->SetItemBkColour(i, 0, (RGB(130, 130, 200)));
		}
	}

	// 그리드 초기화
	mp_gridctrl->ClearCells(CCellRange(2, 1, rowCount + 1, 8));
	_GFG::_GFG_InitItemBkColor(rowCount + 1, 8, mp_gridctrl);

	// 그리드 매핑.
	_GFG::_GFG_InitMakeGrid(fcode, 0x1AC, 0, mp_gridctrl);
}
//--------------------------------------------------------------------------------------------

BOOL CForm_DuDefault_1::DestroyWindow()
{
	if (NULL != mp_gridctrl) {
		delete mp_gridctrl;
		mp_gridctrl = NULL;
	}

	return CFormView::DestroyWindow();
}
//--------------------------------------------------------------------------------------------

// Bit format
void CForm_DuDefault_1::OnGridClick(NMHDR *pNotifyStruct, LRESULT * /*pResult*/)
{
	NM_GRIDVIEW *pItem = (NM_GRIDVIEW *)pNotifyStruct;
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();
	Sheet *pSheet = mainDlg->mp_Libxl->sheetMap.find(m_port)->second;

	if (pItem->iRow == 0 || pItem->iRow == 1) return; // fix cells
	if (pItem->iColumn == 0 || pItem->iColumn == 9) return; // Unused cells in column.	
	if (pSheet->getMerge(pItem->iRow + 3, pItem->iColumn + 1, 0, 0, 0, 0)) return; // 병합된 셀인지 체크.

	int mvbIndex = binarySearch(mainDlg->mp_Libxl->mvb_Addr, 120, m_port);
	mvbIndex += mainDlg->mp_Libxl->m_totalNodeCnt * 0; // myNode라서 0을 곱함.

	// 공유 메모리에서 데이터 가져옴.
	unsigned char data_8bit;
	memcpy(&data_8bit, &mainDlg->m_pData->data[mvbIndex][pItem->iRow - 2], 1);

	// 공유 메모리에 데이터 세팅.
	unsigned char x = 7 - (pItem->iColumn - 1);
	data_8bit ^= 0x1 << x;
	memset(&mainDlg->m_pData->data[mvbIndex][pItem->iRow - 2], data_8bit, 1);

	// 셀색 변경.
	if ((data_8bit >> x) & 0x1)
		mp_gridctrl->SetItemBkColour(pItem->iRow, pItem->iColumn, RCLICK_RGB);
	else
		mp_gridctrl->SetItemBkColour(pItem->iRow, pItem->iColumn, WHITE_RGB);	
}
//--------------------------------------------------------------------------------------------

// Merge Cell
void CForm_DuDefault_1::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT * /*pResult*/)
{
	NM_GRIDVIEW *pItem = (NM_GRIDVIEW *)pNotifyStruct;
	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();
	Sheet *pSheet = mainDlg->mp_Libxl->sheetMap.find(m_port)->second;

	if (pItem->iRow == 0 || pItem->iRow == 1) return; // fix cells
	if (pItem->iColumn == 0 || pItem->iColumn == 9) return; // Unused cells in column.
	if (!pSheet->getMerge(pItem->iRow + 3, pItem->iColumn + 1, 0, 0, 0, 0)) return; // 병합된 셀인지 체크.
	
	CSetDataPopUp *pDataPopUp;
	pDataPopUp = new CSetDataPopUp(pItem->iRow, pItem->iColumn, m_port, 0, mp_gridctrl);
	pDataPopUp->Create(IDD_SETDATA_POPUP, this);
	pDataPopUp->ShowWindow(5); // 5 is SH_SHOWS
}
//--------------------------------------------------------------------------------------------