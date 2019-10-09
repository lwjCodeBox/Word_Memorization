
// Word_Memorization.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWordMemorizationApp:
// See Word_Memorization.cpp for the implementation of this class
//

class CWordMemorizationApp : public CWinApp
{
public:
	CWordMemorizationApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWordMemorizationApp theApp;
