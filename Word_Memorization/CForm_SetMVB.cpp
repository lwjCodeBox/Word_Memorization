// CForm_SetMVB.cpp : implementation file
//

#include "pch.h"
#include "Word_Memorization.h"
#include "CForm_SetMVB.h"

#include "Word_MemorizationDlg.h"

#include "_CExcelLib.h"
#include "DefineOfDev_J.h"

// CForm_SetMVB

IMPLEMENT_DYNCREATE(CForm_SetMVB, CFormView)

CForm_SetMVB::CForm_SetMVB()
	: CFormView(IDD_FORM_SETMVB)
{

}

CForm_SetMVB::~CForm_SetMVB()
{
	// Timer
	/*KillTimer(USER_TIMER_0);
	KillTimer(USER_TIMER_1);
	KillTimer(USER_TIMER_2);
	KillTimer(USER_TIMER_3);*/

}

void CForm_SetMVB::DoDataExchange(CDataExchange *pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SETMVB_ADDR, str_SetAddr);
	DDX_Control(pDX, IDC_SETMVB_WORD, str_SetWord);
	DDX_Control(pDX, IDC_SETMVB_VALUE, str_SetValue);
}

BEGIN_MESSAGE_MAP(CForm_SetMVB, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CForm_SetMVB::OnBnClickedButton1)
	ON_WM_TIMER()

	ON_COMMAND_RANGE(IDC_SETMVB_TM_START_0, IDC_SETMVB_TM_START_3, TiemerStart)
	ON_COMMAND_RANGE(IDC_SETMVB_TM_STOP_0, IDC_SETMVB_TM_STOP_3, TimerStop)
END_MESSAGE_MAP()


// CForm_SetMVB diagnostics

#ifdef _DEBUG
void CForm_SetMVB::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CForm_SetMVB::Dump(CDumpContext &dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CForm_SetMVB message handlers


BOOL CForm_SetMVB::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CForm_SetMVB::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}


void CForm_SetMVB::OnBnClickedButton1()
{
	WORD portAddr, word, value;

	CString strPortAddr;
	GetDlgItemText(IDC_SETMVB_ADDR, strPortAddr);
	portAddr = _tcstoul(strPortAddr, NULL, 16); // 문자열을 16진수로 변환.

	word = GetDlgItemInt(IDC_SETMVB_WORD);
	word *= 2;

	value = GetDlgItemInt(IDC_SETMVB_VALUE);

	BYTE node;
	node = GetDlgItemInt(IDC_SETMVB_NODE); // 0이면 myNode를 의미함.

	mp_FormMainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	if (mp_FormMainDlg != NULL) {
		//mp_FormMainDlg->SetMVBValue(node, port, value);

		BYTE l_byte, h_byte;

		_CExcelLib *p_ExcelLib = (_CExcelLib *)mp_FormMainDlg->mp_Libxl;
		int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);
		int t_port = binarySearch(p_ExcelLib->mvb_Addr, dataSize, portAddr);
		
		t_port += p_ExcelLib->m_totalNodeCnt * node;

		h_byte = ((unsigned char *)&value)[1]; // word 상위
		l_byte = ((unsigned char *)&value)[0]; // word 하위

		memset(&(mp_FormMainDlg->m_pData->data[t_port][word]), h_byte, 1);   // mvb 상위 바이트에 값을 넣음
		memset(&(mp_FormMainDlg->m_pData->data[t_port][word+1]), l_byte, 1); // mvb 하위 바이트에 값을 넣음

		p_ExcelLib = NULL;
	}

	mp_FormMainDlg = NULL;

}


void CForm_SetMVB::OnTimer(UINT_PTR nIDEvent)
{
	unsigned int port;
	mp_FormMainDlg = (CWordMemorizationDlg *)::AfxGetApp()->GetMainWnd();

	switch (nIDEvent)
	{
	case USER_TIMER_0:
		port = GetDlgItemInt(IDC_SETMVB_TM_PORT0);

		if (m_HeartBit_0 != 0xFFFF) {
			m_HeartBit_0++;

			mp_FormMainDlg->SetMVBHeartBit(port, m_HeartBit_0);
			//memset(&(mp_FormMainDlg->m_pData->data[port][0]), m_HeartBit_0, 2);
		}
		else
			m_HeartBit_0 = 0;

		break;

	case USER_TIMER_1:
		port = GetDlgItemInt(IDC_SETMVB_TM_PORT1);

		if (m_HeartBit_1 != 0xFFFF) {
			m_HeartBit_1++;

			//mp_FormMainDlg->SetMVBHeartBit(port, m_HeartBit_1);
			memset(&(mp_FormMainDlg->m_pData->data[port][0]), m_HeartBit_1, 2);
		}
		else
			m_HeartBit_1 = 0;

		break;

	case USER_TIMER_2:
		port = GetDlgItemInt(IDC_SETMVB_TM_PORT2);

		if (m_HeartBit_2 != 0xFFFF) {
			m_HeartBit_2++;

			mp_FormMainDlg->SetMVBHeartBit(port, m_HeartBit_2);
			//memset(&(mp_FormMainDlg->m_pData->data[port][0]), m_HeartBit_2, 2);
		}
		else
			m_HeartBit_2 = 0;

		break;

	case USER_TIMER_3:
		port = GetDlgItemInt(IDC_SETMVB_TM_PORT3);

		if (m_HeartBit_3 != 0xFFFF) {
			m_HeartBit_3++;

			mp_FormMainDlg->SetMVBHeartBit(port, m_HeartBit_3);
			//memset(&(mp_FormMainDlg->m_pData->data[port][0]), m_HeartBit_3, 2);
		}
		else
			m_HeartBit_3 = 0;

		break;
	}

	mp_FormMainDlg = NULL;

	CFormView::OnTimer(nIDEvent);
}


void CForm_SetMVB::TiemerStart(UINT ID)
{
	switch (ID - IDC_SETMVB_TM_START_0)
	{
	case 0:
		m_HeartBit_0 = 0;
		SetTimer(USER_TIMER_0, 300, NULL);
		break;

	case 1:
		m_HeartBit_1 = 0;
		SetTimer(USER_TIMER_1, 300, NULL);
		break;

	case 2:
		m_HeartBit_2 = 0;
		SetTimer(USER_TIMER_2, 300, NULL);
		break;

	case 3:
		m_HeartBit_3 = 0;
		SetTimer(USER_TIMER_3, 300, NULL);
		break;
	}
}


void CForm_SetMVB::TimerStop(UINT ID)
{
	switch (ID - IDC_SETMVB_TM_STOP_0)
	{
	case 0:
		KillTimer(USER_TIMER_0);
		break;

	case 1:
		KillTimer(USER_TIMER_1);
		break;

	case 2:
		KillTimer(USER_TIMER_2);
		break;

	case 3:
		KillTimer(USER_TIMER_3);
		break;
	}

}

