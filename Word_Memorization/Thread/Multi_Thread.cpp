#include "pch.h"

/// <Developed by developer Wonjong>
/// * 멀티 스레드 코드임.
/// * Copyright 2020.10.28 이원종. All rights reserved.
/// </Developed by developer Wonjong>

#include "Multi_Thread.h"

DWORD WINAPI SM_Thread_Run(void *ap_data)
{
	ThreadData *p_data = (ThreadData *)ap_data;
	
	int index;
		
	TRACE("[%08x] Thread Start!\n", p_data->thread_id);

	__int64 sum = 0;
	int start_tick = GetTickCount(), kill_flag = 0;
	unsigned int i;
	
	if (WaitForSingleObject(p_data->h_kill_event, 0) == WAIT_OBJECT_0)	kill_flag = 1;
		
	//if (IsPrime(i)) sum += i;		
	
	TRACE("[%08x] Thread Stop!", p_data->thread_id);

	CloseHandle(p_data->h_thread);

/*
	EnterCriticalSection(&gh_sum_lock);
	*p_data->p_sum += sum;
	LeaveCriticalSection(&gh_sum_lock);
*/

	if (WaitForSingleObject(p_data->h_kill_event, 0) == WAIT_OBJECT_0)	kill_flag = 1;

	::PostMessage(p_data->h_wnd, 27001, kill_flag, (LPARAM)p_data);

	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+