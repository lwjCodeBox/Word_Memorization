#pragma once
#include "framework.h"
class CSharedMemory
{
// Variable
private:
	HANDLE handle; //������ ����ϴ� ���� �޸𸮰� �����Ѵٸ� �ڵ��� ��� ���� ������ �ϳ� �����մϴ�.

// Function
public:
	void Init_SharedMemory(); //���� �޸��� �ڵ��� ����ϴ�.
};

