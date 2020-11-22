// CDeviceProtocol.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CDeviceProtocol.h"
#include "afxdialogex.h"


// CDeviceProtocol dialog

IMPLEMENT_DYNAMIC(CDeviceProtocol, CDialogEx)

CDeviceProtocol::CDeviceProtocol(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROTOCOL_EXCEL_DLG, pParent)
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
END_MESSAGE_MAP()


// CDeviceProtocol message handlers


BOOL CDeviceProtocol::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mp_PT_Grid = new CGridCtrl;
	mp_PT_Grid->Create(CRect(10, 5, 1018, 760), this, IDC_PT_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER);

	mp_PT_Grid->SetRowCount(32 + 2);
	mp_PT_Grid->SetColumnCount(8 + 1); // 현시할 column 8개, fixed column 1개

	mp_PT_Grid->SetFixedRowCount(2);
	mp_PT_Grid->SetFixedColumnCount(1);

	mp_PT_Grid->SetFixedBkColor(RGB(200, 200, 200));

	// grid option
	mp_PT_Grid->SetGridLineColor(RGB(128, 128, 255));
	mp_PT_Grid->SetTrackFocusCell(true);
	mp_PT_Grid->SetEditable(true);

	mp_PT_Grid->EnableTitleTips(false);

	CString str;

	// Bit 7 ~ 0
	for (int i = 1; i < 9; i++) {
		str.Format(L"Bit %02d", 7 - (i - 1));
		mp_PT_Grid->SetItemText(1, i, str);
	}
	// Bit 15 ~ 8
	for (int i = 1; i < 9; i++) {
		str.Format(L"Bit %02d", 16 - i);
		mp_PT_Grid->SetItemText(0, i, str);
	}
	// Byte
	for (int i = 2; i < 34; i++) {
		int word = (i - 2) / 2;
		str.Format(L"Byte %02d (W %02d)", i - 2, word);
		mp_PT_Grid->SetItemText(i, 0, str);
	}

	// column width
	for (int col = 1; col < 9; col++) {
		mp_PT_Grid->SetColumnWidth(col, 114);
	}

	// 그리드 초기화
	mp_PT_Grid->ClearCells(CCellRange(2, 1, 33, 8));
	_GFG::_GFG_InitItemBkColor(33, 8, mp_PT_Grid);

	// 매개 변수 범위는 기준은 엑셀 기준이다.
	_GFG::_GFG_InitMakeGrid(5, 36, 2, 9, 0x1A4, mp_PT_Grid); // 비트 형식인지 병합한 형식인지 체크.
	_GFG::_GFG_SetWordFormatCell(5, 36, 2, 9, 0x1A4, mp_PT_Grid); // 병합한 형태이면 병합한 모양에 맞게 그리드에 그리기.

	// 매개 변수 범위는 그리드 컨트롤 기준이다.
	SetTextGrid(2, 33, 1, 8, m_flag);       // 그리드에 엑셀에 있는 텍스트 넣기. 

	_GFG::_GFG_GetBitDataFormSM(5, 36, 2, 9, 0x1A4, 0, mp_PT_Grid); // 데이터 체크를 해서 0이 아닌 값이 있으면 그리드 셀 색 변경 - 비트 형식
	_GFG::_GFG_GetMoreThanTwoBitsOfDataFormSM(5, 36, 2, 9, 0x1A4, 0, mp_PT_Grid); // 데이터 체크를 해서 0이 아닌 값이 있으면 그리드 셀 색 변경 - 병합된 형식.

	//mp_PT_Grid->SetFocusCell(3, 1);
	mp_PT_Grid->SetEditable(false);
	//mp_PT_Grid->set(true);

	return TRUE;  
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void CDeviceProtocol::OnClose()
{
	delete mp_PT_Grid;
	
	DestroyWindow();

	CDialogEx::OnClose();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+