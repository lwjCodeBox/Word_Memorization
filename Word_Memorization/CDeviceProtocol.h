#pragma once

#include "GridCtrl_src_new/GridCtrl.h"
#include "_CExcelLib.h"

#define IDC_PT_GRID		20001

// CDeviceProtocol dialog

class CDeviceProtocol : public CDialogEx, private _CExcelLib
{
	DECLARE_DYNAMIC(CDeviceProtocol)

private:
	CGridCtrl *mp_PT_Grid = NULL;
	
	CString m_deviceName;
	short m_port;
	int m_node;
	
	unsigned char m_page = 0;
	BYTE **mp_click;
public:
	CDeviceProtocol(BYTE *ap_IsClickedPos, CString a_device, int a_port, int a_node, CWnd* pParent = nullptr);   // standard constructor

	virtual ~CDeviceProtocol();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROTOCOL_EXCEL_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT *);
	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT *);

	DECLARE_MESSAGE_MAP()

private:
	void CreateGrid(int a_port, int a_node);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBnClickedPageDownBtn();
	afx_msg void OnBnClickedPageUpBtn();
};
