// CTab3.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CTab3.h"
#include "afxdialogex.h"

#include "Word_MemorizationDlg.h"

// CTab3 dialog

IMPLEMENT_DYNAMIC(CTab3, CDialogEx)

CTab3::CTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{
	mp_MainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	//arr[rows][columns]��� int�� 2���� �迭�� �ִٰ� �����ϸ�
	//for (int i = 0; i < rows; i++) {
	//	memset(arr[i], �ʱ�ȭ�ϰ��� �ϴ� ��, sizeof(int) * colums);
	//}
	int row = 15, column = 8;
	for (int i = 0; i < row; i++) {
		memset(m_CellClickStatus[i], 0, column * sizeof(unsigned char));
	}
}

CTab3::~CTab3()
{
}

void CTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab3, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CTab3 message handlers


void CTab3::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	
	CPen pen;
	pen.CreatePen(PS_DOT, 3, RGB(128, 128, 128)); 
	CPen *p_OldPen = dc.SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(150, 200, 200));     
	CBrush *p_OldBrush = dc.SelectObject(&brush);
	
	// Test code
	//for (int i = 0; i < 8; i++) {
	//	dc.Rectangle(20 + i * 30 + (i * 30), 130, 20 + (i + 1) * 30 + (i * 30), 190); // �� 30�� 30��ŭ ������ �����
	//}

	// Original code
	//for (int i = 0; i < 9; i++) {
	//	dc.Rectangle(20 + i * 150, 60, 20 + (i + 1) * 150, 120); // x��ǥ ������, y��ǥ ������, x��ǥ ������, y��ǥ ������
	//}
	
/* Sample Code of Builder XE5
	// Load Protocol Signal Name from Config.xlsx
	int grid_row = 0;
	int t_gap_col = 0; // for merge cell
	int t_gap_row = 0; // Skip... Later...

	for (int i = row_first; i < row_last; i++) {
		for (int j = col_first; j < col_last; j++) {
			tempStr = (wchar_t *)sheet->readStr(i, j, &format);
			p_grid->Cells[j][grid_row + 1] = tempStr;

			bMerge = sheet->getMerge(i, j, &merge_row_first, &merge_row_last, &merge_col_first, &merge_col_last);
			if (bMerge) { // do not handle cells merged more than 1 BYTE.
				t_gap_col = merge_col_last - merge_col_first + 1; // +1 is essential
				p_grid->MergeCells(j, grid_row, t_gap_col, 1);
				p_grid->MergeCells(j, grid_row + 1, t_gap_col, 1);
				j += (t_gap_col - 1);
			}
		}
		grid_row += 2;
	}
*/
	
	// fixed row, col
	int startWidth, endWidht;
	int startHeight, endHeight;
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 17; j++) {
			startWidth = 20 + i * 250; // x��ǥ ������
			endWidht = startWidth + 250;
			startHeight = 60 + j * 60;
			endHeight = startHeight + 60;

			dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 1; j++) {
			startWidth = 20 + i * 250; // x��ǥ ������
			endWidht = startWidth + 250;
			startHeight = 60 + j * 60;
			endHeight = startHeight + 60;

			dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
		}
	}
	dc.SelectObject(p_OldBrush);
	brush.DeleteObject();

	

	int row_first = 0; // user define (�� ���� ��ġ)
	int row_last = 0;
	int col_first = 0; // user define (�� ���� ��ġ)
	int col_last = 0; // user define

	int mergeCount = 0;
	bool bMerge = false;

	// not fixed row, col
	brush.CreateSolidBrush(RGB(200, 200, 200));
	p_OldBrush = dc.SelectObject(&brush);

	// ��ü �ʱ�ȭ
	for (int j = 1; j < 17; j++) {
		for (int i = 1; i < 9; i++) {
			//if (i == 9) break; // i�� 9���� ���� ��Ʈ ǥ���� ��ĭ �� �ϴµ� �������� �о���� ��ġ�� 9������ �Ʒ� �ڵ忡�� +1�� ����.

			// ������ �Ǿ� �ִ��� üũ
			//bMerge = mp_MainDlg->mp_Libxl->m_pSheet1->getMerge(j+1, i+1, &row_first, &row_last, &col_first, &col_last);
			//if (bMerge) {
			//	mergeCount++;
			//}
			//else {
			//	mergeCount = 0;
			//}

			startWidth = 20 + i * 250; // x��ǥ ������
			endWidht = startWidth + 250;
			startHeight = 60 + j * 60;
			endHeight = startHeight + 60;

			dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
		}
	}

	// ���յ� �κи� �ٽ� �׸�
	int firstMergeCellPos = 0;

	for (int j = 1; j < 18; j++) {
		for (int i = 1; i < 10; i++) {
			if (j == 17) break;
			if (i == 9) break; 
			bMerge = mp_MainDlg->mp_Libxl->m_pSheet1->getMerge(j + 1, i + 1, &row_first, &row_last, &col_first, &col_last);

			if (bMerge) {
				if (firstMergeCellPos == 0)
					startWidth = 20 + i * 250; 

				firstMergeCellPos++;
				mergeCount++;
				continue;
			}
			else {
				if (0 == mergeCount) {
					startWidth = 20 + i * 250;
				}
				else {
					endWidht = startWidth + (250 * mergeCount);
					
					firstMergeCellPos = 0;
					mergeCount = 0;

					startHeight = 60 + j * 60;
					endHeight = startHeight + 60;
					dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
				}
			}
		}
	}

	// �Ͻ������� ���� �����߱� ������ ������ �������� �ǵ����� ���� �ٸ� �ý���
	// �Ǵ� ���α׷��� ���� �ٶ����ϴ�.
	dc.SelectObject(p_OldBrush);
	dc.SelectObject(p_OldPen);

	// ��, �귯�� ��ü ����
	pen.DeleteObject();
	brush.DeleteObject();

	PrintInitializeCell(&dc);
	FixedCellText(&dc);
}


