
// Word_MemorizationDlg.h : header file
//

#pragma once

#include "_CExcelLib.h"

#include "CSharedMemory.h"

#include "DefineOfDev_J.h"
#include "Grid_Func_Group.h"

// ȭ�� ��ȯ.
#include "CForm_Protocol.h"
#include "CForm_HeartBit.h"
#include "CForm_DuDefault_1.h"
#include "CForm_SetMVB.h" // ���� MVB �� ����

class _CExcelLib;

// CWordMemorizationDlg dialog
class CWordMemorizationDlg : public CDialogEx
{
// lwj
private:
	CForm_Protocol    *mp_Form_Protocol;
	CForm_HeartBit    *mp_Form_HeartBit;
	CForm_DuDefault_1 *mp_Form_DuDefault_1;
	CForm_SetMVB      *mp_Form_SetMVB;

	unsigned int m_CarButtonRange_StartX;
	unsigned int m_CarButtonRange_EndX;
	unsigned int m_CarButtonRange_StartY;
	unsigned int m_CarButtonRange_EndY;

	unsigned int m_ScreenButtonRange_StartX;
	unsigned int m_ScreenButtonRange_EndX;
	unsigned int m_ScreenButtonRange_StartY;
	unsigned int m_ScreenButtonRange_EndY;

	//unsigned char m_ClickedCarPos[8];
	unsigned char **m_ClickedCarPos = NULL;
	unsigned char m_ClickedScreenPos[5];

// lwj
public:
	_CExcelLib *mp_Libxl;
	
	// aDTC, aMC1 �̸� ��尡 0�ε� ���⼭�� myNode ��� ������ 0�̸� myNode�� �ǹ� �ϰ� 1�̸� 0�� ��带 ����. (���� ��忡�� +1�� ��)
	DuNode nodeData; 

	// Shared Memory
	CSharedMemory *m_sm; // For Allocating Shared Memory (Realtime Protocol)
	TSharedMemory *m_pData; // Pointer of Shared Memory (Realtime Protocol)

	TButtonRect m_trainBTN;
	TButtonRect m_scrBTN;

// Construction
public:
	CWordMemorizationDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORD_MEMORIZATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

// lwj
private:
	afx_msg void ChangeScreen(UINT ID);
	void CreateForm();

	void OnDrawTrainButton(CDC *p_DC, CRect *p_R);
	void OnDrawScreenButton(CDC *p_DC, CRect *p_R);

// lwj
public:
	void SetMVBValue(unsigned int a_Node, unsigned int a_Port, unsigned int a_Value);
	void SetMVBHeartBit(unsigned int a_Port, unsigned int a_Value);
	void SetMVBHeartBit15(unsigned int a_Port, unsigned int a_Value);

	WORD GetWordDataFromSM(WORD a_PortAddr, BYTE a_Node, BYTE a_WordPos);
	BYTE GetByteDataFromSM(WORD a_PortAddr, BYTE a_Node, BYTE a_Byte);
	void SetBitDataToSM(WORD a_PortAddr, BYTE a_Node, BYTE a_Word, BYTE a_ColPos, WORD a_Data);
	void Set16DataToSM(WORD a_PortAddr, BYTE a_Node, BYTE a_Word, WORD a_Data);
	void Set08DataToSM(WORD a_PortAddr, BYTE a_Node, BYTE a_Word, bool a_Pos, BYTE a_Data);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	
	CEdit m_Edit1;	
	CEdit m_Edit2;
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
