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

#ifdef Edit_and_ListControl_Sample_CODE	
void CForm_DuDefault_1::Clear_EditCtrl()
{
	if (mp_fixedRow != NULL) {
		for (int i = 0; i < m_fixedRowCnt; i++) {
			delete mp_fixedRow[i];
		}
		delete[] mp_fixedRow;
	}

	if (mp_fixedColumn != NULL) {
		for (int i = 0; i < 2; i++) {
			for (int sub_i = 0; sub_i < m_fixedColumnCnt; sub_i++) {
				delete mp_fixedColumn[i * m_fixedColumnCnt + sub_i];
			}
		}
		delete[] mp_fixedColumn;

	}

	if (mp_cedit != NULL) {
		for (int i = 0; i < m_row; i++) {
			for (int sub_i = 0; sub_i < m_column; sub_i++) {
				delete mp_cedit[i * m_column + sub_i];
			}
		}
		delete[] mp_cedit;
	}

	if (mp_setPos != NULL) delete[] mp_setPos;
}

void CForm_DuDefault_1::Create_EditCtrl(int a_Row, int a_Column)
{
	CString number_str;

	int fr_X = 30; // x 시작 좌표
	int fr_Y = 110; // y 시작 좌표
	int fr_W = 70; // 사각형의 폭
	int fr_H = 25; // 사각형의 높이

	m_fixedRowCnt = a_Row; //32;
	mp_fixedRow = new CEdit * [m_fixedRowCnt];

	for (int i = 0; i < m_fixedRowCnt; i++) {
		mp_fixedRow[i] = new CEdit();
		mp_fixedRow[i]->Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER | ES_CENTER,
			CRect(fr_X, fr_Y + i * fr_H, fr_X + fr_W, fr_Y + (i + 1) * fr_H),
			//this, 10000 + i * m_fixedRowCnt); 이건 두줄로 표기 할때 아래줄은 한자리수를 나타내고 윗줄은 두자리 수를 나타낼때 사용함.
			this, 10000 + i);

		number_str.Format(L"Byte %d", i);
		SetDlgItemText(10000 + i, number_str);

		//number_str.Format(L"%d", 10000 + i);
		//SetDlgItemText(10000 + i, number_str);
	}



	int fc_X = 100; // x 시작 좌표
	int fc_Y = 60; // y 시작 좌표
	int fc_W = 100; // 사각형의 폭
	int fc_H = 25; // 사각형의 높이

	m_fixedColumnCnt = a_Column; //8;
	mp_fixedColumn = new CEdit * [2 * m_fixedColumnCnt];

	for (int i = 0; i < 2; i++) {
		for (int sub_i = 0; sub_i < m_fixedColumnCnt; sub_i++) {
			mp_fixedColumn[i * m_fixedColumnCnt + sub_i] = new CEdit();
			mp_fixedColumn[i * m_fixedColumnCnt + sub_i]->Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER | ES_CENTER,
				//CRect(fc_X + i * fc_W, fc_Y, fc_X + (i + 1) * fc_W, fc_Y + fc_H),
				CRect(fc_X + sub_i * fc_W, fc_Y + i * fc_H, fc_X + (sub_i + 1) * fc_W, fc_Y + (i + 1) * fc_H),
				this, 20000 + i * m_fixedColumnCnt + sub_i);

			number_str.Format(L"Bit %d", 15 - (i * m_fixedColumnCnt + sub_i));
			SetDlgItemText(20000 + i * m_fixedColumnCnt + sub_i, number_str);

			//number_str.Format(L"%d", 20000 + i * m_fixedColumnCnt + sub_i);
			//SetDlgItemText(20000 + i * m_fixedColumnCnt + sub_i, number_str);
		}
	}


	int d_X = 100; // x 시작 좌표
	int d_Y = 110; // y 시작 좌표
	int d_W = 100; // 사각형의 폭
	int d_H = 25; // 사각형의 높이

	m_row = a_Row; // 32;
	m_column = a_Column; // 8;

	mp_cedit = new CEdit * [m_row * m_column];
	for (int i = 0; i < m_row; i++) {
		for (int sub_i = 0; sub_i < m_column; sub_i++) {
			mp_cedit[i * m_column + sub_i] = new CEdit();
			mp_cedit[i * m_column + sub_i]->Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER | WS_BORDER | ES_MULTILINE | ES_CENTER,
				CRect(d_X + sub_i * d_W, d_Y + i * d_H, d_X + (sub_i + 1) * d_W, d_Y + (i + 1) * d_H),
				this, 30000 + i * m_column + sub_i);
			// col 2 || row 5
			//SetDlgItemText(30000 + i * m_column + sub_i, pExcel->getExcelValue(i+5, m_column + sub_i + 2));
			number_str.Format(L"text %d", 30000 + i * m_column + sub_i);
			SetDlgItemText(30000 + i * m_column + sub_i, number_str);
		}
	}

	mp_setPos = new unsigned char[m_row * m_column];
	memset(mp_setPos, 0, m_row * m_column);
}
#endif


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
#ifdef Edit_and_ListControl_Sample_CODE
	mp_fixedRow = NULL;
	mp_fixedColumn = NULL;
	mp_cedit = NULL;
