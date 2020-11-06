#pragma once

/// <Developed by developer Wonjong>
/// * 멀티 스레드 코드임.
/// * Copyright 2020.11.04 이원종. All rights reserved.
/// </Developed by developer Wonjong>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#include <vector>

struct ThreadData
{
	HWND h_wnd;
	HANDLE h_kill_event;
	HANDLE h_thread;
	DWORD thread_id;
		
	unsigned int node;
	unsigned int port;	
};

struct TDataPtr
{	
	std::vector<short> ClickedPos;
	std::vector<void *> pThreadItemDataPtr;		
};
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void *FindThreadPtr(ThreadData *ap_data);
// 버튼을 클릭한 위치의 번호가 백터 배열에 몇 번째에 위치했는지 찾고 배열에 위치한 스레드 정보를 가져옴.
void *GetThreadPtr(int a_pos);
// 벡터 배열에 있는 스레드 정보를 가져옴.
void *GetThreadPtr_2(int a_pos);
int ThreadWorking(unsigned int a_heartbit, int a_port, ThreadData *ap_data);
DWORD WINAPI SM_Thread_Run(void *ap_data);
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+