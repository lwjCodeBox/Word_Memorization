#include <stdio.h>

#include "WJ_String.h"

void testF()
{
	WJ_String string = L"lee"; // ���� �����ڷ� 'lee' ���ڿ� ����

	string = L"tipssoft";   // ���� �����ڸ� ����Ͽ� ����

	WJ_String test(L"Hello");  // ��ü �����ڸ� ����Ͽ� 'Hello' ���ڿ� ����

	test = string;    // string ��ü�� ����� ���ڿ��� test ��ü�� ����
	
	//���� ���ڿ��� �ٸ� ���ڿ��� �߰��ϴ� �ڵ�� ������ �����ϴ�.
	WJ_String my_string = L"tipssoft";
	my_string += L".com";     // string ��ü���� 'tipssoft.com' ���ڿ��� �����

	WJ_String my_str2 = L"kkk";
	wprintf(L"%s\n", my_str2.GetString());

	my_str2.Format(L"�̿���");
	wprintf(L"%s\n", my_str2.GetString());
	
	return;
}
void main()
{
	testF();

	WJ_String str(L"lee");
	WJ_String str2(L"won");
	WJ_String str3(L"jong");

	
	//if(L"leewon" == (str+ str2)) 
		//printf("OK\n");
	
		
	str2 = L"123" + str2;
	wprintf(L"%s\n", str2.GetString());
	str += L"kkk";
	wprintf(L"%s\n", str.GetString());

	printf("\n2. end\n");
}