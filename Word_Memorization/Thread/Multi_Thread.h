/// <Developed by developer Wonjong>
/// * ��Ƽ ������ �ڵ���.
/// * Copyright 2020.10.28 �̿���. All rights reserved.
/// </Developed by developer Wonjong>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#define MAX_THREAD_CNT 10;

struct ThreadData
{
	HWND h_wnd;
	HANDLE h_kill_event;
	HANDLE h_thread;
	DWORD thread_id;

	// lwj - 2020.11.02
	unsigned int thread_count; // �ʿ� ����...
	unsigned int port;
	bool flag;

	//unsigned int start_step, end_step, thread_count;	
	__int64 *p_sum;
};

struct TDataPtr
{
	void *p_ptr[10];
};
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void *GetThreadPtr(int a_pos);
void DeleteThreadPtr(int a_pos);
void ThreadWorking(int a_port, ThreadData *ap_data);
DWORD WINAPI SM_Thread_Run(void *ap_data);
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+