#endif
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
	//CWordMemorizationDlg mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();
	
	//if (m_flag == 1) return;

	m_flag = 1;

	//memset(clicked, 0, sizeof(clicked));

	if (mp_gridctrl == NULL) {
		mp_gridctrl = new CGridCtrl;
		mp_gridctrl->Create(CRect(10, 60, 1020, 850), this, IDC_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER);
	}
	else {
		delete mp_gridctrl;
		mp_gridctrl = NULL;

		mp_gridctrl = new CGridCtrl;
		mp_gridctrl->Create(CRect(10, 60, 1020, 850), this, IDC_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER);
	}

	mp_gridctrl->SetRowCount(32+2);
	mp_gridctrl->SetColumnCount(8 + 1); // 현시할 column 8개, fixed column 1개

	mp_gridctrl->SetFixedRowCount(2);
	mp_gridctrl->SetFixedColumnCount(1);

	mp_gridctrl->SetFixedBkColor(RGB(200, 200, 200));

	// grid option
	mp_gridctrl->SetGridLineColor(RGB(128, 128, 255));
	mp_gridctrl->SetTrackFocusCell(true);
	mp_gridctrl->SetEditable(true);

	mp_gridctrl->EnableTitleTips(false);

	CString str;
	
	// Bit 7 ~ 0
	for (int i = 1; i < 9; i++) {
		str.Format(L"Bit %02d", 7-(i - 1));
		mp_gridctrl->SetItemText(1, i, str);
	}
	// Bit 15 ~ 8
	for (int i = 1; i < 9; i++) {
		str.Format(L"Bit %02d", 16-i);
		mp_gridctrl->SetItemText(0, i, str);
	}
	// Byte
	for (int i = 2; i < 34; i++) {
		int word = (i - 2) / 2;
		str.Format(L"Byte %02d (W %02d)", i - 2, word);
		mp_gridctrl->SetItemText(i, 0, str);
	}
	
	// column width
	for (int col = 1; col < 9; col++) {
		mp_gridctrl->SetColumnWidth(col, 114);
	}
	
	// 그리드 초기화
	mp_gridctrl->ClearCells(CCellRange(2, 1, 33, 8));
	_GFG::_GFG_InitItemBkColor(33, 8, mp_gridctrl);
	
	// 매개 변수 범위는 기준은 엑셀 기준이다.
	_GFG::_GFG_InitMakeGrid(5, 36, 2, 9, 0x1A4, mp_gridctrl); // 비트 형식인지 병합한 형식인지 체크.
	_GFG::_GFG_SetWordFormatCell(5, 36, 2, 9, 0x1A4, mp_gridctrl); // 병합한 형태이면 병합한 모양에 맞게 그리드에 그리기.
	
	// 매개 변수 범위는 그리드 컨트롤 기준이다.
	SetTextGrid(2, 33, 1, 8, m_flag);       // 그리드에 엑셀에 있는 텍스트 넣기. 

	_GFG::_GFG_GetBitDataFormSM(5, 36, 2, 9, 0x1A4, 0, mp_gridctrl); // 데이터 체크를 해서 0이 아닌 값이 있으면 그리드 셀 색 변경 - 비트 형식
	_GFG::_GFG_GetMoreThanTwoBitsOfDataFormSM(5, 36, 2, 9, 0x1A4, 0, mp_gridctrl); // 데이터 체크를 해서 0이 아닌 값이 있으면 그리드 셀 색 변경 - 병합된 형식.

	//mp_gridctrl->SetFocusCell(3, 1);
	mp_gridctrl->SetEditable(false);
	//mp_gridctrl->set(true);

