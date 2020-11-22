#pragma once

#include "GridCtrl_src_new/GridCtrl.h"

#define IDC_PT_GRID		20001

// CDeviceProtocol dialog

class CDeviceProtocol : public CDialogEx
{
	DECLARE_DYNAMIC(CDeviceProtocol)

private:
	CGridCtrl *mp_PT_Grid = NULL;

public:
	CDeviceProtocol(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDeviceProtocol();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROTOCOL_EXCEL_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
//	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);
};
