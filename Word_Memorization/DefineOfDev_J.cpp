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
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool IsBitCheck16(WORD a_Target, WORD a_BitPos)
{
	if ((a_Target >> a_BitPos) & 0x01) return true;
	else return false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

CString GetTextFormExcel(int a_Row, int a_Col, libxl::Sheet *ap_Excel){
	// [그리드 2, 1] -> [엑셀 포멧 5, 2]
	return ap_Excel->readStr(a_Row + 3, a_Col + 1, NULL);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Set_HeartBit_OnOffcolor(BYTE a_status, wchar_t *ap_wstr, RECT btnRect, CDC *ap_dc)
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
	ap_dc->SelectObject(&font);

	int old_mode = ap_dc->SetBkMode(TRANSPARENT);
	
	if (1 == a_status) { // 안눌림 -> 눌림
		ap_dc->FillSolidRect(&btnRect, RGB(0, 50, 128));
		ap_dc->Draw3dRect(&btnRect, RGB(0, 0, 0), RGB(0, 200, 255));		
		ap_dc->SetTextColor(RGB(255, 255, 255));

		ap_dc->DrawText(ap_wstr, (CRect)btnRect + CPoint(2, 2), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else { // 눌림 -> 안눌림
		ap_dc->FillSolidRect(&btnRect, RGB(128, 129, 128));
		ap_dc->Draw3dRect(&btnRect, RGB(209, 209, 209), RGB(10, 10, 10));
		ap_dc->SetTextColor(RGB(255, 255, 255));

		ap_dc->DrawText(ap_wstr, &btnRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	// 글꼴 객체를 제거한다.
	font.DeleteObject();

	// 배경을 이전 모드로 설정한다.
	ap_dc->SetBkMode(old_mode);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void Set_Protocol_OnOffcolor(BYTE a_status, wchar_t *ap_wstr, RECT btnRect, CDC *ap_dc)
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
	ap_dc->SelectObject(&font);

	int old_mode = ap_dc->SetBkMode(TRANSPARENT);
	
	ap_dc->FillSolidRect(&btnRect, RGB(0, 64, 0));
	ap_dc->Draw3dRect(&btnRect, RGB(0, 255, 64), RGB(/*0, 90, 0*/0, 255, 64)); // 위가 밝음, 아래가 어두움
	ap_dc->SetTextColor(RGB(255, 255, 255));

	ap_dc->DrawText(ap_wstr, &btnRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// 글꼴 객체를 제거한다.
	font.DeleteObject();

	// 배경을 이전 모드로 설정한다.
	ap_dc->SetBkMode(old_mode);
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+