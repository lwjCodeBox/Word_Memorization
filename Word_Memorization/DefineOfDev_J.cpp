#include "pch.h"

#include "DefineOfDev_J.h"

//size 크기의 data배열안에서 d를 찾기
//값이없으면 -1반환
//값이 있으면 data배열의 index 반환
int binarySearch(WORD *data, int size, WORD d)
{
	int s = 0; //시작
	int e = size - 1; //끝
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
	// [그리드 2, 1] -> [엑셀 포멧 5, 2]
	return ap_Excel->readStr(a_Row + 3, a_Col + 1, NULL);
}
//--------------------------------------------------------------------------------------------

// https://m.blog.naver.com/PostView.nhn?blogId=sinarn&logNo=130180639399&proxyReferer=https:%2F%2Fwww.google.com%2F
void DbgLog(LPCSTR ap_str, ...)
{
    va_list args;
    
    // 시작
    va_start(args, ap_str);

    // "abc"가 들어오면 문자열은 크기는 3이지만 맨 마지막 위치한 곳에 '\0'을 추가 해야하기 때문에
    // 문자열의 크기는 4가 되야한다.
    // 가변인자로 이루어진 문자열의 크기를 구한다. (_vscprintf doesn't count terminating '\0')
    int len = _vscprintf(ap_str, args) + 1; // _vscprintf for '\0'

    // 위에서 구한 크기 +1만큼 pBuf에 메모리를 할당한다.
    char *pBuf = (char *)malloc(sizeof(char) * len);    

    if (pBuf) {
        // 문자열을 pBuf에 입력한다.
        // 문자열 크기가 4가 되어야 하지만 vsprintf() 반환 값이 3인 이유는 '\0' 전까지의 문자열을 의미함.
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
	// 글꼴 객체 선언
	CFont font;

	// 원하는 그림을 그리기 위해 DC를 얻는다.
	//CClientDC dc(this);

	// 원하는 속성을 지정하여 글꼴을 생성한다.
	font.CreateFont(18, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, L"맑은 고딕");

	// 생성된 글꼴을 사용하여 문자열을 출력하기 위해 해당 글꼴을 DC에 연결한다.
	dc->SelectObject(&font);

	int old_mode = dc->SetBkMode(TRANSPARENT);
	CString str;
	str.Format(L"%s", ap_wstr);

	if (1 == a_status) { // 안눌림 -> 눌림
		dc->FillSolidRect(&btnRect, RGB(0, 50, 128)); // 눌림.
		dc->Draw3dRect(&btnRect, RGB(0, 200, 255), RGB(0, 0, 0));
		dc->SetTextColor(RGB(255, 255, 255));
		  
		dc->DrawText(str, (CRect)btnRect + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else { // 눌림 -> 안눌림
		dc->FillSolidRect(&btnRect, RGB(192, 192, 192)); // 안눌림.							
		dc->Draw3dRect(&btnRect, RGB(255, 255, 255), RGB(255, 255, 255));
		dc->SetTextColor(RGB(0, 0, 0));

		dc->DrawText(str, &btnRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// 글꼴 객체를 제거한다.
	font.DeleteObject();

	// 배경을 이전 모드로 설정한다.
	dc->SetBkMode(old_mode);

}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+