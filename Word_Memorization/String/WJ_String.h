#pragma once
#include <stdio.h>
#include <Windows.h>

// WJ_String Ŭ������ ���ڿ��� ���ϰ� ������ �� �ֵ��� ���� Ŭ����.
// https://blog.naver.com/tipsware/221140629230
class WJ_String
{
protected:
	wchar_t *mp_string; // �� ��ü�� �����ϴ� ���ڿ��� �ּ�
	int m_length;       // �� ��ü�� �����ϴ� ���ڿ��� ���� ("abc"�̸� 3�� ����)

public:
	WJ_String(); // �⺻ ������
	//WJ_String(const char *ap_string);
	WJ_String(const wchar_t *ap_string);
	WJ_String(const WJ_String &ar_string); // ���� ������.

	virtual ~WJ_String();

	void InitialObject(const wchar_t *ap_string); // ��ü �ʱ�ȭ �Լ�
	/*inline*/ int GetLength();				// ���ڿ��� ���̸� �˷��ִ� �Լ�
	/*inline*/ const wchar_t *GetString();	// ���ڿ��� ������ �˷��ִ� �Լ�
	void RemoveString();				// �� ��ü�� �����ϴ� ���ڿ��� �����Ѵ�.

	// ���޵� ���ڿ��� �����ؼ� �����Ѵ�.
	void SetString(const wchar_t *ap_string);
	// ���޵� ���ڿ��� �ּҸ� �״�� ����Ѵ�. (���縦 ���� �ʰ� ������ �״�� �����)
	void AttachString(wchar_t *ap_string, int a_lenght);
	// ����� ���ڿ��� �ٸ� ���ڿ��� �߰��ϴ� ��쿡 ����Ѵ�.
	// ex) "abc"�� ����Ǿ� �ִµ� AddString("def", 3); �̶�� �ϸ�
	// "abcdef"�� �ȴ�.
	void AddString(const wchar_t *ap_string, int a_length);

	// ���� ������ �����ε� str = L"test";
	void operator=(const WJ_String &ar_string);
	// ���ڿ� Ȯ��(append)�� ���� ������ �����ε�
	void operator+=(const WJ_String &ar_str);
	
	// ���ڿ��� ���ϱ� ���� ������ �����ε�
	friend WJ_String operator+(const WJ_String &ar_str1, const WJ_String &ar_str2)
	{
		WJ_String str = ar_str1;
		str.AddString(ar_str2.mp_string, ar_str2.m_length);
		return str;
	}
	// ���ڿ� �񱳸� ���� ������ �����ε� (������ Ȯ���ϱ� ���� ������)
	friend char operator==(const WJ_String &ar_str1, const WJ_String &ar_str2)
	{
		if (ar_str1.m_length != ar_str2.m_length) return 0;
		return memcmp(ar_str1.mp_string, ar_str2.mp_string, ar_str1.m_length << 1) == 0; // "<< 1"�ϴ� ����� "* 2"�� ���� ǥ�� ����̴�.
	}
	// ���ڿ� �񱳸� ���� ������ �����ε� (�ٸ��� Ȯ���ϱ� ���� ������)
	friend char operator!=(const WJ_String &ar_str1, const WJ_String &ar_str2)
	{
		if (ar_str1.m_length != ar_str2.m_length) return 0;
		return memcmp(ar_str1.mp_string, ar_str2.mp_string, ar_str1.m_length << 1) != 0; // "<< 1"�ϴ� ����� "* 2"�� ���� ǥ�� ����̴�.
	}

	wchar_t *GetStrBuffer() { return mp_string; }

// ���������� ���
public:
	// ���������� ����ϰ� �ܼ�â���� ��� (X)
	void DbgLog(LPCSTR ap_str, ...);
	// ���������� ����ϰ� �ܼ�â���� ��� (X)
	void DbgLogW(const wchar_t *ap_str, ...);
	// ���������� ����ϰ� �ܼ�â���� ��� (0)
	void DbgLogW_P(const wchar_t *ap_str, ...);
	// CString ��ü�� Format() �Լ� ó�� ���.
	void Format(const wchar_t *ap_str, ...);
};