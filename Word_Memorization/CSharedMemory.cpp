#include "pch.h"
#include "CSharedMemory.h"

void CSharedMemory::Init_SharedMemory()
{
	//���� �޸��� �ڵ��� ����ϴ�.
	handle = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"TestSharedMemory");

	//���� �ڵ��� �����Ѵٸ� �޼��� �ڽ��� ��� �ش� ������ ����մϴ�.
	if (handle != NULL) AfxMessageBox(L"���� �޸𸮸� ã�ҽ��ϴ�!");
	else AfxMessageBox(L"���� �޸𸮰� �������� �ʽ��ϴ�.");

	//���� �޸𸮸� 1KB ������� �����մϴ�.
	handle = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, L"TestSharedMemory");

	//���� �޸𸮸� ���������� ���������� �޼��� �ڽ��� ��� �ش� ������ ����մϴ�.
	if (handle != NULL) AfxMessageBox(L"���� �޸𸮸� �����߽��ϴ�!");

	//���� �޸𸮸� �����ϴµ� �����ߴٸ� �޼��� �ڽ��� ����մϴ�.
	//�޸𸮰� ������ �ÿ� ���� �޸� ������ ���� �� �� �ְ�,
	//������ �̸����� ������ ���� �޸��� ������ �ɷ� �ִ� ��쿡�� ������ �� �ֽ��ϴ�.
	else AfxMessageBox(L"���� �޸𸮸� �����ϴµ� �����߽��ϴ�");
}
