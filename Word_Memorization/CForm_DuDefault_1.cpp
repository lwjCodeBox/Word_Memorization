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

	int fr_X = 30; // x ���� ��ǥ
	int fr_Y = 110; // y ���� ��ǥ
	int fr_W = 70; // �簢���� ��
	int fr_H = 25; // �簢���� ����

	m_fixedRowCnt = a_Row; //32;
	mp_fixedRow = new CEdit * [m_fixedRowCnt];

	for (int i = 0; i < m_fixedRowCnt; i++) {
		mp_fixedRow[i] = new CEdit();
		mp_fixedRow[i]->Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER | ES_CENTER,
			CRect(fr_X, fr_Y + i * fr_H, fr_X + fr_W, fr_Y + (i + 1) * fr_H),
			//this, 10000 + i * m_fixedRowCnt); �̰� ���ٷ� ǥ�� �Ҷ� �Ʒ����� ���ڸ����� ��Ÿ���� ������ ���ڸ� ���� ��Ÿ���� �����.
			this, 10000 + i);

		number_str.Format(L"Byte %d", i);
		SetDlgItemText(10000 + i, number_str);

		/*number_str.Format(L"%d", 10000 + i);
		SetDlgItemText(10000 + i, number_str);*/
	}



	int fc_X = 100; // x ���� ��ǥ
	int fc_Y = 60; // y ���� ��ǥ
	int fc_W = 100; // �簢���� ��
	int fc_H = 25; // �簢���� ����

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


	int d_X = 100; // x ���� ��ǥ
	int d_Y = 110; // y ���� ��ǥ
	int d_W = 100; // �簢���� ��
	int d_H = 25; // �簢���� ����

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

	Clear_EditCtrl(); // ����Ʈ â�� �ѹ� �ʱ�ȭ �Ѵ�. 

	Create_EditCtrl(32, 8); // ���ϴ� ������ ��ŭ ����Ʈ�� ����.

	pExcel->Read_DU_Default(m_flag); // 1�� �ǹ̴� DU default 1�� Ŭ�� �ߴٴ� �ǹ�.

	if (mh_bk_fixed_row_col != NULL) {
		// �ڽ��� ���� Brush ��ü�� �����Ѵ�.
		DeleteObject(mh_bk_fixed_row_col);
		mh_bk_fixed_row_col = NULL;
	}

	if (mh_bk_edit_row_col != NULL) {
		// �ڽ��� ���� Brush ��ü�� �����Ѵ�.
		DeleteObject(mh_bk_edit_row_col);
		mh_bk_edit_row_col = NULL;
	}

	mh_bk_fixed_row_col = ::CreateSolidBrush(RGB(192, 192, 192));
	
	mh_bk_edit_row_col = ::CreateSolidBrush(RGB(128, 128, 255));

#ifdef TEST_CODE
	if (mh_edit_bk_brush != NULL) {
		// �ڽ��� ���� Brush ��ü�� �����Ѵ�.
		DeleteObject(mh_edit_bk_brush);
		mh_edit_bk_brush = NULL;
	}

	// Edit ��Ʈ���� �������� ����� Brush ��ü�� �����մϴ�.
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
		// �ڽ��� ���� Brush ��ü�� �����Ѵ�.
		DeleteObject(mh_bk_fixed_row_col);
		mh_bk_fixed_row_col = NULL;
	}

	if (mh_bk_edit_row_col != NULL) {
		// �ڽ��� ���� Brush ��ü�� �����Ѵ�.
		DeleteObject(mh_bk_edit_row_col);
		mh_bk_edit_row_col = NULL;
	}

#ifdef TEST_CODE
	if (mh_edit_bk_brush != NULL) {
		// �ڽ��� ���� Brush ��ü�� �����Ѵ�.
		DeleteObject(mh_edit_bk_brush);
		mh_edit_bk_brush = NULL;
	}
#endif
	return CFormView::DestroyWindow();
}