#ifdef Edit_and_ListControl_Sample_CODE
		Clear_EditCtrl(); // 에디트 창을 한번 초기화 한다.

		Create_EditCtrl(32, 8); // 원하는 사이즈 만큼 에디트를 만듬.

		pExcel->Read_DU_Default(m_flag); // 1의 의미는 DU default 1을 클릭 했다는 의미.

		if (mh_bk_fixed_row_col != NULL) {
			// 자신이 만든 Brush 객체를 제거한다.
			DeleteObject(mh_bk_fixed_row_col);
			mh_bk_fixed_row_col = NULL;
		}

		if (mh_bk_edit_row_col != NULL) {
			// 자신이 만든 Brush 객체를 제거한다.
			DeleteObject(mh_bk_edit_row_col);
			mh_bk_edit_row_col = NULL;
		}

		mh_bk_fixed_row_col = ::CreateSolidBrush(RGB(192, 192, 192));

		mh_bk_edit_row_col = ::CreateSolidBrush(RGB(128, 128, 255));
#endif
}
//--------------------------------------------------------------------------------------------

void CForm_DuDefault_1::OnBnClickedDfsDefault2()
{
	//if (m_flag == 2) return;

	m_flag = 2;

	if (mp_gridctrl != NULL) {
		delete mp_gridctrl;
		mp_gridctrl = NULL;

		mp_gridctrl = new CGridCtrl;
		mp_gridctrl->Create(CRect(10, 60, 1020, 850), this, IDC_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER);
	}
	
	mp_gridctrl->SetRowCount(32 + 2);
	mp_gridctrl->SetColumnCount(8 + 1); // 현시할 column 8개, fixed column 1개

	mp_gridctrl->SetFixedRowCount(2);
	mp_gridctrl->SetFixedColumnCount(1);

	mp_gridctrl->SetFixedBkColor(RGB(200, 200, 200));

	// grid option
	mp_gridctrl->SetGridLineColor(RGB(128, 128, 255));
	mp_gridctrl->SetTrackFocusCell(true);
	mp_gridctrl->SetEditable(true);

	mp_gridctrl->EnableTitleTips(false);

	CString str;

	// Bit 7 ~ 0
	for (int i = 1; i < 9; i++) {
		str.Format(L"Bit %02d", 7 - (i - 1));
		mp_gridctrl->SetItemText(1, i, str);
	}
	// Bit 15 ~ 8
	for (int i = 1; i < 9; i++) {
		str.Format(L"Bit %02d", 16 - i);
		mp_gridctrl->SetItemText(0, i, str);
	}
	// Byte
	for (int i = 2; i < 34; i++) {
		int word = (i - 2) / 2;
		str.Format(L"Byte %02d (W %02d)", i - 2, word);
		mp_gridctrl->SetItemText(i, 0, str);
	}

	// column width
	for (int col = 1; col < 9; col++) {
		mp_gridctrl->SetColumnWidth(col, 114);
	}

	// 그리드 초기화
	mp_gridctrl->ClearCells(CCellRange(2, 1, 33, 8));
	_GFG::_GFG_InitItemBkColor(33, 8, mp_gridctrl);

	// 매개 변수 범위는 기준은 엑셀 기준이다.
	_GFG::_GFG_InitMakeGrid(5, 36, 2, 9, 0x1A8, mp_gridctrl); // 비트 형식인지 병합한 형식인지 체크.             
	_GFG::_GFG_SetWordFormatCell(5, 36, 2, 9, 0x1A8, mp_gridctrl); // 병합한 형태이면 병합한 모양에 맞게 그리드에 그리기.

	// 매개 변수 범위는 그리드 컨트롤 기준이다.
	SetTextGrid(2, 33, 1, 8, m_flag);       // 그리드에 엑셀에 있는 텍스트 넣기. 

	_GFG::_GFG_GetBitDataFormSM(5, 36, 2, 9, 0x1A8, 0, mp_gridctrl); // 데이터 체크를 해서 0이 아닌 값이 있으면 그리드 셀 색 변경 - 비트 형식
	_GFG::_GFG_GetMoreThanTwoBitsOfDataFormSM(5, 36, 2, 9, 0x1A8, 0, mp_gridctrl); // 데이터 체크를 해서 0이 아닌 값이 있으면 그리드 셀 색 변경 - 병합된 형식.
}
//--------------------------------------------------------------------------------------------

