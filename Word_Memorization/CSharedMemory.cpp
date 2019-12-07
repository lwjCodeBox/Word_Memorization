#include "pch.h"
#include "CSharedMemory.h"

void CSharedMemory::Init_SharedMemory()
{
	//공유 메모리의 핸들을 얻습니다.
	handle = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"TestSharedMemory");

	//만일 핸들이 존재한다면 메세지 박스를 띄워 해당 내용을 출력합니다.
	if (handle != NULL) AfxMessageBox(L"공유 메모리를 찾았습니다!");
	else AfxMessageBox(L"공유 메모리가 존재하지 않습니다.");

	//공유 메모리를 1KB 사이즈로 생성합니다.
	handle = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, L"TestSharedMemory");

	//공유 메모리를 성공적으로 생성했으면 메세지 박스를 띄워 해당 내용을 출력합니다.
	if (handle != NULL) AfxMessageBox(L"공유 메모리를 생성했습니다!");

	//공유 메모리를 생성하는데 실패했다면 메세지 박스를 출력합니다.
	//메모리가 부족할 시에 공유 메모리 생성에 실패 할 수 있고,
	//동일한 이름으로 생성된 공유 메모리의 보안이 걸려 있는 경우에도 실패할 수 있습니다.
	else AfxMessageBox(L"공유 메모리를 생성하는데 실패했습니다");
}
