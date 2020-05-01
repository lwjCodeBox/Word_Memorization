#pragma once


// CTab2 dialog

class CWordMemorizationDlg;
class CTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab2)

public:
	CTab2(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTab2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListControl;
	CFont m_editFont;
	
	CWordMemorizationDlg* mp_MainDlg;
// Function List
public:
	void ListInitialize();
};