void CForm_DuDefault_1::OnBnClickedDfsDefault3()
{
	//if (m_flag == 3) return;

	m_flag = 3;

	if (mp_gridctrl != NULL) {
		delete mp_gridctrl;
		mp_gridctrl = NULL;

		mp_gridctrl = new CGridCtrl;
		mp_gridctrl->Create(CRect(10, 60, 1020, 850), this, IDC_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER);
	}

	mp_gridctrl->SetRowCount(32 + 2);
	mp_gridctrl->SetColumnCount(8 + 1); // 현시할 column 8개, fixed column 1개

	mp_gridctrl->SetFixedRowCount(2);
	mp_gridctrl->SetFixedColumnCount(1);

	mp_gridctrl->SetFixedBkColor(RGB(200, 200, 200));

	// grid option
	mp_gridctrl->SetGridLineColor(RGB(128, 128, 255));
	mp_gridctrl->SetTrackFocusCell(true);
	mp_gridctrl->SetEditable(true);

	mp_gridctrl->EnableTitleTips(false);

	CString str;

	// Bit 7 ~ 0
	for (int i = 1; i < 9; i++) {
		str.Format(L"Bit %02d", 7 - (i - 1));
		mp_gridctrl->SetItemText(1, i, str);
	}
	// Bit 15 ~ 8
	for (int i = 1; i < 9; i++) {
		str.Format(L"Bit %02d", 16 - i);
		mp_gridctrl->SetItemText(0, i, str);
	}
	// Byte
	for (int i = 2; i < 34; i++) {
		int word = (i - 2) / 2;
		str.Format(L"Byte %02d (W %02d)", i - 2, word);
		mp_gridctrl->SetItemText(i, 0, str);
	}

	// column width
	for (int col = 1; col < 9; col++) {
		mp_gridctrl->SetColumnWidth(col, 114);
	}

	// 그리드 초기화
	mp_gridctrl->ClearCells(CCellRange(2, 1, 33, 8));
	_GFG::_GFG_InitItemBkColor(33, 8, mp_gridctrl);

	// 매개 변수 범위는 기준은 엑셀 기준이다.
	_GFG::_GFG_InitMakeGrid(5, 36, 2, 9, 0x1AC, mp_gridctrl); // 비트 형식인지 병합한 형식인지 체크.                    
	_GFG::_GFG_SetWordFormatCell(5, 36, 2, 9, 0x1AC, mp_gridctrl); // 병합한 형태이면 병합한 모양에 맞게 그리드에 그리기.

	// 매개 변수 범위는 그리드 컨트롤 기준이다.
	SetTextGrid(2, 33, 1, 8, m_flag);       // 그리드에 엑셀에 있는 텍스트 넣기. 

	_GFG::_GFG_GetBitDataFormSM(5, 36, 2, 9, 0x1AC, 0, mp_gridctrl); // 데이터 체크를 해서 0이 아닌 값이 있으면 그리드 셀 색 변경 - 비트 형식
	_GFG::_GFG_GetMoreThanTwoBitsOfDataFormSM(5, 36, 2, 9, 0x1AC, 0, mp_gridctrl); // 데이터 체크를 해서 0이 아닌 값이 있으면 그리드 셀 색 변경 - 병합된 형식.
}
//--------------------------------------------------------------------------------------------

