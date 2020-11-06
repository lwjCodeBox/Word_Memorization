#pragma once

/// <Developed by developer Wonjong>
/// * ��Ƽ ������ �ڵ���.
/// * Copyright 2020.11.04 �̿���. All rights reserved.
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
// ��ư�� Ŭ���� ��ġ�� ��ȣ�� ���� �迭�� �� ��°�� ��ġ�ߴ��� ã�� �迭�� ��ġ�� ������ ������ ������.
void *GetThreadPtr(int a_pos);
// ���� �迭�� �ִ� ������ ������ ������.
void *GetThreadPtr_2(int a_pos);
int ThreadWorking(unsigned int a_heartbit, int a_port, ThreadData *ap_data);
DWORD WINAPI SM_Thread_Run(void *ap_data);
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+