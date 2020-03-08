#pragma once

#include "libxl.h"
#include "Word_MemorizationDlg.h"

#include "CSharedMemory.h"

using namespace libxl;

class _CExcelLib
{
public:
	_CExcelLib();

	CString getExcelValue(int a_Row, int a_Col);
	CString getExclSheetName(int a_Sheet);
	int getTotalNode();
	bool Load_logical_Port_Adrs(TSharedMemory *ap_SM_Data);

private:
	Sheet* getSheetByName(Book* book, const wchar_t* name); // ����ϰ� �ִ� Sheet�� �̸��� ����.

	bool ExcelCertified();
	bool InitReadExcel(CString (*ap_ExcelList)[9]); // ap_ExcelList[100][2] == (*ap_ExcelList)[2] ���� �ǹ���

public:
	Book* m_Book;
	Sheet* m_pSheet1; 
	Sheet *m_pSheet2; // logical_port_adrs Sheet
	
private:
	CString m_ExcelList[18][9];   
	int m_TotalNode;
}; 

 