BOOL CForm_DuDefault_1::DestroyWindow()
{
	if (NULL != mp_gridctrl) {
		delete mp_gridctrl;
		mp_gridctrl = NULL;
	}


#ifdef Edit_and_ListControl_Sample_CODE
	Clear_EditCtrl();

	if (mh_bk_fixed_row_col != NULL) {
		// 자신이 만든 Brush 객체를 제거한다.
		DeleteObject(mh_bk_fixed_row_col);
		mh_bk_fixed_row_col = NULL;
	}

	if (mh_bk_edit_row_col != NULL) {
		// 자신이 만든 Brush 객체를 제거한다.
		DeleteObject(mh_bk_edit_row_col);
		mh_bk_edit_row_col = NULL;
	}
#endif
	return CFormView::DestroyWindow();
}
//--------------------------------------------------------------------------------------------

#ifdef Edit_and_ListControl_Sample_CODE
HBRUSH CForm_DuDefault_1::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// 갱신되는 컨트롤의 ID를 얻는다.
	int control_id = pWnd->GetDlgCtrlID();
	// 컨트롤의 ID가 내가 원하는 ID인지 체크한다.
	if (control_id >= 10000 && control_id <= 10992) {
		// Focus를 가진 윈도우의 핸들 값을 얻는다.
		HWND cur_focus = ::GetFocus();
		// 현재 그림을 그리는 컨트롤과 핸들이 일치하는지 체크한다.
		if (cur_focus == pWnd->m_hWnd) {
			// 이전에 focus를 가지고 있던 윈도우가 있다면 해당 윈도우를 갱신하도록
			// InvalidateRect 함수를 호출합니다.
			if (mh_old_focus != cur_focus) {
				if (mh_old_focus != NULL) ::InvalidateRect(mh_old_focus, NULL, TRUE);
				// 현재 컨트롤의 핸들을 기억시킨다.
				mh_old_focus = cur_focus;
			}
			// 입력 상태에 있는 컨트롤은 텍스트 색상을 밝게 표시한다.
			pDC->SetTextColor(RGB(0, 255, 255));
		}
		else {
			// 입력 상태가 아닌 컨트롤은 텍스트 색상을 어둡게 표시한다.
			pDC->SetTextColor(RGB(0, 168, 168));
		}
		// 텍스트의 배경 색상을 설정한다.
		pDC->SetBkColor(RGB(0, 0, 128));
		// Edit 컨트롤의 배경색으로 사용할 Brush 핸들 값을 반환한다.
		return mh_edit_bk_brush;
	}
	return hbr;
}
#endif

