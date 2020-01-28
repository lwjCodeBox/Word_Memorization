#pragma once


// CTab1 dialog

#define MAX_BTN 5

#define BTN_ID_1 10001
#define BTN_ID_2 10002
#define BTN_ID_3 10003
#define BTN_ID_4 10004
#define BTN_ID_5 10005

class CTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab1)

public:
	CTab1(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTab1();

	CButton **m_pBtn;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

};
