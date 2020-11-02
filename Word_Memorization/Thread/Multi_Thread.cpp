#include "pch.h"

/// <Developed by developer Wonjong>
/// * 멀티 스레드 코드임.
/// * Copyright 2020.10.28 이원종. All rights reserved.
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

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ThreadWorking(int a_port, ThreadData *ap_data)
{	
	CWordMemorizationDlg *parentdlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();
	
	int i = 0;
	while (true) {
		if (!ap_data->flag) return;
		
		memset(&(parentdlg->m_pData->data[a_port][1]), i, 1);
		i++;
		Sleep(100);
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

DWORD WINAPI SM_Thread_Run(void *ap_data)
{
	ThreadData *p_data = (ThreadData *)ap_data;
	int kill_flag = 0;
	
	if (WaitForSingleObject(p_data->h_kill_event, 0) == WAIT_OBJECT_0)	kill_flag = 1;
				
	//
	TRACE("[%08x] Thread Start!\n", p_data->thread_id);	
	threadItemPtr.p_ptr[p_data->thread_count] = p_data;
	ThreadWorking(p_data->port, p_data);
	TRACE("[%08x] Thread Stop!\n", p_data->thread_id);
	//

	CloseHandle(p_data->h_thread);

/* 이사님 코드
	EnterCriticalSection(&gh_sum_lock);
	*p_data->p_sum += sum;
	LeaveCriticalSection(&gh_sum_lock);
*/

	if (WaitForSingleObject(p_data->h_kill_event, 0) == WAIT_OBJECT_0)	kill_flag = 1;		
	::PostMessage(p_data->h_wnd, 27001, kill_flag, (LPARAM)p_data);
	
	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+