#ifdef Edit_and_ListControl_Sample_CODE
// https://lafirr.tistory.com/5
void CForm_DuDefault_1::OnCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult)
{
	COLORREF text_color = 0;
	COLORREF bg_color = RGB(255, 255, 255);
	
		NMLVCUSTOMDRAW *lplvcd = reinterpret_cast<NMLVCUSTOMDRAW *>(pNMHDR);
		*pResult = 0;

		switch (lplvcd->nmcd.dwDrawStage) {
		case CDDS_PREPAINT:
			*pResult = CDRF_NOTIFYITEMDRAW;
			return;

			// 배경 혹은 텍스트를 수정한다.
		case CDDS_ITEMPREPAINT:
			// 1번째 열 빨간색, 2번째 열 녹색, 3번째 이하는 파란색의 글자색을 갖는다.
			if (lplvcd->nmcd.dwItemSpec == 0) text_color = RGB(255, 0, 0);
			else if (lplvcd->nmcd.dwItemSpec == 1) text_color = RGB(0, 255, 0);
			else text_color = RGB(0, 0, 255);
			lplvcd->clrText = text_color;
			*pResult = CDRF_NOTIFYITEMDRAW;
			return;

			// 서브 아이템의 배경 혹은 텍스트를 수정한다.
		case CDDS_SUBITEM | CDDS_PREPAINT | CDDS_ITEM:
			if (lplvcd->iSubItem != 0) {
				// 1번째 행이라면...
				if (lplvcd->iSubItem == 1) {
					text_color = RGB(0, 127, 127);
					bg_color = RGB(255, 255, 255);
				}
				else {
					text_color = RGB(255, 255, 255);
					if (lplvcd->nmcd.dwItemSpec == 0) bg_color = RGB(255, 0, 102);
					else if (lplvcd->nmcd.dwItemSpec == 1) bg_color = RGB(255, 0, 0);
					else bg_color = RGB(0, 102 - (int)lplvcd->nmcd.dwItemSpec,
						204 - (int)lplvcd->nmcd.dwItemSpec * 2);
				}
				lplvcd->clrText = text_color;
				lplvcd->clrTextBk = bg_color;
			}
			*pResult = CDRF_NEWFONT;
			return;
		}
	


	/* 한 줄씩 다른 색으로 칠하기
		NMLVCUSTOMDRAW *pLVCD = reinterpret_cast<NMLVCUSTOMDRAW *>(pNMHDR);
		*pResult = 0;

		if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
		{
			*pResult = CDRF_NOTIFYITEMDRAW;
		}
		else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
		{
			if ((pLVCD->nmcd.dwItemSpec % 2) == 0)
			{
				pLVCD->clrText = RGB(0, 0, 0);
				pLVCD->clrTextBk = RGB(230, 230, 230);
			}
			else
			{
				pLVCD->clrText = RGB(255, 0, 0);
				pLVCD->clrTextBk = RGB(255, 255, 255);
			}
			*pResult = CDRF_DODEFAULT;
		}
	*/
}
#endif

// bit format
void CForm_DuDefault_1::OnGridClick(NMHDR *pNotifyStruct, LRESULT * /*pResult*/)
{
	NM_GRIDVIEW *pItem = (NM_GRIDVIEW *)pNotifyStruct;
		
	if (pItem->iRow == 0 || pItem->iRow == 1 || pItem->iColumn == 0) return; // fix cells
		
	//  0이 아니라면 병합된 셀을 의미 하기 떄문에 병합된 셀에서 우클릭을 할 경우 이 함수를 리턴해 버린다. 
	if (IsMergeCheck(pItem->iRow, pItem->iColumn, m_flag) != 0) return;

	CWordMemorizationDlg *mainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();
	_CExcelLib *p_ExcelLib = (_CExcelLib *)mainDlg->mp_Libxl;

	WORD portAddr = 0;
	switch (m_flag) {
	case 1:
		portAddr = 0x1A4;	break;
	case 2:
		portAddr = 0x1A8;	break;
	case 3:
		portAddr = 0x1AC;	break;
	}
	
	// 120의 의미는 myNode의 총 갯수를 의미 한다. 계산 법은 다음과 같다.
	// int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
	int t_port = binarySearch(p_ExcelLib->mvb_Addr, 120, portAddr);
	WORD t_WordPos = (pItem->iRow - 2) / 2;
	WORD smData = mainDlg->GetWordDataFromSM(portAddr, 0, t_WordPos); // (WORD a_PortAddr, BYTE a_Node, BYTE a_Word)
	
	BYTE colPos = 7 - (pItem->iColumn - 1);
	if (pItem->iRow % 2 == 0) colPos += 8;

	mainDlg->SetBitDataToSM(portAddr, 0, t_WordPos, colPos, smData);

	// Returns cell background color
	if (mp_gridctrl->GetCell(pItem->iRow, pItem->iColumn)->GetBackClr() != RCLICK_RGB) {
		mp_gridctrl->SetItemBkColour(pItem->iRow, pItem->iColumn, RCLICK_RGB);
	}
	else
		mp_gridctrl->SetItemBkColour(pItem->iRow, pItem->iColumn, WHITE_RGB);

	mp_gridctrl->RedrawCell(pItem->iRow, pItem->iColumn);

	p_ExcelLib = NULL;
	mainDlg = NULL;
}
//--------------------------------------------------------------------------------------------

