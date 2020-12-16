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
//--------------------------------------------------------------------------------------------

bool IsBitCheck16(WORD a_Target, WORD a_BitPos)
{
	if ((a_Target >> a_BitPos) & 0x01) return true;
	else return false;
}
//--------------------------------------------------------------------------------------------

CString GetTextFormExcel(int a_Row, int a_Col, libxl::Sheet *ap_Excel){
	// [�׸��� 2, 1] -> [���� ���� 5, 2]
	return ap_Excel->readStr(a_Row + 3, a_Col + 1, NULL);
}
//--------------------------------------------------------------------------------------------

// https://m.blog.naver.com/PostView.nhn?blogId=sinarn&logNo=130180639399&proxyReferer=https:%2F%2Fwww.google.com%2F
void DbgLog(LPCSTR ap_str, ...)
{
    va_list args;
    
    // ����
    va_start(args, ap_str);

    // "abc"�� ������ ���ڿ��� ũ��� 3������ �� ������ ��ġ�� ���� '\0'�� �߰� �ؾ��ϱ� ������
    // ���ڿ��� ũ��� 4�� �Ǿ��Ѵ�.
    // �������ڷ� �̷���� ���ڿ��� ũ�⸦ ���Ѵ�. (_vscprintf doesn't count terminating '\0')
    int len = _vscprintf(ap_str, args) + 1; // _vscprintf for '\0'

    // ������ ���� ũ�� +1��ŭ pBuf�� �޸𸮸� �Ҵ��Ѵ�.
    char *pBuf = (char *)malloc(sizeof(char) * len);    

    if (pBuf) {
        // ���ڿ��� pBuf�� �Է��Ѵ�.
        // ���ڿ� ũ�Ⱑ 4�� �Ǿ�� ������ vsprintf() ��ȯ ���� 3�� ������ '\0' �������� ���ڿ��� �ǹ���.
        int size = vsprintf(pBuf, ap_str, args);
        OutputDebugStringA(pBuf);        
        printf("[len %d] [size %d] %s", len, size, pBuf);
        free(pBuf);
    }

    va_end(args);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void DbgLogW(LPCWSTR ap_str, ...)
{
    va_list args;
    va_start(args, ap_str);

    int len = _vscwprintf(ap_str, args) + 1;
    wchar_t *pBuf = (wchar_t *)malloc(sizeof(wchar_t) * len);
    
    if (pBuf) {
        int size = vswprintf(pBuf, len, ap_str, args);
        OutputDebugStringW(pBuf);
        wprintf(L"[len %d] [size %d] %s", len, size, pBuf);
                        
        free(pBuf);
    }

    va_end(args);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

wchar_t *DbgLogW_P(LPCWSTR ap_str, ...)
{
    va_list args;
    va_start(args, ap_str);

    int len = _vscwprintf(ap_str, args) + 1;
    wchar_t *pBuf = (wchar_t *)malloc(sizeof(wchar_t) * len);

    if (pBuf) {
        vswprintf(pBuf, len, ap_str, args);                
    }

    va_end(args);

    return pBuf;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void SetButtonON_OFF(BYTE a_status, wchar_t *ap_wstr, RECT btnRect, CClientDC *dc)
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
	dc->SelectObject(&font);

	int old_mode = dc->SetBkMode(TRANSPARENT);
	CString str;
	str.Format(L"%s", ap_wstr);

	if (1 == a_status) { // �ȴ��� -> ����
		dc->FillSolidRect(&btnRect, RGB(0, 50, 128)); // ����.
		dc->Draw3dRect(&btnRect, RGB(0, 200, 255), RGB(0, 0, 0));
		dc->SetTextColor(RGB(255, 255, 255));
		  
		dc->DrawText(str, (CRect)btnRect + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else { // ���� -> �ȴ���
		dc->FillSolidRect(&btnRect, RGB(192, 192, 192)); // �ȴ���.							
		dc->Draw3dRect(&btnRect, RGB(255, 255, 255), RGB(255, 255, 255));
		dc->SetTextColor(RGB(0, 0, 0));

		dc->DrawText(str, &btnRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// �۲� ��ü�� �����Ѵ�.
	font.DeleteObject();

	// ����� ���� ���� �����Ѵ�.
	dc->SetBkMode(old_mode);

}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+