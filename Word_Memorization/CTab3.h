#pragma once


// CTab3 dialog

// ********* Button *********
#define MAX_BTN 11

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

#define BTN_SEND 20000
// **************************

// ********** Edit **********
#define MAX_EDIT 3
#define EDIT_ID_1  20001
#define EDIT_ID_2  20002
#define EDIT_ID_3  20003
// **************************

// ********* Timer **********
#define USER_TIMER_0 30000
// **************************


//class _CExcelLib;
class CWordMemorizationDlg;
class CTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CTab3)

private:
	CWordMemorizationDlg *mp_MainDlg;
	// �� �迭�� �������� ���ӻ��� ȸ�� ���� �ϳ��� ����Ҽ� �ְ� �Ǵ��Ҽ� �ִ�.
	// 0�̸� Ŭ���� ���ߴٴ� �ǹ�, 1�̸� Ŭ���� �ߴٴ� �ǹ�.
	unsigned char m_CellClickStatus[15][8]; 

	CButton **m_pBtn; // ��ư ����
	CEdit **m_pEdit;// ����Ʈ ����

	unsigned short m_HeartBit;

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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