// Merge Cell
void CForm_DuDefault_1::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT * /*pResult*/)
{
	NM_GRIDVIEW *pItem = (NM_GRIDVIEW *)pNotifyStruct;
	
	if (pItem->iRow == 0 || pItem->iRow == 1 || pItem->iColumn == 0) return; // fix cells
	
	//  0이라면 병합되지 않은 셀을 의미 하기 떄문에 병합되지 않은 셀을 더블 클릭하면 리턴한다. 
	if (IsMergeCheck(pItem->iRow, pItem->iColumn, m_flag) == 0) return;

	/*if (mp_gridctrl->GetCell(pItem->iRow, pItem->iColumn)->GetBackClr() != LDCLICK_RGB) {
		
		CString cStr = GetTextFormExcel(pItem->iRow, pItem->iColumn, *ppSheet);
		wchar_t *wtext = cStr.GetBuffer(cStr.GetLength()); 

		mp_gridctrl->SetItemBkColour(pItem->iRow, pItem->iColumn, LDCLICK_RGB);
	}
	else {
		mp_gridctrl->SetItemBkColour(pItem->iRow, pItem->iColumn, WHITE_RGB);
	}*/
	//5, 36, 2, 9, 0x1A4, mp_gridctrl

	WORD portAddr = 0;
	switch (m_flag) {
	case 1:
		portAddr = 0x1A4;	break;
	case 2:
		portAddr = 0x1A8;	break;
	case 3:
		portAddr = 0x1AC;	break;
	}

	//_GFG::_GFG_GetMoreThanTwoBitsOfDataFormSM(pItem->iRow + 3, pItem->iRow + 1, 2, 9, portAddr, 0, mp_gridctrl);
	
	CSetDataPopUp *pDataPopUp;
	pDataPopUp = new CSetDataPopUp(pItem->iRow, pItem->iColumn, portAddr, 0, mp_gridctrl);
	pDataPopUp->Create(IDD_SETDATA_POPUP);
	pDataPopUp->ShowWindow(5); // 5 is SH_SHOWS

	//mp_gridctrl->RedrawCell(pItem->iRow, pItem->iColumn);
}
//--------------------------------------------------------------------------------------------

