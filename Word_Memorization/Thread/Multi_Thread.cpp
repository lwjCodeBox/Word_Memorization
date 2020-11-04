#include "pch.h"

/// <Developed by developer Wonjong>
/// * 멀티 스레드 코드임.
/// * Copyright 2020.11.04 이원종. All rights reserved.
/// </Developed by developer Wonjong>

#include "Multi_Thread.h"
#include "../Word_MemorizationDlg.h"

TDataPtr threadItemPtr;

void *GetThreadPtr(int a_pos)
{
	ThreadData *data = (ThreadData*)threadItemPtr.p_ptr[a_pos];
	return data;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

void DeleteThreadPtr(int a_pos) 
{
	threadItemPtr.p_ptr[a_pos] = NULL;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

int ThreadWorking(unsigned int a_heartbit, int a_port, ThreadData *ap_data)
{	
	CWordMemorizationDlg *parentdlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();
	memset(&(parentdlg->m_pData->data[a_port][1]), a_heartbit, 1);
	Sleep(300);

	return 1;	
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

DWORD WINAPI SM_Thread_Run(void *ap_data)
{
	ThreadData *p_data = (ThreadData *)ap_data;
	int kill_flag = 0;
	unsigned int heartbit = 0;
	
	TRACE("[%08x] Thread Start!\n", p_data->thread_id);
	threadItemPtr.p_ptr[p_data->thread_count] = p_data;

	while(true){
		if (WaitForSingleObject(p_data->h_kill_event, 10) == WAIT_OBJECT_0) {
			TRACE("[%08x] Thread Stop!\n", p_data->thread_id);
			kill_flag = 1; // 1의 의미는 사용자가 스레드를 강제로 중지를 했다는 의미이다.							
			break;
		}
		
		ThreadWorking(heartbit, p_data->port, p_data);
		heartbit++;
	}

	TRACE("***[%08x] Exit the task!***\n", p_data->thread_id);
	CloseHandle(p_data->h_thread); // 스레드 종료.

/* 이사님 코드
	EnterCriticalSection(&gh_sum_lock);
	*p_data->p_sum += sum;
	LeaveCriticalSection(&gh_sum_lock);
*/

	if (WaitForSingleObject(p_data->h_kill_event, 10) == WAIT_OBJECT_0)	
		kill_flag = 1; // 1의 의미는 사용자가 스레드를 강제로 중지를 했다는 의미이다.

	// 주소정보를 넘길땐 LPARAM에 넘겨준다. 그런데 WPARAM에 넘겨 줘도 상관은 없지만 관습적으로 LPARAM에 넘겨준다.
	// 메시지를 받는 쪽에서 (부모 대화상자) 27001번 메시지가 들어오게 된다면 어떤 특정 스레드가 종료가 되었다는 정보를 알 수 있다.
	// 그리고 kill_flag가 0이면 시간이 흘러서 종료되었다는 의미이고 (현재 이 코드에서는 강제로 스레드를 죽이는 방식이라는 점을 기억해두자.)
	// kill_flag가 1이면 특정 스레드를 강제로 죽였거나 전체 스레드를 종료했다는 의미이다.
	::PostMessage(p_data->h_wnd, 27001, kill_flag, (LPARAM)p_data);
	
	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+