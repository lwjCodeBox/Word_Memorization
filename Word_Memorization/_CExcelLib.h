#pragma once

#include "libxl.h"
#include "Word_MemorizationDlg.h"

#include "CSharedMemory.h"

#include <map>

using namespace libxl;

class _CExcelLib
{
public:
	_CExcelLib();
	
	CString getExclSheetName(int a_Sheet);
	bool Load_logical_Port_Adrs(TSharedMemory *ap_SM_Data); // MVB ��ü �ʱ�ȭ
	bool Load_logical_Port_Adrs(); // MVB���� ����ϴ� ��Ʈ �ּҸ� �������� �о��.

	// Du Default1, 2, 3
	CString GetDuDefaultValue(int a_Row, int a_Col, int a_PportAddr) // a_select == 1 is duDefault 1...
	{
		// �׸��� ��Ʈ�� �������� row, col������ ���´µ� 
		// ������ �ִ� ������ �°� �о������ row+3 col+1 �ؾ��Ѵ�.
		Sheet *pSheet = sheetMap.find(a_PportAddr)->second;

		return pSheet->readStr(a_Row, a_Col);		
	}
	// ��Ʈ �ּҿ� �´� libxl::Sheet ������ ��ȯ map <key, value>
	std::map<WORD, Sheet *> m_InitSheetMap();
	std::map<WORD, Sheet *> sheetMap;	
		
private:
	Sheet* getSheetByName(Book* book, const wchar_t* name); // ����ϰ� �ִ� Sheet�� �̸��� ����.

	bool ExcelCertified();
	
	bool Read_DU_Default(); // Read DU Defautl1, 2, 3 CString str[ap_ExcelList[100][2] == CString str(*ap_ExcelList)[2] ���� �ǹ���]
	bool Read_VAC_SDR_SD(); // VAC SDR/SD
	bool Read_DCU_SDR_SD(); // DCU SDR/SD
	bool Read_BECU_SDR_SD(); // BECU SDR/SD
	bool Read_VVVF_SDR_SD(); // VVVF SDR/SD
	// ���� �߰� 2

public:
	WORD mvb_Addr[120]; // myNode �� ������ 120���� �迭�� ũ�⸦ 120���� ����.
	WORD m_totalNodeCnt;

	Book *m_Book;	
	Sheet *m_pSheet2; // logical_port_adrs Sheet

	// du_Defatul1, 2, 3 Sheet	
	Sheet *m_pDU_Default_1, *m_pDU_Default_2, *m_pDU_Default_3; 
	// VAC Sheet
	Sheet *mp_Sheet_VAC_SDR, *mp_Sheet_VAC_SD;
	// DCU Sheet
	Sheet *mp_Sheet_DCU_SDR, *mp_Sheet_DCU_SD;
	// EBCU Sheet
	Sheet *mp_Sheet_EBCU_SDR1, *mp_Sheet_EBCU_SDR2, *mp_Sheet_EBCU_SDR3, *mp_Sheet_EBCU_SD;
	// VVVF Sheet
	Sheet *mp_Sheet_VVVF_SDR, *mp_Sheet_VVVF_SD1, *mp_Sheet_VVVF_SD2;

	// ���� �߰� 4	
}; 