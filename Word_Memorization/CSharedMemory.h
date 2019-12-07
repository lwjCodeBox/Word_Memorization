#pragma once
#include "framework.h"
class CSharedMemory
{
// Variable
private:
	HANDLE handle; //기존에 사용하는 공유 메모리가 존재한다면 핸들을 얻기 위해 변수를 하나 생성합니다.

// Function
public:
	void Init_SharedMemory(); //공유 메모리의 핸들을 얻습니다.
};

