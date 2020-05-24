#pragma once
#include "framework.h"

#define SM_DATA_MAX_COUNT	120 // 120�� myNode �Ѱ��� //100 ->  {478 = Using total port count}
#define SM_DATA_MAX_LENGTH	32  // 1432  // == MAX_DATA_COUNT_PER_PORT  (in DefStruct.h)

typedef struct TSharedMemoryData {
	BYTE data[SM_DATA_MAX_COUNT][SM_DATA_MAX_LENGTH];
} TSharedMemory;

class CSharedMemory
{
// Variable
private:
	HANDLE m_handle; //������ ����ϴ� ���� �޸𸮰� �����Ѵٸ� �ڵ��� ��� ���� ������ �ϳ� �����մϴ�.
	size_t m_nMemSize;
	void* m_Ptr;


// Function
public:
	CSharedMemory(int a_memSize);
	void Init_SharedMemory(); //���� �޸��� �ڵ��� ����ϴ�.
	bool Attach();
	const void* GetData(void) const;
};