void CTab3::OnLButtonDown(UINT nFlags, CPoint point)
{
	//CPaintDC dc(this); // device context for painting
	CClientDC dc(this);

	CPen pen;
	pen.CreatePen(PS_DOT, 3, RGB(128, 128, 128));   
	CPen *p_OldPen = dc.SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(200, 200, 200));    
	CBrush *p_OldBrush = dc.SelectObject(&brush);

	//CPaintDC dc2(this); // device context for painting
	CClientDC dc2(this);

	CPen pen2;
	pen2.CreatePen(PS_DOT, 3, RGB(128, 128, 128));
	CPen *p_OldPen2 = dc2.SelectObject(&pen2);

	CBrush brush2;
	brush2.CreateSolidBrush(RGB(0, 200, 0));     // ���� ä����� ����
	CBrush *p_OldBrush2 = dc2.SelectObject(&brush2);

	// 250�� �ǹ̰� �簢���� ���� ���ϸ� �簢�� �� ���� ��ŭ ����.
	// 60�� �ǹ̰� �簢���� ���̸� ���ϸ� �簢�� ���� ��ŭ ����.
	unsigned int rx = (unsigned int)(point.x - 20) / 250, ry = (unsigned int)(point.y - 60) / 60; 
	int startWidth, endWidht;
	int startHeight, endHeight;

	if ((rx > 0 && rx < 9) && (ry > 0 && ry < 17)) { // 0��° ��ġ ��, �� �տ� �ִ� ��������� Ŭ���� �ص� �� ������ ����.
		// ��δ� �׸���.
		//for (int i = 0; i < 9; i++) {
		//	for (int j = 0; j < 17; j++) {
		//		startWidth = 20 + i * 250; // x��ǥ ������
		//		endWidht = startWidth + 250;
		//		startHeight = 60 + j * 60;
		//		endHeight = startHeight + 60;
		//
		//		dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
		//	}
		//}
		startWidth = 20 + rx * 250; // x��ǥ ������
		endWidht = startWidth + 250;
		startHeight = 60 + ry * 60;
		endHeight = startHeight + 60;
		
		// Ŭ���� �߾����� ���߾����� �Ǵ�.
		if (1 == m_CellClickStatus[ry - 1][8 - rx]) {
			m_CellClickStatus[ry - 1][8 - rx] = 0;
			dc.Rectangle(startWidth, startHeight, endWidht, endHeight);
		}
		else {
			m_CellClickStatus[ry - 1][8 - rx] = 1;
			dc2.Rectangle(startWidth, startHeight, endWidht, endHeight);
		}


		// ���� 8-rx�� �ؾ��ϴ� ������ �� ��ĭ�� ���� ��ȣ�� ����ϴ� ���̱� ������
		// ������ 0,0�� �Ǵ� ��ġ�� �� ��° ĭ�����̴�. 
		PrintSelectedCell(ry-1, 8-rx); // ��(a_Row),��(a_Col) 
	}
	
	dc.SelectObject(p_OldBrush);
	dc.SelectObject(p_OldPen);
	pen.DeleteObject();
	brush.DeleteObject();

	dc2.SelectObject(p_OldBrush2);
	dc2.SelectObject(p_OldPen2);
	pen2.DeleteObject();
	brush2.DeleteObject();
	
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CTab3::PrintSelectedCell(int a_Col, int a_Row)
{
	CClientDC dc(this);

	//////////////// �������� �ؽ�Ʈ ��� /////////////
	CString str;
	str.Format(L"%s", mp_MainDlg->mp_Libxl->getExcelValue(a_Col, a_Row));
	unsigned char strLen = str.GetLength();

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0, 0, 0));
	//dc.TextOutW( 80 + (a_Row * 60), 20 + (37 - strLen) + (a_Col * 150), str);
	int row = 250 + ((7 - a_Row) * 250 + (strLen + 70));
	int col = 60 + ((a_Col + 1) * 60) + 20;
	dc.TextOutW(row, col, str); // ��, �� 
}

