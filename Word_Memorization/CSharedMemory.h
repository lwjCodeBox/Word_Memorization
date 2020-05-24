#pragma once
#include "framework.h"

#define SM_DATA_MAX_COUNT	120 // 120은 myNode 총개수 //100 ->  {478 = Using total port count}
#define SM_DATA_MAX_LENGTH	32  // 1432  // == MAX_DATA_COUNT_PER_PORT  (in DefStruct.h)

typedef struct TSharedMemoryData {
	BYTE data[SM_DATA_MAX_COUNT][SM_DATA_MAX_LENGTH];
} TSharedMemory;

class CSharedMemory
{
// Variable
private:
	HANDLE m_handle; //기존에 사용하는 공유 메모리가 존재한다면 핸들을 얻기 위해 변수를 하나 생성합니다.
	size_t m_nMemSize;
	void* m_Ptr;


// Function
public:
	CSharedMemory(int a_memSize);
	void Init_SharedMemory(); //공유 메모리의 핸들을 얻습니다.
	bool Attach();
	const void* GetData(void) const;
};

