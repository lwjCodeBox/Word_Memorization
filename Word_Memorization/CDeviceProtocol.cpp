// CDeviceProtocol.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CDeviceProtocol.h"
#include "afxdialogex.h"

#include "Grid_Func_Group.h"

// CDeviceProtocol dialog

IMPLEMENT_DYNAMIC(CDeviceProtocol, CDialogEx)

CDeviceProtocol::CDeviceProtocol(int a_port, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROTOCOL_EXCEL_DLG, pParent), m_port(a_port)
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
	mp_PT_Grid->Create(CRect(10, 5, 1018, 760), this, IDC_PT_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER); // 10, 5, 1018, 760

	mp_PT_Grid->SetRowCount(32 + 2);
	mp_PT_Grid->SetColumnCount(8 + 1); // ������ column 8��, fixed column 1��

	mp_PT_Grid->SetFixedRowCount(2);
	mp_PT_Grid->SetFixedColumnCount(1);

	mp_PT_Grid->SetFixedBkColor(RGB(200, 200, 200));

	// grid option
	mp_PT_Grid->SetGridLineColor(RGB(128, 128, 255));
	mp_PT_Grid->SetTrackFocusCell(true);
	mp_PT_Grid->SetEditable(true);
	mp_PT_Grid->SetEditable(false);
	mp_PT_Grid->EnableTitleTips(false);

	CString str;
	
	// bit
	for (int i = 1; i < 9; i++) {
		// column width
		mp_PT_Grid->SetColumnWidth(i, 114);

		// Bit 7 ~ 0
		str.Format(L"Bit %02d", 7 - (i - 1));
		mp_PT_Grid->SetItemText(1, i, str);

		// Bit 15 ~ 8
		str.Format(L"Bit %02d", 16 - i);
		mp_PT_Grid->SetItemText(0, i, str);
	}
		
	// Byte
	for (int i = 2; i < 34; i++) {
		int word = (i - 2) / 2;
		str.Format(L"Byte %02d (W %02d)", i - 2, word);
		mp_PT_Grid->SetItemText(i, 0, str);
	}	

	// �׸��� �ʱ�ȭ
	mp_PT_Grid->ClearCells(CCellRange(2, 1, 33, 8));
	_GFG::_GFG_InitItemBkColor(33, 8, mp_PT_Grid);

	// �Ű� ���� ������ ������ ���� �����̴�.
	_GFG::_GFG_InitMakeGrid(5, 36, 2, 9, m_port, mp_PT_Grid); // ��Ʈ �������� ������ �������� üũ.
	_GFG::_GFG_SetWordFormatCell(5, 36, 2, 9, m_port, mp_PT_Grid); // ������ �����̸� ������ ��翡 �°� �׸��忡 �׸���.

	// �Ű� ���� ������ �׸��� ��Ʈ�� �����̴�.
	_GFG::_GFG_SetTextGrid(2, 33, 1, 8, m_port, mp_PT_Grid);       // �׸��忡 ������ �ִ� �ؽ�Ʈ �ֱ�. 

	_GFG::_GFG_GetBitDataFormSM(5, 36, 2, 9, m_port, 0, mp_PT_Grid); // ������ üũ�� �ؼ� 0�� �ƴ� ���� ������ �׸��� �� �� ���� - ��Ʈ ����
	_GFG::_GFG_GetMoreThanTwoBitsOfDataFormSM(5, 36, 2, 9, m_port, 0, mp_PT_Grid); // ������ üũ�� �ؼ� 0�� �ƴ� ���� ������ �׸��� �� �� ���� - ���յ� ����.

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
