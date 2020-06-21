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

void CForm_DuDefault_1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CForm_DuDefault_1, CFormView)
	ON_BN_CLICKED(IDC_DFS_DEFAULT_1, &CForm_DuDefault_1::OnBnClickedDfsDefault1)
	ON_BN_CLICKED(IDC_DFS_DEFAULT_2, &CForm_DuDefault_1::OnBnClickedDfsDefault2)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(LEditDown_Default_1, &CForm_DuDefault_1::OnLeditdownDefault1)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CForm_DuDefault_1 diagnostics

#ifdef _DEBUG
void CForm_DuDefault_1::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CForm_DuDefault_1::Dump(CDumpContext& dc) const
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
		if (control_id >= 20000 && control_id <= 20000 + m_fixedColumnCnt*2) {
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

afx_msg LRESULT CForm_DuDefault_1::OnLeditdownDefault1(WPARAM wParam, LPARAM lParam)
{

	return 0;
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
	if(nFlags == 30000)
		SetDlgItemText(30002, L"click");
	CFormView::OnLButtonDown(nFlags, point);
}
