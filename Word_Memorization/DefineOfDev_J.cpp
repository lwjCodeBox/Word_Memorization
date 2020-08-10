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
