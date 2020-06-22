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

	// ��� ��Ʈ���� ���� ���ѹ��� (���� ������ �������� ����)
	mp_Grid->GetHeaderCtrl()->EnableWindow(false);


	mp_Grid->SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);



	mp_Grid->DeleteAllItems();

	// ����Ʈ ��Ÿ�� ����
	//LVS_EX_FULLROWSELECT  : �������� ������ �� �� �� ��ü�� ������Ų��.
	//LVS_EX_GRIDLINES      : �� �����ۿ� ��輱�� �׷��ش�.
	//LVS_EX_CHECKBOXES     : �� �����ۿ� Check Box�� ǥ���� �ش�.
	//LVS_EX_HEADERDRAGDROP : �÷� ����� �巡�� �����ν� �÷��� ������ �ٲ� �� �ְ� ���ش�.
	mp_Grid->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	// Ÿ��Ʋ ���� 
	mp_Grid->InsertColumn(0, _T("ù ��° Ÿ��Ʋ"), LVCFMT_LEFT, 200, -1); // ���� ����
	mp_Grid->InsertColumn(1, _T("�� ��° Ÿ��Ʋ"), LVCFMT_RIGHT, 109, -1); // ������ ����
	mp_Grid->InsertColumn(2, _T("�� ��° Ÿ��Ʋ"), LVCFMT_CENTER, 109, -1); // ��� ����




	// Row 0 
	mp_Grid->InsertItem(0, _T("1."));
	mp_Grid->InsertItem(1, _T("2."));
	mp_Grid->InsertItem(2, _T("3."));
	mp_Grid->InsertItem(3, _T("4."));
	mp_Grid->InsertItem(4, _T("5."));

	// ù��° ���ڴ� ��, �ι�° ���ڴ� ���� �Ǹ��Ѵ�. 
	mp_Grid->SetItem(0, 1, LVIF_TEXT, _T("0�� 1��"), 0, 0, 0, NULL);
	mp_Grid->SetItem(1, 1, LVIF_TEXT, _T("1�� 1��"), 0, 0, 0, NULL);
	mp_Grid->SetItem(2, 1, LVIF_TEXT, _T("2�� 1��"), 0, 0, 0, NULL);
	mp_Grid->SetItem(3, 1, LVIF_TEXT, _T("3�� 1��"), 0, 0, 0, NULL);
	mp_Grid->SetItem(4, 1, LVIF_TEXT, _T("4�� 1��"), 0, 0, 0, NULL);

	m_hOldFont = NULL;
	m_hFont.CreateFont(16, 0, 0, 0, FW_HEAVY, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, L"console");


	/* ����Ʈ ��Ʈ�� �׽�Ʈ �غ��� ���� ����
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
	*/

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
	//Clear_EditCtrl();

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
		if (control_id >= 20000 && control_id <= 20000 + m_fixedColumnCnt * 2) {
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
		*pResult = CDRF_NOTIFYITEMDRAW;          // �����ۿܿ� �Ϲ������� ó���ϴ� �κ�
		lplvcd->clrTextBk = RGB(0, 0, 255);
		break;



	case CDDS_ITEMPREPAINT:                          // �� �����ۿ� ���� ó���� �� ���
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		break;



	case CDDS_ITEMPREPAINT | CDDS_SUBITEM:  // ��� �� �����ۿ� ���� ó���� �� ���
		nRow = (int)lplvcd->nmcd.dwItemSpec;         // �� �ε����� ������
		nSub = (int)lplvcd->iSubItem;                       // �� �ε����� ������



// �ش� �κп� if ���ǹ��� ���� ���ϴ� ���� ���� ������ ���� �Ҽ� �ִ�.

// ������� �ش� ��� ���� ����Ʈ�� ���� ���ϰų�, �ش� ��� �� �ε����� ���Ѵ�.
		//if()
		//{

		//	lplvcd->clrTextBk = RGB(255, 255, 255);           // �ش� ��, �� �������� ������ �����Ѵ�.

		//	lplvcd->clrText = RGB(0, 0, 0);                      // �ش� ��, �� �������� ���ڻ��� �����Ѵ�.

		//}

		//// �ش� �κп� if ���ǹ��� ���� ���ϴ� ���� ���� ��Ʈ�� ���� �Ҽ� �ִ�.
		//if()
		//{

		//	CDC *pDC = CDC::FromHandle(lplvcd->nmcd.hdc);
		//	hOldFont = (CFont *)pDC->SelectObject(&hFont);

		//}

		//   else

		//   {

		//   // hOldFont�� �ǵ�����.

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

			// ��� Ȥ�� �ؽ�Ʈ�� �����Ѵ�.
		case CDDS_ITEMPREPAINT:
			// 1��° �� ������, 2��° �� ���, 3��° ���ϴ� �Ķ����� ���ڻ��� ���´�.
			if (lplvcd->nmcd.dwItemSpec == 0) text_color = RGB(255, 0, 0);
			else if (lplvcd->nmcd.dwItemSpec == 1) text_color = RGB(0, 255, 0);
			else text_color = RGB(0, 0, 255);
			lplvcd->clrText = text_color;
			*pResult = CDRF_NOTIFYITEMDRAW;
			return;

			// ���� �������� ��� Ȥ�� �ؽ�Ʈ�� �����Ѵ�.
		case CDDS_SUBITEM | CDDS_PREPAINT | CDDS_ITEM:
			if (lplvcd->iSubItem != 0) {
				// 1��° ���̶��...
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


	/* �� �پ� �ٸ� ������ ĥ�ϱ�
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
