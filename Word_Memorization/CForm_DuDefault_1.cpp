// CForm_DuDefault_1.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CForm_DuDefault_1.h"

#include "Word_MemorizationDlg.h"
#include "_CExcelLib.h"
#include "DefineOfDev_J.h"

#include "CSharedMemory.h"

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
	

	if (m_flag == 1) return;

	m_flag = 1;

	//memset(clicked, 0, sizeof(clicked));

	CRect rc(10, 60, 1020, 850);
	
	mp_gridctrl = new CGridCtrl;
	mp_gridctrl->Create(rc, this, IDC_GRID, WS_CHILD | WS_VISIBLE | WS_BORDER);
		
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
		str.Format(L"Byte %02d", i - 2);
		mp_gridctrl->SetItemText(i, 0, str);
	}
	
	// column width
	for (int col = 1; col < 9; col++) {
		mp_gridctrl->SetColumnWidth(col, 114);
	}
	
	// Grid Setting
	bool bMerge = false;
	int mergeCol_start = 0;
	int mergeCol_finish = 0;

	// for()문의 조건 범위 기준은 엘셀의 읽어올 위치를 기준으로 잡고 설정함
	for (int row = 5; row < 37; row++) {	
		for (int col = 2; col < 11; col++) {			
			bMerge = pExcel->m_pDU_Default_1->getMerge(row, col, 0, 0, 0, 0); // row, col, &row_first, &row_last, &col_first, &col_last			

			// 병합이 되었다면...
			if (bMerge) {
				if (mergeCol_finish == 0) {
					mergeCol_start = col-1;				
					mergeCol_finish = col-2;
				}				
				mergeCol_finish++;
			}
			// 병합이 안되어 있다면...
			else {
				// 일반 비트 형식 
				if (0 == mergeCol_finish) {}
				// 병합된 크기 만큼 병합.
				else {
					int t_row = row - 3;
					mp_gridctrl->MergeCells(CCellRange(t_row, mergeCol_start, t_row, mergeCol_finish));

					mergeCol_start = 0;
					mergeCol_finish = 0;
				}
			}

		}
	}
	
	// Text
	for (int row = 2; row < 34; row++) {
		for (int col = 1; col < 9; col++) {
			mp_gridctrl->SetItemText(row, 9 - col, pExcel->GetDuDefaultValue(row - 2, col - 1, m_flag));
		}
	}
	

	//unsigned char t_buffer[32][8];
	unsigned char t_buffer[256];

/*
	BYTE l_byte, h_byte;
	int dataSize = sizeof(pExcel->mvb_Addr) / sizeof(WORD);
	int t_port = binarySearch(pExcel->mvb_Addr, dataSize, 0x1A4);

	//unsigned short value;
	//h_byte = ((unsigned char *)&value)[1]; // word 상위
	//l_byte = ((unsigned char *)&value)[0]; // word 하위

	//memset(&(mainDlg.m_pData->data[t_port][0]), h_byte, 1);   // mvb 상위 바이트에 값을 넣음
	//memset(&(mainDlg.m_pData->data[t_port][1]), l_byte, 1); // mvb 하위 바이트에 값을 넣음
	
	//memcpy(t_buffer, &(m_pData->data[m_signal[i].mem_Row][0]), MAX_DATA_COUNT_PER_PORT);

	//CheckData();

	//memset(t_buffer, 7, 32);
	//memcpy(&(mp_MainDlg->m_pData->data[t_port][0]), &t_buffer, 2);
*/
	
	bool b = false;
	b = mp_gridctrl->IsMergedCell(2, 1, CCellRange(0, 0, 0, 0));
	b = mp_gridctrl->IsMergedCell(10, 1, CCellRange(0, 0, 0, 0));
	b = mp_gridctrl->IsMergedCell(11, 1, CCellRange(-1,-1,-1,-1));
	b = mp_gridctrl->IsMergedCell(12, 1, CCellRange(0, 0, 0, 0));


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
	if (m_flag == 2) return;

	m_flag = 2;
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

	// 클릭된 위치 저장.
	//if (0 == clicked[pItem->iRow][pItem->iColumn]) {
	//	clicked[pItem->iRow][pItem->iColumn] = 1;
	//	mp_gridctrl->SetItemBkColour(pItem->iRow, pItem->iColumn, RCLICK_RGB);
	//}
	//else {
	//	clicked[pItem->iRow][pItem->iColumn] = 0;
	//	mp_gridctrl->SetItemBkColour(pItem->iRow, pItem->iColumn, RGB(255, 255, 255)); // 흰색
	//}
	
	mp_gridctrl->SetItemBkColour(pItem->iRow, pItem->iColumn, RCLICK_RGB); // test
	
	mp_gridctrl->RedrawCell(pItem->iRow, pItem->iColumn);
}
//--------------------------------------------------------------------------------------------

// byte format
void CForm_DuDefault_1::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT * /*pResult*/)
{
	NM_GRIDVIEW *pItem = (NM_GRIDVIEW *)pNotifyStruct;
	
	if (pItem->iRow == 0 || pItem->iRow == 1 || pItem->iColumn == 0) return; // fix cells

	mp_gridctrl->SetItemBkColour(pItem->iRow, pItem->iColumn, LDCLICK_RGB);
	mp_gridctrl->RedrawCell(pItem->iRow, pItem->iColumn);
}
//--------------------------------------------------------------------------------------------

void CForm_DuDefault_1::CheckData(int a_Row, int a_Column)
{
	
	//mp_gridctrl->SetItemBkColour(a_Row, a_Column, RCLICK_RGB);
}
//--------------------------------------------------------------------------------------------

void CForm_DuDefault_1::IsDataCheck(int a_Row, int a_Column)
{
	// Grid Setting
	bool bMerge = false;
	int mergeCol_start = 0;
	int mergeCol_finish = 0;

	// Shared Memory Data Check
	BYTE l_byte, h_byte;
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
					//else
						//mp_gridctrl->SetItemBkColour(row, col, WHITE_RGB);
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