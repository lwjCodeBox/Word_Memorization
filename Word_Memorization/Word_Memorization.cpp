
// Word_Memorization.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "Word_Memorization.h"
#include "Word_MemorizationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWordMemorizationApp

BEGIN_MESSAGE_MAP(CWordMemorizationApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWordMemorizationApp construction

CWordMemorizationApp::CWordMemorizationApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CWordMemorizationApp object

CWordMemorizationApp theApp;


// CWordMemorizationApp initialization

BOOL CWordMemorizationApp::InitInstance()
{
	CWinApp::InitInstance();

	CWordMemorizationDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

