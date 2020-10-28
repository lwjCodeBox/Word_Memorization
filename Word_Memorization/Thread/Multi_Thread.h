#pragma once

/// <Developed by developer Wonjong>
/// * 멀티 스레드 코드임.
/// * Copyright 2020.10.28 이원종. All rights reserved.
/// </Developed by developer Wonjong>

typedef struct ThreadData
{
	HWND h_wnd;
	//CListBox *p_list_box;
	HANDLE h_kill_event;
	HANDLE h_thread;
	DWORD thread_id;

	unsigned int thread_count;
	//unsigned int start_step, end_step, thread_count;	
	__int64 *p_sum;
}ThreadData;
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
DWORD WINAPI SM_Thread_Run(void *ap_data);
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+