void CTab3::PrintInitializeCell(CPaintDC *a_DC)
{
	CString str;
	
	for (int col = 0; col < 15 + 1; col++) { // ��(col)
		for (int row = 0; row < 7 + 1; row++) { // ��(row)
			str.Format(L"%s", mp_MainDlg->mp_Libxl->getExcelValue(col, row)); // ��(col), ��(row) 
			unsigned char strLen = str.GetLength();

			a_DC->SetBkMode(TRANSPARENT);
			a_DC->SetTextColor(RGB(0, 0, 0));
			
			int t_row = 250 + ((7 - row) * 250 + (strLen + 70));
			int t_col = 60 + ((col + 1) * 60) + 20;
			a_DC->TextOutW(t_row, t_col, str); // ��, ��
		}
	}
}

void CTab3::FixedCellText(CPaintDC *a_DC)
{
	CString str;

	// ��(row)
	for (int row = 0; row < 7 + 1; row++) { 
		unsigned char strLen = str.GetLength();

		a_DC->SetBkMode(TRANSPARENT);
		a_DC->SetTextColor(RGB(140, 0, 255));
			
		int t_row = 250 + ((7 - row) * 250 + (strLen + 70));
		int t_col = 80; //60 + ((col + 1) * 60) + 20;

		str.Format(L"Bit %d", row);
		a_DC->TextOutW(t_row, t_col, str); // ��, �� 
	}
	// ��(col)
	for (int col = 0; col < 15 + 1; col++) { 
		unsigned char strLen = str.GetLength();

		a_DC->SetBkMode(TRANSPARENT);
		a_DC->SetTextColor(RGB(140, 0, 255));

		int t_row = strLen + 70 ; //250 + ((7 - row) * 250 + (strLen + 70));
		int t_col = 60 + ((col + 1) * 60) + 20;

		str.Format(L"Word %d", col);
		a_DC->TextOutW(t_row, t_col, str); // ��, �� 
	}
}