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
	bool Load_logical_Port_Adrs(TSharedMemory *ap_SM_Data); // MVB 전체 초기화
	void _CExcelLib::Load_logical_Port_Adrs(); // MVB에서 사용하는 포트 주소를 엑셀에서 읽어옴.

private:
	Sheet* getSheetByName(Book* book, const wchar_t* name); // 사용하고 있는 Sheet의 이름을 얻어옴.

	bool ExcelCertified();
	bool InitReadExcel(CString (*ap_ExcelList)[9]); // ap_ExcelList[100][2] == (*ap_ExcelList)[2] 같은 의미임

public:
	Book* m_Book;
	Sheet* m_pSheet1; 
	Sheet *m_pSheet2; // logical_port_adrs Sheet

	WORD mvb_Addr[120]; // myNode 총 갯수가 120개라서 배열의 크기를 120으로 잡음.
	
private:
	CString m_ExcelList[18][9];   
	int m_TotalNode;
}; 

 