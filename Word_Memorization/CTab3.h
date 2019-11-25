#pragma once


// CTab3 dialog


//class _CExcelLib;
class CWordMemorizationDlg;
class CTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab3)

private:
	CWordMemorizationDlg *mp_MainDlg;

private:
	void PrintExcelSheet(int a_Col, int a_Row);

public:
	CTab3(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTab3();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
