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
