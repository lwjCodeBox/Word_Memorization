
// Word_MemorizationDlg.h : header file
//

#pragma once

#include "_CExcelLib.h"

#include "CSharedMemory.h"

#include "DefineOfDev_J.h"

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

// lwj
public:
	_CExcelLib *mp_Libxl;
	
	// aDTC, aMC1 �̸� ��尡 0�ε� ���⼭�� myNode ��� ������ 0�̸� myNode�� �ǹ� �ϰ� 1�̸� 0�� ��带 ����. (���� ��忡�� +1�� ��)
	DuNode nodeData; 

	// Shared Memory
	CSharedMemory *m_sm; // For Allocating Shared Memory (Realtime Protocol)
	TSharedMemory *m_pData; // Pointer of Shared Memory (Realtime Protocol)

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
	afx_msg void SelectedCar(UINT ID);
	void CreateForm();

// lwj
public:
	void SetMVBValue(unsigned char a_Node, unsigned char a_Port, unsigned char a_Value);
	void SetMVBHeartBit(unsigned char a_Port, unsigned char a_Value);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	
	CEdit m_Edit1;	
	CEdit m_Edit2;
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
