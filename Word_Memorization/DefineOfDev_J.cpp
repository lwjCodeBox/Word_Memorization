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
// [����] -> [���] -> [��������] �׸��� �ƽ�Ű �ڵ�� ������ ���...
void DbgLog(LPCTSTR a_str, ...)
{
    //va_list args;
    //va_start(args, a_str);

    //// "abc"�� ������ ���ڿ��� ũ��� 3������ �� ������ ��ġ�� ���� \n�� �߰� �ؾ��ϱ� ������
    //// ���ڿ��� ũ��� 4�� �Ǿ��Ѵ�.
    //int len = _vsctprintf(a_str, args) + 1; // _vstprintf_s for '\0'
    //char *pBuf = (char *)malloc(sizeof(char) * len);

    //if (pBuf) {
    //    // ���ڿ� ũ�Ⱑ 4�� �Ǿ�� ������ _vstprintf_s ��ȯ ���� 3�� ������ ���๮��(\n) �������� ���ڿ��� �ǹ���.
    //    int size = _vstprintf_s(pBuf, len, a_str, args);
    //    OutputDebugString(pBuf);
    //    printf("[len %d] [size %d] %s", len, size, pBuf);
    //    free(pBuf);
    //}

    //va_end(args);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// [����] -> [���] -> [��������] �׸��� �����ڵ�� ������ ���...
void DbgLogW(LPCTSTR str, ...)
{
    wchar_t *pCopy = '\0';
    va_list args;
    va_start(args, str);

    int len = _vsctprintf(str, args) + 1;
    wchar_t *pBuf = (wchar_t *)malloc(sizeof(wchar_t) * len);
    
    if (pBuf) {
        int size = vswprintf(pBuf, len, str, args);
        OutputDebugStringW(pBuf);
        wprintf(L"[len %d] [size %d] %s", len, size, pBuf);
                        
        free(pBuf);
    }

    va_end(args);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+