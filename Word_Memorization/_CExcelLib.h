#pragma once

#include "libxl.h"
#include "Word_MemorizationDlg.h"

using namespace libxl;

class _CExcelLib
{
public:
	_CExcelLib();

	CString getExcelValue(int a_Row, int a_Col);
	CString getExclSheetName(int a_Sheet);

private:
	Sheet* getSheetByName(Book* book, const wchar_t* name); // ����ϰ� �ִ� Sheet�� �̸��� ����.

	bool ExcelCertified();
	bool InitReadExcel(CString (*ap_ExcelList)[9]); // ap_ExcelList[100][2] == (*ap_ExcelList)[2] ���� �ǹ���

public:
	Book* m_Book;
	Sheet* m_pSheet1;
	
private:
	CString m_ExcelList[18][9];   
}; 

 