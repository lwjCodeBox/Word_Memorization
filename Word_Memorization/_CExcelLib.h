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
	bool Load_logical_Port_Adrs(TSharedMemory *ap_SM_Data); // MVB 전체 초기화
	bool Load_logical_Port_Adrs(); // MVB에서 사용하는 포트 주소를 엑셀에서 읽어옴.

	// Du Default1, 2, 3
	CString GetDuDefaultValue(int a_Row, int a_Col, int a_PportAddr) // a_select == 1 is duDefault 1...
	{
		// 그리드 컨트롤 기준으로 row, col범위가 들어온는데 
		// 엑셀에 있는 범위에 맞게 읽어오려면 row+3 col+1 해야한다.
		Sheet *pSheet = sheetMap.find(a_PportAddr)->second;

		return pSheet->readStr(a_Row, a_Col);		
	}
	// 포트 주소에 맞는 libxl::Sheet 정보를 반환 map <key, value>
	std::map<WORD, Sheet *> m_InitSheetMap();
	std::map<WORD, Sheet *> sheetMap;	
		
private:
	Sheet* getSheetByName(Book* book, const wchar_t* name); // 사용하고 있는 Sheet의 이름을 얻어옴.

	bool ExcelCertified();
	
	bool Read_DU_Default(); // Read DU Defautl1, 2, 3 CString str[ap_ExcelList[100][2] == CString str(*ap_ExcelList)[2] 같은 의미임]
	bool Read_VAC_SDR_SD(); // VAC SDR/SD
	bool Read_DCU_SDR_SD(); // DCU SDR/SD
	bool Read_BECU_SDR_SD(); // BECU SDR/SD
	bool Read_VVVF_SDR_SD(); // VVVF SDR/SD
	bool Read_CCU_IO_VCU(); // CCU/IO/VCU

	// 엑셀 추가 2

public:
	WORD mvb_Addr[120]; // myNode 총 갯수가 120개라서 배열의 크기를 120으로 잡음.
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
	// CCU / IO / VCU Sheet
	Sheet *mp_Sheet_CCU, *mp_Sheet_IO, *mp_Sheet_VCU;

	// 엑셀 추가 4	
}; 