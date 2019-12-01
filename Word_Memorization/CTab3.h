#pragma once


// CTab3 dialog


//class _CExcelLib;
class CWordMemorizationDlg;
class CTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab3)

private:
	CWordMemorizationDlg *mp_MainDlg;
	unsigned char m_CellClickStatus[15]; // 15개의 행을 말하며 열은 비트로 쪼개서 현재 셀이 클릭되었었는지 확인함.
	
private:
	void PrintSelectedCell(int a_Col, int a_Row);
	void PrintInitializeCell(CPaintDC *a_DC);
	unsigned char BitSetting(unsigned char a_BitPos);

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
