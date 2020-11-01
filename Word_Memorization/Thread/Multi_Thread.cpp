#include "pch.h"

/// <Developed by developer Wonjong>
/// * 멀티 스레드 코드임.
/// * Copyright 2020.10.28 이원종. All rights reserved.
/// </Developed by developer Wonjong>

#include "Multi_Thread.h"
#include "../Word_MemorizationDlg.h"

class CWordMemorizationDlg;

int ThreadWorking(int a_num)
{
	CWordMemorizationDlg *mp_ParentDlg;// = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();
	

	//TSharedMemory *m_pData;
	//m_pData = (TSharedMemory *)GetData();

	//for (int i = 2; i < a_num; i++) {
		//memset(&(mp_ParentDlg->m_pData->data[2][1]), 2, 1);
		//memset(&(mp_FormMainDlg->m_pData->data[port][1]), m_HeartBit_2, 1);
		Sleep(10);
	//}
	return 1;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//ThreadData GetThreadDataPtr(int a_num)
//{
//	
//	try { 
//		//v.at(a_num);
//	}
//	catch (std::out_of_range &e) { AfxMessageBox(L"Catch the std::out_of_range(thread pointer Pos)"); }
//}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

DWORD WINAPI SM_Thread_Run(void *ap_data)
{
	ThreadData *p_data = (ThreadData *)ap_data;
	
	int index;
		
	TRACE("[%08x] Thread Start!\n", p_data->thread_id);

	__int64 sum = 0;
	int start_tick = GetTickCount(), kill_flag = 0;
	unsigned int i;
	
	if (WaitForSingleObject(p_data->h_kill_event, 0) == WAIT_OBJECT_0)	kill_flag = 1;
		
	//if (ThreadWorking(i)) sum += i;
	ThreadWorking(10000);
	
	TRACE("[%08x] Thread Stop!\n", p_data->thread_id);

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