HBRUSH CForm_DuDefault_1::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// ���ŵǴ� ��Ʈ���� ID�� ��´�.
	int control_id = pWnd->GetDlgCtrlID();
	
	// ���� 1�̸� ���� row�� ������ ���°���.
	// ���� 2�̸� ���� column�������� ���°���.
	// ���� 3�̸� �����͸� �����ϴ� ����Ʈ�� ������ ���°���.
	int flag = control_id / 10000; // ���� 1�̸� ���� row�� ������ ���°Ű� 
	switch (flag) {
	case 1: // fixed Row
		// ��Ʈ���� ID�� ���� ���ϴ� ID���� üũ�Ѵ�.
		if (control_id >= 10000 && control_id <= 10000 + m_fixedRowCnt) {
			// �ؽ�Ʈ�� ��� ������ �����Ѵ�.
			pDC->SetBkColor(RGB(192, 192, 192));
			// Edit ��Ʈ���� �������� ����� Brush �ڵ� ���� ��ȯ�Ѵ�.
			return mh_bk_fixed_row_col;
		}

	case 2: // fixed column
		// ��Ʈ���� ID�� ���� ���ϴ� ID���� üũ�Ѵ�.
		if (control_id >= 20000 && control_id <= 20000 + m_fixedColumnCnt*2) {
			// �ؽ�Ʈ�� ��� ������ �����Ѵ�.
			pDC->SetBkColor(RGB(192, 192, 192));
			// Edit ��Ʈ���� �������� ����� Brush �ڵ� ���� ��ȯ�Ѵ�.
			return mh_bk_fixed_row_col;
		}
		
	case 3: // normal row, column
		// ��Ʈ���� ID�� ���� ���ϴ� ID���� üũ�Ѵ�.
		if (control_id >= 30000 && control_id <= 30000 + (m_row * m_column)) {
			//// �ؽ�Ʈ�� ��� ������ �����Ѵ�.
			//pDC->SetBkColor(RGB(128, 128, 255));

			pDC->SetBkColor(RGB(128, 128, 255));

			// Edit ��Ʈ���� �������� ����� Brush �ڵ� ���� ��ȯ�Ѵ�.
			return mh_bk_edit_row_col;
		}
	}
#ifdef TEST_CODE	
	// ���ŵǴ� ��Ʈ���� ID�� ��´�.
	int control_id = pWnd->GetDlgCtrlID();
	// ��Ʈ���� ID�� ���� ���ϴ� ID���� üũ�Ѵ�.
	if (control_id >= 10000 && control_id <= 10992) {
		// Focus�� ���� �������� �ڵ� ���� ��´�.
		HWND cur_focus = ::GetFocus();
		// ���� �׸��� �׸��� ��Ʈ�Ѱ� �ڵ��� ��ġ�ϴ��� üũ�Ѵ�.
		if (cur_focus == pWnd->m_hWnd) {
			// ������ focus�� ������ �ִ� �����찡 �ִٸ� �ش� �����츦 �����ϵ���
			// InvalidateRect �Լ��� ȣ���մϴ�.
			if (mh_old_focus != cur_focus) {
				if (mh_old_focus != NULL) ::InvalidateRect(mh_old_focus, NULL, TRUE);
				// ���� ��Ʈ���� �ڵ��� ����Ų��.
				mh_old_focus = cur_focus;
			}
			// �Է� ���¿� �ִ� ��Ʈ���� �ؽ�Ʈ ������ ��� ǥ���Ѵ�.
			pDC->SetTextColor(RGB(0, 255, 255));
		}
		else {
			// �Է� ���°� �ƴ� ��Ʈ���� �ؽ�Ʈ ������ ��Ӱ� ǥ���Ѵ�.
			pDC->SetTextColor(RGB(0, 168, 168));
		}
		// �ؽ�Ʈ�� ��� ������ �����Ѵ�.
		pDC->SetBkColor(RGB(0, 0, 128));
		// Edit ��Ʈ���� �������� ����� Brush �ڵ� ���� ��ȯ�Ѵ�.
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
