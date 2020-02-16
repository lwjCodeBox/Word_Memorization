#pragma once


// CTab3 dialog

#define MAX_BTN 10

#define BTN_ID_1  10001
#define BTN_ID_2  10002
#define BTN_ID_3  10003
#define BTN_ID_4  10004
#define BTN_ID_5  10005
#define BTN_ID_6  10006
#define BTN_ID_7  10007
#define BTN_ID_8  10008
#define BTN_ID_9  10009
#define BTN_ID_10 100010

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

	CButton **m_pBtn; // 버튼 생성
	
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
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void OnButtonEvent(UINT ID);
};
