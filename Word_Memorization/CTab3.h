#pragma once


// CTab3 dialog


//class _CExcelLib;
class CWordMemorizationDlg;
class CTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab3)

private:
	CWordMemorizationDlg *mp_MainDlg;
	// 이 배열로 셀색상을 라임색과 회색 둘중 하나를 사용할수 있게 판단할수 있다.
	// 0이면 클릭을 안했다는 의미, 1이면 클릭을 했다는 의미.
	unsigned char m_CellClickStatus[15][8]; 
	
private:
	void PrintSelectedCell(int a_Col, int a_Row);
	void PrintInitializeCell(CPaintDC *a_DC);
	void FixedCellText(CPaintDC *a_DC);

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
