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
	bool Load_logical_Port_Adrs(); // MVB에서 사용하는 포트 주소를 엑셀에서 읽어옴.

	// Du Default1, 2, 3
	CString GetDuDefaultValue(int a_Row, int a_Col, int a_select) // a_select == 1 is duDefault 1...
	{
		switch (a_select) {
		case 1:
			return m_Excel_DuDefault_1[a_Row][a_Col];
			
		case 2:
			return m_Excel_DuDefault_2[a_Row][a_Col];

		case 3:
			return m_Excel_DuDefault_3[a_Row][a_Col];
		}
		return L"err";
	}

	Sheet *GetSheet(WORD a_Addr) 
	{
		Sheet *p = NULL;
		if (a_Addr == 0x1A4) {
			p = m_pDU_Default_1;
		}
		else if (a_Addr == 0x1A8) {
			p = m_pDU_Default_2;
		}
		else if (a_Addr == 0x1AC) {
			p = m_pDU_Default_3;
		}
		else return 0;

		return p;
		//else return NULL;
	}
private:
	Sheet* getSheetByName(Book* book, const wchar_t* name); // 사용하고 있는 Sheet의 이름을 얻어옴.

	bool ExcelCertified();
	bool InitReadExcel(CString (*ap_ExcelList)[9]); // ap_ExcelList[100][2] == (*ap_ExcelList)[2] 같은 의미임
	// Read DU Defautl1, 2, 3
	bool Read_DU_Default(CString(*ap_Excel_DuDefault_1)[8], CString(*ap_Excel_DuDefault_2)[8], CString(*ap_Excel_DuDefault_3)[8]);



public:
	Book* m_Book;
	Sheet* m_pSheet1; 
	Sheet *m_pSheet2; // logical_port_adrs Sheet
	Sheet *m_pDU_Default_1, *m_pDU_Default_2, *m_pDU_Default_3; // du_Defatul1, 2, 3 Sheet

	WORD mvb_Addr[120]; // myNode 총 갯수가 120개라서 배열의 크기를 120으로 잡음.
	BYTE m_totalNodeCnt;
	
private:
	CString m_ExcelList[18][9]; 
	int m_TotalNode;
	
	// Du Default1, 2, 3
	CString m_Excel_DuDefault_1[32][8];
	CString m_Excel_DuDefault_2[32][8];
	CString m_Excel_DuDefault_3[32][8];

}; 

 