// CForm_DuDefault_1.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CForm_DuDefault_1.h"

//#include "Word_MemorizationDlg.h"
#include "_CExcelLib.h"

// CForm_DuDefault_1

IMPLEMENT_DYNCREATE(CForm_DuDefault_1, CFormView)

CForm_DuDefault_1::CForm_DuDefault_1()
	: CFormView(IDD_FORM_DU_DEFAULT)
{

}

CForm_DuDefault_1::CForm_DuDefault_1(_CExcelLib *a_Libxl)
	: CFormView(IDD_FORM_DU_DEFAULT), pExcel(a_Libxl)
{

}

CForm_DuDefault_1::~CForm_DuDefault_1()
{
}

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

		/*number_str.Format(L"%d", 10000 + i);
		SetDlgItemText(10000 + i, number_str);*/
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

			/*number_str.Format(L"%d", 20000 + i * m_fixedColumnCnt + sub_i);
			SetDlgItemText(20000 + i * m_fixedColumnCnt + sub_i, number_str);*/
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

void CForm_DuDefault_1::DoDataExchange(CDataExchange *pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CForm_DuDefault_1, CFormView)
	ON_BN_CLICKED(IDC_DFS_DEFAULT_1, &CForm_DuDefault_1::OnBnClickedDfsDefault1)
	ON_BN_CLICKED(IDC_DFS_DEFAULT_2, &CForm_DuDefault_1::OnBnClickedDfsDefault2)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LISTCONTROL, &CForm_DuDefault_1::OnCustomdrawList)
	ON_NOTIFY(NM_CLICK, IDC_LISTCONTROL, &CForm_DuDefault_1::OnNMClickList)
END_MESSAGE_MAP()

//ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST, OnCustomdrawList)

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
	mp_fixedRow = NULL;
	mp_fixedColumn = NULL;
	mp_cedit = NULL;
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CForm_DuDefault_1::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}


void CForm_DuDefault_1::OnBnClickedDfsDefault1()
{
	//mp_MainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	if (m_flag == 1) return;

	m_flag = 1;

	CRect rect(10, 60, 980, 800);

	mp_Grid = new CListCtrl;
	mp_Grid->Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | LVS_REPORT | LVS_ALIGNLEFT | WS_BORDER | WS_TABSTOP, rect, this, 10000);

	// 헤더 컨트롤을 고정 시켜버림 (열의 간격을 조정하지 못함)
	mp_Grid->GetHeaderCtrl()->EnableWindow(false);


	mp_Grid->SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);



	mp_Grid->DeleteAllItems();

	// 리스트 스타일 설정
	//LVS_EX_FULLROWSELECT  : 아이템을 선택할 때 한 줄 전체를 반전시킨다.
	//LVS_EX_GRIDLINES      : 각 아이템에 경계선을 그려준다.
	//LVS_EX_CHECKBOXES     : 각 아이템에 Check Box를 표시해 준다.
	//LVS_EX_HEADERDRAGDROP : 컬럼 헤더를 드래그 함으로써 컬럼의 순서를 바꿀 수 있게 해준다.
	mp_Grid->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	// 타이틀 삽입 
	mp_Grid->InsertColumn(0, _T("첫 번째 타이틀"), LVCFMT_LEFT, 200, -1); // 왼쪽 정렬
	mp_Grid->InsertColumn(1, _T("두 번째 타이틀"), LVCFMT_RIGHT, 109, -1); // 오른쪽 정렬
	mp_Grid->InsertColumn(2, _T("세 번째 타이틀"), LVCFMT_CENTER, 109, -1); // 가운데 정렬




	// Row 0 
	mp_Grid->InsertItem(0, _T("1."));
	mp_Grid->InsertItem(1, _T("2."));
	mp_Grid->InsertItem(2, _T("3."));
	mp_Grid->InsertItem(3, _T("4."));
	mp_Grid->InsertItem(4, _T("5."));

	// 첫번째 인자는 행, 두번째 인자는 열을 의마한다. 
	mp_Grid->SetItem(0, 1, LVIF_TEXT, _T("0행 1열"), 0, 0, 0, NULL);
	mp_Grid->SetItem(1, 1, LVIF_TEXT, _T("1행 1열"), 0, 0, 0, NULL);
	mp_Grid->SetItem(2, 1, LVIF_TEXT, _T("2행 1열"), 0, 0, 0, NULL);
	mp_Grid->SetItem(3, 1, LVIF_TEXT, _T("3행 1열"), 0, 0, 0, NULL);
	mp_Grid->SetItem(4, 1, LVIF_TEXT, _T("4행 1열"), 0, 0, 0, NULL);

	m_hOldFont = NULL;
	m_hFont.CreateFont(16, 0, 0, 0, FW_HEAVY, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"console");


	/* 리스트 컨트롤 테스트 해보기 위해 막음
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
	*/