int CForm_DuDefault_1::IsMergeCheck(int a_Row, int a_Column, int a_flag)
{
	Sheet **ppSheet = NULL;

	if (a_flag == 1)	  ppSheet = &pExcel->m_pDU_Default_1;
	else if (a_flag == 2) ppSheet = &pExcel->m_pDU_Default_2;
	else if (a_flag == 3) ppSheet = &pExcel->m_pDU_Default_3;

	int row_first = 5, row_last = 36;
	int col_first = 2, col_last = 9;

	bool bMerge = false;
	int mergeCount = 0;

	col_last++;

	for (int col = a_Column+1; col <= col_last; col++) {
		bMerge = (*ppSheet)->getMerge(a_Row+3, col, 0, 0, 0, 0);

		// 병합이 되었다면...
		if (bMerge) mergeCount++;
		else {
			ppSheet = NULL;
			return mergeCount;
		}

		// Check Word Fomat
		if (mergeCount == 8) {
			// 짝수가 나오면 워드 단위로 읽고 홀수가 나오면 클릭한 위치의 다음 행의 병합 상태는 체크 하지 않는다.
			// 그래야 클릭한 셀이 바이트 단위 인지 워드 단위 인지 알 수 있다.
			unsigned char rowPos = a_Row % 2;

			col_last--; // 엑셀 범위를 맞추기 위해서 다시 하나 감소시킨다. 

			(*ppSheet)->getMerge(a_Row + 4, 2, &row_first, &row_last, &col_first, &col_last); // +4를 하는 이유는 클릭한 행의 아래 행에 위치한 엑셀을 읽어 오기 위함이다.
			// 처음 행과 마지막 행을 비교하는 이유는 바이트 형식이면 두 변수(t_row_first, t_row_last)의 값이 같게 되지만 워드 형식이면 두 변수의 값이 다르다.
			if ((row_first != row_last) && (rowPos == 0)) {
				return 16; // 워드 포멧
			}
			else {
				ppSheet = NULL;
				return mergeCount;
			}
		}
	}

	// 조건에 맞지 않게 동작했다면 아래 코드를 타게됨.
	ppSheet = NULL;
	return -1;
}
//--------------------------------------------------------------------------------------------

void CForm_DuDefault_1::IsDataCheck(int a_Row, int a_Column)
{
	// Grid Setting
	bool bMerge = false;
	int mergeCol_start = 0;
	int mergeCol_finish = 0;

	// Shared Memory Data Check
	//BYTE l_byte, h_byte;
	int dataSize = sizeof(pExcel->mvb_Addr) / sizeof(WORD);
	int t_port = binarySearch(pExcel->mvb_Addr, dataSize, 0x1A4);
	unsigned char data;

	// for()문의 조건 범위 기준은 엘셀의 읽어올 위치를 기준으로 잡고 설정함
	for (int row = 0; row <= a_Row; row++) {
		for (int col = 0; col <= a_Column; col++) {
			bMerge = pExcel->m_pDU_Default_1->getMerge(row+5, col+2, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last			

			// 병합이 되었다면...
			if (bMerge) {
				if (mergeCol_finish == 0) {
					mergeCol_start = col - 1;
					mergeCol_finish = col - 2;
				}
				mergeCol_finish++;
			}
			// 병합이 안되어 있다면...
			else {
				// 일반 비트 형식 
				if (0 == mergeCol_finish) {
					int pos = row - 5;
					data = mp_MainDlg->m_pData->data[t_port][pos];

					int shift = 7 % (col - 2);

					if (((data >> shift) & 0x01) == 0x01)
						mp_gridctrl->SetItemBkColour(row, col, RCLICK_RGB);
				}
				// 병합된 크기 만큼 병합.
				else {
					int t_row = row - 3;
					mp_gridctrl->MergeCells(CCellRange(t_row, mergeCol_start, t_row, mergeCol_finish));

					mp_gridctrl->SetItemBkColour(t_row, mergeCol_start, LDCLICK_RGB);

					mergeCol_start = 0;
					mergeCol_finish = 0;
				}
			}
		}
	}
}
//--------------------------------------------------------------------------------------------

void CForm_DuDefault_1::SetTextGrid(int a_RowFirst, int a_RowLast, int a_ColFirst, int a_ColLast, int a_flag)
{
	for (int row = a_RowFirst; row <= a_RowLast; row++) {
		for (int col = a_ColFirst; col <= a_ColLast; col++) {
			mp_gridctrl->SetItemText(row, 9 - col, pExcel->GetDuDefaultValue(row - 2, col - 1, a_flag));
		}
	}
}
//--------------------------------------------------------------------------------------------

void CForm_DuDefault_1::InitItemBkColor(int a_rowLast, int a_colLast)
{
	for (int row = 2; row <= a_rowLast; row++) {
		for (int col = 1; col <= a_colLast; col++) {
			mp_gridctrl->SetItemBkColour(row, col, WHITE_RGB);
		}
	}
}
//--------------------------------------------------------------------------------------------