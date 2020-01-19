#include "pch.h"
#include "CSharedMemory.h"

CSharedMemory::CSharedMemory(int a_memSize)
	: m_nMemSize(a_memSize), m_handle(NULL)
{
}


void CSharedMemory::Init_SharedMemory()
{
	// SM_NAME_MVB_SIMULATOR
	if (m_handle != NULL) {
		AfxMessageBox(L"�̹� ������ ���� �޸𸮰� �����մϴ�.");
		return;
	}

	m_handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"HM_SHARED_MEMORY_MVB_SIMULATOR");
	if (m_handle != NULL) {
		AfxMessageBox(L"������ ����ϴ� ���� �޸𸮰� ���� �մϴ�.");
		return;
	}

	//���� �޸𸮸� m_nMemSize ������� �����մϴ�.
	m_handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, m_nMemSize, L"HM_SHARED_MEMORY_MVB_SIMULATOR");

	//���� �޸𸮸� ���������� ���������� �޼��� �ڽ��� ��� �ش� ������ ����մϴ�.
	if (m_handle != NULL) {
		CString str;
		str.Format(L"���� �޸𸮰� ���� �Ǿ����ϴ�.\r\n �̸�: %s, ũ��: %d byte", L"HM_SHARED_MEMORY_MVB_SIMULATOR", m_nMemSize);
		AfxMessageBox(str);
		return;
	}
	else {
		// �޸𸮰� ������ �ÿ� ���� �޸� ������ ���� �� �� �ְ�,
		// ������ �̸����� ������ ���� �޸��� ������ �ɷ� �ִ� ��쿡�� ������ �� �ֽ��ϴ�.
		AfxMessageBox(L"���� �޸𸮸� �����ϴµ� �����߽��ϴ�.");
		return;
	}

/* �̻�� tips ����Ʈ���� �ۿ�.
	//���� �޸��� �ڵ��� ����ϴ�.
	m_handle = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"HM_SHARED_MEMORY_MVB_SIMULATOR");

	//���� �ڵ��� �����Ѵٸ� �޼��� �ڽ��� ��� �ش� ������ ����մϴ�.
	if (m_handle != NULL) AfxMessageBox(L"���� �޸𸮸� ã�ҽ��ϴ�!");
	else AfxMessageBox(L"���� �޸𸮰� �������� �ʽ��ϴ�.");

	//���� �޸𸮸� 1KB ������� �����մϴ�.
	m_handle = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, L"HM_SHARED_MEMORY_MVB_SIMULATOR");

	//���� �޸𸮸� ���������� ���������� �޼��� �ڽ��� ��� �ش� ������ ����մϴ�.
	if (m_handle != NULL) AfxMessageBox(L"���� �޸𸮸� �����߽��ϴ�!");

	//���� �޸𸮸� �����ϴµ� �����ߴٸ� �޼��� �ڽ��� ����մϴ�.
	//�޸𸮰� ������ �ÿ� ���� �޸� ������ ���� �� �� �ְ�,
	//������ �̸����� ������ ���� �޸��� ������ �ɷ� �ִ� ��쿡�� ������ �� �ֽ��ϴ�.
	else AfxMessageBox(L"���� �޸𸮸� �����ϴµ� �����߽��ϴ�");
*/
}

bool CSharedMemory::Attach()
{
	if (m_Ptr != NULL) {
		return TRUE;
	}
	// ���� �޸𸮿� �����ϴ� �ּҰ��� ȹ���մϴ�.
	// ������ ����� �����մϴ�.
	m_Ptr = MapViewOfFile(m_handle, FILE_MAP_ALL_ACCESS, 0, 0, m_nMemSize);

	if (m_Ptr == NULL) {
		AfxMessageBox(L"���� �޸� �����ּ� ȹ�� ����.");
		return FALSE;
	}
	return TRUE;
}

const void* CSharedMemory::GetData(void) const
{
	return m_Ptr;
}