#ifdef TEST_CODE
	if (mh_edit_bk_brush != NULL) {
		// 자신이 만든 Brush 객체를 제거한다.
		DeleteObject(mh_edit_bk_brush);
		mh_edit_bk_brush = NULL;
	}

	// Edit 컨트롤의 배경색으로 사용할 Brush 객체를 생성합니다.
	mh_edit_bk_brush = ::CreateSolidBrush(RGB(0, 0, 128));
#endif // TEST_CODE

}


void CForm_DuDefault_1::OnBnClickedDfsDefault2()
{
	if (m_flag == 2) return;

	m_flag = 2;
}


BOOL CForm_DuDefault_1::DestroyWindow()
{
	//Clear_EditCtrl();

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

#ifdef TEST_CODE
	if (mh_edit_bk_brush != NULL) {
		// 자신이 만든 Brush 객체를 제거한다.
		DeleteObject(mh_edit_bk_brush);
		mh_edit_bk_brush = NULL;
	}
#endif
	return CFormView::DestroyWindow();
}


HBRUSH CForm_DuDefault_1::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// 갱신되는 컨트롤의 ID를 얻는다.
	int control_id = pWnd->GetDlgCtrlID();

	// 값이 1이면 고정 row의 정보가 들어온거임.
	// 값이 2이면 고정 column의정보가 들어온거임.
	// 값이 3이면 데이터를 세팅하는 에디트의 정보가 들어온거임.
	int flag = control_id / 10000; // 값이 1이면 고정 row의 정보가 들어온거고 
	switch (flag) {
	case 1: // fixed Row
		// 컨트롤의 ID가 내가 원하는 ID인지 체크한다.
		if (control_id >= 10000 && control_id <= 10000 + m_fixedRowCnt) {
			// 텍스트의 배경 색상을 설정한다.
			pDC->SetBkColor(RGB(192, 192, 192));
			// Edit 컨트롤의 배경색으로 사용할 Brush 핸들 값을 반환한다.
			return mh_bk_fixed_row_col;
		}

	case 2: // fixed column
		// 컨트롤의 ID가 내가 원하는 ID인지 체크한다.
		if (control_id >= 20000 && control_id <= 20000 + m_fixedColumnCnt * 2) {
			// 텍스트의 배경 색상을 설정한다.
			pDC->SetBkColor(RGB(192, 192, 192));
			// Edit 컨트롤의 배경색으로 사용할 Brush 핸들 값을 반환한다.
			return mh_bk_fixed_row_col;
		}

	case 3: // normal row, column
		// 컨트롤의 ID가 내가 원하는 ID인지 체크한다.
		if (control_id >= 30000 && control_id <= 30000 + (m_row * m_column)) {
			//// 텍스트의 배경 색상을 설정한다.
			//pDC->SetBkColor(RGB(128, 128, 255));

			pDC->SetBkColor(RGB(128, 128, 255));

			// Edit 컨트롤의 배경색으로 사용할 Brush 핸들 값을 반환한다.
			return mh_bk_edit_row_col;
		}
	}

#ifdef TEST_CODE	
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
#endif
	return hbr;
}

/*
int control_id = GetDlgCtrlID();
		if (control_id >= 30000 && control_id <= 30000 + (m_row * m_column)) {
			//0x0400 + 1
			int id = 1024 + (control_id - 30000) + 1;
			this->PostMessage(id, 0, 0);
		}
*/



