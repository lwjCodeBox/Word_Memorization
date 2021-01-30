#pragma once

#include "GridCtrl_src_new/GridCtrl.h"
#include "_CExcelLib.h"
#include <String/WJ_String.h>

#define IDC_PT_GRID		20001

// CDeviceProtocol dialog

class CDeviceProtocol : public CDialogEx, private _CExcelLib
{
	DECLARE_DYNAMIC(CDeviceProtocol)

private:
	CGridCtrl *mp_PT_Grid = NULL;
	
	WJ_String m_deviceName;
	WJ_String m_caption;
	short m_port;
	int m_node;
	
	HWND h_handle;

	int m_map_key;
	unsigned char m_page = 0;

public:
	CDeviceProtocol(WJ_String a_device, WJ_String a_caption, int a_port, int a_node, CWnd* pParent = nullptr);   // standard constructor
	
	virtual ~CDeviceProtocol();

	void SetHWND(HWND h) { h_handle = h; }

	void SetMapKey(int a_key) { m_map_key = a_key; }
	int GetMapKey() { return m_map_key; }

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROTOCOL_POPUP };
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
	afx_msg void OnBnClickedExitBtn();
};
