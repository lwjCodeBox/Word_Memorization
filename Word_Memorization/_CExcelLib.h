#pragma once

#include "libxl.h"
#include "Word_MemorizationDlg.h"

#include "CSharedMemory.h"

using namespace libxl;

class _CExcelLib
{
public:
	_CExcelLib();
	
	CString getExclSheetName(int a_Sheet);
	bool Load_logical_Port_Adrs(TSharedMemory *ap_SM_Data); // MVB ��ü �ʱ�ȭ
	bool Load_logical_Port_Adrs(); // MVB���� ����ϴ� ��Ʈ �ּҸ� �������� �о��.

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
		if (a_Addr == 0x1A4)		return m_pDU_Default_1;
		else if (a_Addr == 0x1A8)	return m_pDU_Default_2;
		else if (a_Addr == 0x1AC)	return m_pDU_Default_3;
		else return NULL;
	}
	
private:
	Sheet* getSheetByName(Book* book, const wchar_t* name); // ����ϰ� �ִ� Sheet�� �̸��� ����.

	bool ExcelCertified();
	// Read DU Defautl1, 2, 3 [ap_ExcelList[100][2] == (*ap_ExcelList)[2] ���� �ǹ���]
	bool Read_DU_Default(CString(*ap_Excel_DuDefault_1)[8], CString(*ap_Excel_DuDefault_2)[8], CString(*ap_Excel_DuDefault_3)[8]);
	// BECU SDR/SD
	bool Read_BECU_SDR_SD();

public:
	Book *m_Book;	
	Sheet *m_pSheet2; // logical_port_adrs Sheet
	Sheet *m_pDU_Default_1, *m_pDU_Default_2, *m_pDU_Default_3; // du_Defatul1, 2, 3 Sheet

	WORD mvb_Addr[120]; // myNode �� ������ 120���� �迭�� ũ�⸦ 120���� ����.
	BYTE m_totalNodeCnt;
	
private:	
	// Du Default1, 2, 3
	CString m_Excel_DuDefault_1[32][8];
	CString m_Excel_DuDefault_2[32][8];
	CString m_Excel_DuDefault_3[32][8];

	// BECU SDR/SD
	

}; 

 