void CForm_DuDefault_1::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int num = 10;
	num = 8;
	CFormView::OnLButtonDown(nFlags, point);
}



/*
void CForm_DuDefault_1::OnCustomdrawDfsDefault1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;

	int nRow, nSub;


	switch (lplvcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;          // 아이템외에 일반적으로 처리하는 부분
		lplvcd->clrTextBk = RGB(0, 0, 255);
		break;



	case CDDS_ITEMPREPAINT:                          // 행 아이템에 대한 처리를 할 경우
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		break;



	case CDDS_ITEMPREPAINT | CDDS_SUBITEM:  // 행과 열 아이템에 대한 처리를 할 경우
		nRow = (int)lplvcd->nmcd.dwItemSpec;         // 행 인덱스를 가져옴
		nSub = (int)lplvcd->iSubItem;                       // 열 인덱스를 가져옴



// 해당 부분에 if 조건문을 통해 원하는 값에 대한 색상을 변경 할수 있다.

// 예를들면 해당 행과 열의 리스트의 값을 비교하거나, 해당 행과 열 인덱스를 비교한다.
		//if()
		//{

		//	lplvcd->clrTextBk = RGB(255, 255, 255);           // 해당 행, 열 아이템의 배경색을 지정한다.

		//	lplvcd->clrText = RGB(0, 0, 0);                      // 해당 행, 열 아이템의 글자색을 지정한다.

		//}

		//// 해당 부분에 if 조건문을 통해 원하는 값에 대한 폰트를 변경 할수 있다.
		//if()
		//{

		//	CDC *pDC = CDC::FromHandle(lplvcd->nmcd.hdc);
		//	hOldFont = (CFont *)pDC->SelectObject(&hFont);

		//}

		//   else

		//   {

		//   // hOldFont로 되돌린다.

		//   CDC *pDC = CDC::FromHandle(lplvcd->nmcd.hdc);
		//   pDC->SelectObject(hOldFont);

		//	}

			break;


		https://blog.naver.com/hjloveu012/80120437871
	default:
		*pResult = CDRF_DODEFAULT;

		break;
	}


}
*/

//BOOL CForm_DuDefault_1::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pLResult)
//{
//	// TODO: Add your specialized code here and/or call the base class
//
//	return CFormView::OnChildNotify(message, wParam, lParam, pLResult);
//}


// https://lafirr.tistory.com/5
void CForm_DuDefault_1::OnCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult)
{
	COLORREF text_color = 0;
	COLORREF bg_color = RGB(255, 255, 255);
	/*
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
	*/


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

void CForm_DuDefault_1::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);


	//int index = pNMItemActivate->iItem;
	//int subItem = pNMItemActivate->iSubItem;

	////int index = mp_Grid->GetSelectionMark();
	//if (index != -1) {
	//	CString str = L"TEST";
	//	if (index == 1) {
	//		mp_Grid->SetItemText(index, subItem, str);
	//		mp_Grid->SetBkColor(RGB(200, 200, 200));
	//	}
	//	else if (index == 2) {
	//		mp_Grid->SetItemText(index, subItem, str);
	//		mp_Grid->SetBkColor(RGB(200, 200, 200));
	//	}
	//	

	//	else if (index == 3) {
	//		mp_Grid->SetItemText(index, subItem, str);
	//		mp_Grid->SetBkColor(RGB(200, 200, 200));
	//	}
	//	

	//	else {
	//		mp_Grid->SetItemText(index, subItem, str);
	//		mp_Grid->SetBkColor(RGB(200, 200, 200));
	//	}
	//	
	//}

	int selectIndex, subItem;
	POSITION pos = mp_Grid->GetFirstSelectedItemPosition();
	selectIndex = mp_Grid->GetNextItem(-1, LVNI_SELECTED);
	subItem = pNMItemActivate->iSubItem;


	//CString result = mp_Grid->GetItemText(selectIndex, 1);
	CString temp;
	temp.Format(L"selectIndex : %d, subItem : %d", selectIndex, subItem);
	AfxMessageBox(temp);


	*pResult = 0;
}
