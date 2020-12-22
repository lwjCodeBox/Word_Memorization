#include "pch.h"

#include "DefineOfDev_J.h"

//size ũ���� data�迭�ȿ��� d�� ã��
//���̾����� -1��ȯ
//���� ������ data�迭�� index ��ȯ
int binarySearch(WORD *data, int size, WORD d)
{
	int s = 0; //����
	int e = size - 1; //��
	int m;

	while (s <= e) {
		m = (s + e) / 2;
		if (data[m] == d)
			return m;
		else if (data[m] > d)
			e = m - 1;
		else
			s = m + 1;
	}
	return -1;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool IsBitCheck16(WORD a_Target, WORD a_BitPos)
{
	if ((a_Target >> a_BitPos) & 0x01) return true;
	else return false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

CString GetTextFormExcel(int a_Row, int a_Col, libxl::Sheet *ap_Excel){
	// [�׸��� 2, 1] -> [���� ���� 5, 2]
	return ap_Excel->readStr(a_Row + 3, a_Col + 1, NULL);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Set_HeartBit_OnOffcolor(BYTE a_status, wchar_t *ap_wstr, RECT btnRect, CDC *ap_dc)
{
	// �۲� ��ü ����
	CFont font;

	// ���ϴ� �׸��� �׸��� ���� DC�� ��´�.
	//CClientDC dc(this);

	// ���ϴ� �Ӽ��� �����Ͽ� �۲��� �����Ѵ�.
	font.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, L"���� ���");

	// ������ �۲��� ����Ͽ� ���ڿ��� ����ϱ� ���� �ش� �۲��� DC�� �����Ѵ�.
	ap_dc->SelectObject(&font);

	int old_mode = ap_dc->SetBkMode(TRANSPARENT);
	
	if (1 == a_status) { // �ȴ��� -> ����
		ap_dc->FillSolidRect(&btnRect, RGB(0, 50, 128));
		ap_dc->Draw3dRect(&btnRect, RGB(0, 0, 0), RGB(0, 200, 255));		
		ap_dc->SetTextColor(RGB(255, 255, 255));

		ap_dc->DrawText(ap_wstr, (CRect)btnRect + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else { // ���� -> �ȴ���
		ap_dc->FillSolidRect(&btnRect, RGB(128, 129, 128));
		ap_dc->Draw3dRect(&btnRect, RGB(209, 209, 209), RGB(10, 10, 10));
		ap_dc->SetTextColor(RGB(255, 255, 255));

		ap_dc->DrawText(ap_wstr, &btnRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// �۲� ��ü�� �����Ѵ�.
	font.DeleteObject();

	// ����� ���� ���� �����Ѵ�.
	ap_dc->SetBkMode(old_mode);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Set_Protocol_OnOffcolor(BYTE a_status, wchar_t *ap_wstr, RECT btnRect, CDC *ap_dc)
{
	// �۲� ��ü ����
	CFont font;
	
	// ���ϴ� �׸��� �׸��� ���� DC�� ��´�.
	//CClientDC dc(this);

	// ���ϴ� �Ӽ��� �����Ͽ� �۲��� �����Ѵ�.
	font.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, L"���� ���");

	// ������ �۲��� ����Ͽ� ���ڿ��� ����ϱ� ���� �ش� �۲��� DC�� �����Ѵ�.
	ap_dc->SelectObject(&font);

	int old_mode = ap_dc->SetBkMode(TRANSPARENT);
	
	ap_dc->FillSolidRect(&btnRect, RGB(0, 64, 0));
	ap_dc->Draw3dRect(&btnRect, RGB(0, 255, 64), RGB(/*0, 90, 0*/0, 255, 64)); // ���� ����, �Ʒ��� ��ο�
	ap_dc->SetTextColor(RGB(255, 255, 255));

	ap_dc->DrawText(ap_wstr, &btnRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// �۲� ��ü�� �����Ѵ�.
	font.DeleteObject();

	// ����� ���� ���� �����Ѵ�.
	ap_dc->SetBkMode(old_mode);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+