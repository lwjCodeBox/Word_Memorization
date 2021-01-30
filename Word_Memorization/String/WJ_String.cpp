#include "pch.h"
#include "WJ_String.h"

WJ_String::WJ_String()
{
    InitialObject(NULL);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

WJ_String::WJ_String(const wchar_t *ap_string)
{
    InitialObject(ap_string);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//WJ_String::WJ_String(const char *ap_string)
//{
//    mp_string = NULL;
//    AsciiToUnicode((char *)ap_string);
//}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

WJ_String::WJ_String(const WJ_String &ar_string)
{
    InitialObject(ar_string.mp_string);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void WJ_String::InitialObject(const wchar_t *ap_string)
{
    if (ap_string == NULL) {
        m_length = 0;
        mp_string = new wchar_t[1];
        mp_string[0] = 0;
    }
    else {
        m_length = wcslen(ap_string);
        mp_string = new wchar_t[m_length + 1];
        memcpy(mp_string, ap_string, (m_length + 1) << 1); // "<< 1"�ϴ� ����� "* 2"�� ���� ǥ�� ����̴�.
    }
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

WJ_String::~WJ_String()
{
    delete[] mp_string;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void WJ_String::RemoveString()
{
    SetString(NULL);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void WJ_String::SetString(const wchar_t *ap_string)
{
    delete[] mp_string;

    InitialObject(ap_string);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void WJ_String::AttachString(wchar_t *ap_string, int a_length)
{
    delete[] mp_string;

    m_length = a_length;
    mp_string = ap_string;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void WJ_String::AddString(const wchar_t *ap_string, int a_length)
{
    int total_length = m_length + a_length;

    wchar_t *p_string = new wchar_t[total_length + 1];

    memcpy(p_string, mp_string, m_length << 1); // "<< 1"�ϴ� ����� "* 2"�� ���� ǥ�� ����̴�.
    memcpy(p_string + m_length, ap_string, (a_length + 1) << 1); // "<< 1"�ϴ� ����� "* 2"�� ���� ǥ�� ����̴�.

    delete[] mp_string;
    mp_string = p_string;
    m_length = total_length;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void WJ_String::operator=(const WJ_String &ar_string)
{
    delete[] mp_string;
    m_length = ar_string.m_length;

    mp_string = new wchar_t[m_length + 1];
    memcpy(mp_string, ar_string.mp_string, (m_length + 1) << 1); // "<< 1"�ϴ� ����� "* 2"�� ���� ǥ�� ����̴�.
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void WJ_String::operator+=(const WJ_String &ar_str)
{
    AddString(ar_str.mp_string, ar_str.m_length);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

const wchar_t *WJ_String::GetString()
{
    return mp_string;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

int WJ_String::GetLength()
{
    return m_length;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// https://m.blog.naver.com/PostView.nhn?blogId=sinarn&logNo=130180639399&proxyReferer=https:%2F%2Fwww.google.com%2F
void WJ_String::DbgLog(LPCSTR ap_str, ...)
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
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void WJ_String::DbgLogW(const wchar_t *ap_str, ...)
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

void WJ_String::DbgLogW_P(const wchar_t *ap_str, ...)
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

#include <locale.h>
void WJ_String::Format(const wchar_t *ap_str, ...)
{
    _wsetlocale(LC_ALL, L"korean");

    va_list args;
    va_start(args, ap_str);

    int len = _vscwprintf(ap_str, args) + 1;
    wchar_t *pBuf = (wchar_t *)malloc(sizeof(wchar_t) * len);

    if (pBuf) {
        delete[] mp_string;

        vswprintf(pBuf, len, ap_str, args);
        
        mp_string = pBuf;
    }

    va_end(args);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+