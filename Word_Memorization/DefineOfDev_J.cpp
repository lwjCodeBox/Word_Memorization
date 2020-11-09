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
// [설정] -> [고급] -> [문자집합] 항목이 아스키 코드로 설정인 경우...
void DbgLog(LPCTSTR a_str, ...)
{
    //va_list args;
    //va_start(args, a_str);

    //// "abc"가 들어오면 문자열은 크기는 3이지만 맨 마지막 위치한 곳에 \n을 추가 해야하기 때문에
    //// 문자열의 크기는 4가 되야한다.
    //int len = _vsctprintf(a_str, args) + 1; // _vstprintf_s for '\0'
    //char *pBuf = (char *)malloc(sizeof(char) * len);

    //if (pBuf) {
    //    // 문자열 크기가 4가 되어야 하지만 _vstprintf_s 반환 값이 3인 이유는 개행문자(\n) 전까지의 문자열을 의미함.
    //    int size = _vstprintf_s(pBuf, len, a_str, args);
    //    OutputDebugString(pBuf);
    //    printf("[len %d] [size %d] %s", len, size, pBuf);
    //    free(pBuf);
    //}

    //va_end(args);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

// [설정] -> [고급] -> [문자집합] 항목이 유니코드로 설정인 경우...
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