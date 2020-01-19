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
		AfxMessageBox(L"이미 생성된 공유 메모리가 존재합니다.");
		return;
	}

	m_handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"HM_SHARED_MEMORY_MVB_SIMULATOR");
	if (m_handle != NULL) {
		AfxMessageBox(L"기존에 사용하는 공유 메모리가 존재 합니다.");
		return;
	}

	//공유 메모리를 m_nMemSize 사이즈로 생성합니다.
	m_handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, m_nMemSize, L"HM_SHARED_MEMORY_MVB_SIMULATOR");

	//공유 메모리를 성공적으로 생성했으면 메세지 박스를 띄워 해당 내용을 출력합니다.
	if (m_handle != NULL) {
		CString str;
		str.Format(L"공유 메모리가 생성 되었습니다.\r\n 이름: %s, 크기: %d byte", L"HM_SHARED_MEMORY_MVB_SIMULATOR", m_nMemSize);
		AfxMessageBox(str);
		return;
	}
	else {
		// 메모리가 부족할 시에 공유 메모리 생성에 실패 할 수 있고,
		// 동일한 이름으로 생성된 공유 메모리의 보안이 걸려 있는 경우에도 실패할 수 있습니다.
		AfxMessageBox(L"공유 메모리를 생성하는데 실패했습니다.");
		return;
	}

/* 이사님 tips 사이트에서 퍼옴.
	//공유 메모리의 핸들을 얻습니다.
	m_handle = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"HM_SHARED_MEMORY_MVB_SIMULATOR");

	//만일 핸들이 존재한다면 메세지 박스를 띄워 해당 내용을 출력합니다.
	if (m_handle != NULL) AfxMessageBox(L"공유 메모리를 찾았습니다!");
	else AfxMessageBox(L"공유 메모리가 존재하지 않습니다.");

	//공유 메모리를 1KB 사이즈로 생성합니다.
	m_handle = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, L"HM_SHARED_MEMORY_MVB_SIMULATOR");

	//공유 메모리를 성공적으로 생성했으면 메세지 박스를 띄워 해당 내용을 출력합니다.
	if (m_handle != NULL) AfxMessageBox(L"공유 메모리를 생성했습니다!");

	//공유 메모리를 생성하는데 실패했다면 메세지 박스를 출력합니다.
	//메모리가 부족할 시에 공유 메모리 생성에 실패 할 수 있고,
	//동일한 이름으로 생성된 공유 메모리의 보안이 걸려 있는 경우에도 실패할 수 있습니다.
	else AfxMessageBox(L"공유 메모리를 생성하는데 실패했습니다");
*/
}

bool CSharedMemory::Attach()
{
	if (m_Ptr != NULL) {
		return TRUE;
	}
	// 공유 메모리에 접근하는 주소값을 획득합니다.
	// 데이터 사이즈를 지정합니다.
	m_Ptr = MapViewOfFile(m_handle, FILE_MAP_ALL_ACCESS, 0, 0, m_nMemSize);

	if (m_Ptr == NULL) {
		AfxMessageBox(L"공유 메모리 접근주소 획득 실패.");
		return FALSE;
	}
	return TRUE;
}

const void* CSharedMemory::GetData(void) const
{
	return m_Ptr;
}