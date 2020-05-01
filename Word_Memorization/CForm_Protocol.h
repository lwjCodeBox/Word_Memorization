#pragma once



// CForm_Protocol form view

class CForm_Protocol : public CFormView
{
	DECLARE_DYNCREATE(CForm_Protocol)

public://protected:
	CForm_Protocol();           // protected constructor used by dynamic creation
	virtual ~CForm_Protocol();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_PROTOCOL };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT &rect, CWnd *pParentWnd, UINT nID, CCreateContext *pContext = NULL);
	virtual void OnInitialUpdate();
};


