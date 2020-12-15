#include "pch.h"
#include "_CExcelLib.h"

_CExcelLib::_CExcelLib()
{
	 ExcelCertified();

	 Read_DU_Default();
	 Read_VAC_SDR_SD();
	 Read_DCU_SDR_SD();
	 Read_BECU_SDR_SD();
	 Read_VVVF_SDR_SD();

	 sheetMap = m_InitSheetMap();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

std::map<WORD, Sheet *> _CExcelLib::m_InitSheetMap()
{
	std::map<WORD, Sheet *> m;

	// Default1, 2, 3
	m.insert(std::make_pair(0x1A4, m_pDU_Default_1));
	m.insert(std::make_pair(0x1A8, m_pDU_Default_2));
	m.insert(std::make_pair(0x1AC, m_pDU_Default_3));

	// VAC SDR /SD
	m.insert(std::make_pair(0x0B8, mp_Sheet_VAC_SDR)); // VAC SDR1, 2
	m.insert(std::make_pair(0x0BC, mp_Sheet_VAC_SDR)); // VAC SDR3, 4

	m.insert(std::make_pair(0x0B0, mp_Sheet_VAC_SD)); // VAC SD1
	m.insert(std::make_pair(0x0B4, mp_Sheet_VAC_SD)); // VAC SD2
	m.insert(std::make_pair(0x0F0, mp_Sheet_VAC_SD)); // VAC SD3
	m.insert(std::make_pair(0x0F4, mp_Sheet_VAC_SD)); // VAC SD4

	// DCU SDR / SD
	m.insert(std::make_pair(0x0FC, mp_Sheet_DCU_SDR));

	m.insert(std::make_pair(0x0D0, mp_Sheet_DCU_SD)); // L_DCU SD_M 1
	m.insert(std::make_pair(0x0D4, mp_Sheet_DCU_SD)); // R_DCU SD_M 1
	m.insert(std::make_pair(0x0D8, mp_Sheet_DCU_SD)); // L_DCU SD_S 1
	m.insert(std::make_pair(0x0DC, mp_Sheet_DCU_SD)); // R_DCU SD_S 1
	m.insert(std::make_pair(0x0E0, mp_Sheet_DCU_SD)); // L_DCU SD_M 2
	m.insert(std::make_pair(0x0E4, mp_Sheet_DCU_SD)); // R_DCU SD_M 2	
	m.insert(std::make_pair(0x0E8, mp_Sheet_DCU_SD)); // L_DCU SD_S 2
	m.insert(std::make_pair(0x0EC, mp_Sheet_DCU_SD)); // R_DCU SD_S 2

	// BECU SDR / SD
	m.insert(std::make_pair(0x028, mp_Sheet_EBCU_SDR1));
	m.insert(std::make_pair(0x038, mp_Sheet_EBCU_SDR2));
	m.insert(std::make_pair(0x048, mp_Sheet_EBCU_SDR3));

	m.insert(std::make_pair(0x010, mp_Sheet_EBCU_SD)); // EBCU SD1
	m.insert(std::make_pair(0x020, mp_Sheet_EBCU_SD)); // EBCU SD2
	m.insert(std::make_pair(0x030, mp_Sheet_EBCU_SD)); // EBCU SD3
	m.insert(std::make_pair(0x040, mp_Sheet_EBCU_SD)); // EBCU SD4
	
	// VVVF SDR / SD
	m.insert(std::make_pair(0x058, mp_Sheet_VVVF_SDR));

	m.insert(std::make_pair(0x050, mp_Sheet_VVVF_SD1)); // VVVF1 SD1
	m.insert(std::make_pair(0x054, mp_Sheet_VVVF_SD2)); // VVVF1 SD2
	m.insert(std::make_pair(0x060, mp_Sheet_VVVF_SD1)); // VVVF2 SD1
	m.insert(std::make_pair(0x064, mp_Sheet_VVVF_SD2)); // VVVF2 SD2
	m.insert(std::make_pair(0x070, mp_Sheet_VVVF_SD1)); // VVVF3 SD1
	m.insert(std::make_pair(0x074, mp_Sheet_VVVF_SD2)); // VVVF3 SD2
	m.insert(std::make_pair(0x080, mp_Sheet_VVVF_SD1)); // VVVF4 SD1
	m.insert(std::make_pair(0x084, mp_Sheet_VVVF_SD2)); // VVVF4 SD2

	
	return m;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

Sheet* _CExcelLib::getSheetByName(Book* book, const wchar_t* name)
{
	int cnt = book->sheetCount();
	
	for (unsigned short i = 0; i < cnt; ++i)
	{
		if (wcscmp(book->getSheet(i)->name(), name) == 0)
		{
			return book->getSheet(i);
		}
	}
	return 0;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool _CExcelLib::ExcelCertified()
{
	LPCTSTR pszPath = L"..\\Debug\\Config\\MFC_Excel.xlsx";
	m_Book = xlCreateXMLBook();
	if (m_Book) {
		m_Book->setKey(L"JungWook Son", L"windows-2124230806c1e30f66bf6365a7l1hdm8");
		if (m_Book->load(pszPath)) {
			return true;
		}
	}
	AfxMessageBox(L"Can not found excel file");
	return false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

CString _CExcelLib::getExclSheetName(int a_Sheet)
{
	return m_Book->getSheet(a_Sheet)->name();
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool _CExcelLib::Load_logical_Port_Adrs(TSharedMemory *ap_SM_Data)
{
	libxl::Format *format = NULL;

	m_pSheet2 = getSheetByName(m_Book, L"logical_port_adrs_2");

	if (m_pSheet2) {
		int t_col_start = 4; // (열 시작 위치)
		int t_col_end = 123;
		int t_row_start = 4; // (행 시작 위치)
		int t_row_end = 9;

		int t_mem_row_idx = 0;

		unsigned short FCODE[5] = { 0, 4, 8, 16, 32 };

		int readFcode = 0;

		unsigned char arr[5] = { 1,2,3,4,5 };


		for (int node = 1; node < 6; node++) // 1 is myNode 
		{
			for (int i = t_col_start; i < t_col_end + 1; i++)
			{
				readFcode = (int)m_pSheet2->readNum(i, 5, &format);

				if (readFcode != 0)
				{
					memset(&(ap_SM_Data->data[t_mem_row_idx][0]), 2, FCODE[readFcode]);
					t_mem_row_idx++;
				}
			}
		}

		return true;
	}

	return false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool _CExcelLib::Load_logical_Port_Adrs()
{
	libxl::Format *format = NULL;

	m_pSheet2 = getSheetByName(m_Book, L"logical_port_adrs_2");

	int readAddr = 0;
	int mem_row_idx = 0;

	if (m_pSheet2) {
		int readFcode = 0;
		const wchar_t *str = NULL; 

		int t_col_start = 4; // (열 시작 위치)
		int t_col_end = 33;
		int t_row_start = 1;//4; // (행 시작 위치)
		int t_row_end = 16; //3칸
		
		// 엑셀 행, 열 시작 위치를 mvb 주소(addr) 위치를 기준으로 잡음.
		for (int i = t_col_start; i <= t_col_end; i++) {		
			for (int j = t_row_start; j*4 <= t_row_end; j++) {			
				readFcode = (int)m_pSheet2->readNum(i, j*4+1, &format); // fcode 위치 정보

				if (readFcode != 0) {
					str = m_pSheet2->readStr(i, j*4, &format); // addr
					readAddr = _tcstoul(str, NULL, 16); // 문자열을 16진수로 변환.

					mvb_Addr[mem_row_idx] = readAddr;					
					mem_row_idx++;
				}
			}
		}
		m_totalNodeCnt = mem_row_idx; // 실제로 사용하는 노드 갯수.

		return true;
	}
	return false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool _CExcelLib::Read_DU_Default()
{
	libxl::Format *format = NULL;

	int col_start = 2; // (열 시작 위치)
	int col_end = 9;
	int row_start = 5; // (행 시작 위치)
	int row_end = 36;
	
	m_pDU_Default_1 = getSheetByName(m_Book, L"du_default1");
	m_pDU_Default_2 = getSheetByName(m_Book, L"du_default2");
	m_pDU_Default_3 = getSheetByName(m_Book, L"du_default3");

	if ((m_pDU_Default_1 != NULL) && (m_pDU_Default_2 != NULL) && (m_pDU_Default_3 != NULL)) {
		/*
		for (int i = row_start; i <= row_end; i++) {
			for (int j = col_start; j <= col_end; j++) {
				ap_Excel_DuDefault_1[i - 5][9 - j] = m_pDU_Default_1->readStr(i, j, &format);
				ap_Excel_DuDefault_2[i - 5][9 - j] = m_pDU_Default_2->readStr(i, j, &format);
				ap_Excel_DuDefault_3[i - 5][9 - j] = m_pDU_Default_3->readStr(i, j, &format);
			}
		}
		*/
		return true;
	}
	else {
		AfxMessageBox(L"엑셀 sheet du_default1, du_default2, du_default3 중에 하나를 읽어오지 못했습니다.");
		return false;
	}
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool _CExcelLib::Read_VAC_SDR_SD()
{
	mp_Sheet_VAC_SDR = getSheetByName(m_Book, L"VAC_SDR");
	mp_Sheet_VAC_SD = getSheetByName(m_Book, L"VAC_SD");

	if ((mp_Sheet_VAC_SDR != NULL) && (mp_Sheet_VAC_SD != NULL))
	{
		return true;
	}
	else {
		AfxMessageBox(L"엑셀 VAC SDR / SD를 읽어오지 못했습니다.");
		return false;
	}

	return false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool _CExcelLib::Read_BECU_SDR_SD()
{
	mp_Sheet_EBCU_SDR1 = getSheetByName(m_Book, L"EBCU_SDR1");
	mp_Sheet_EBCU_SDR2 = getSheetByName(m_Book, L"EBCU_SDR2");
	mp_Sheet_EBCU_SDR3 = getSheetByName(m_Book, L"EBCU_SDR3");
	mp_Sheet_EBCU_SD   = getSheetByName(m_Book, L"EBCU_SD");

	if ((mp_Sheet_EBCU_SDR1 != NULL) && (mp_Sheet_EBCU_SDR2 != NULL) && 
		(mp_Sheet_EBCU_SDR3 != NULL) && (mp_Sheet_EBCU_SD != NULL)) 
	{	
		return true;
	}
	else {
		AfxMessageBox(L"엑셀 BECU SDR / SD를 읽어오지 못했습니다.");
		return false;
	}

	return false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool _CExcelLib::Read_VVVF_SDR_SD()
{
	mp_Sheet_VVVF_SDR = getSheetByName(m_Book, L"VVVF_SDR");
	mp_Sheet_VVVF_SD1 = getSheetByName(m_Book, L"VVVF_SD1");
	mp_Sheet_VVVF_SD2 = getSheetByName(m_Book, L"VVVF_SD2");

	if ((mp_Sheet_VVVF_SDR != NULL) && (mp_Sheet_VVVF_SD1 != NULL) && (mp_Sheet_VVVF_SD2 != NULL)) {		
		return true;
	}
	else {
		AfxMessageBox(L"엑셀 VVVF SDR / SD를 읽어오지 못했습니다.");
		return false;
	}

	return false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

bool _CExcelLib::Read_DCU_SDR_SD()
{
	mp_Sheet_DCU_SDR = getSheetByName(m_Book, L"DCU_SDR");
	mp_Sheet_DCU_SD = getSheetByName(m_Book, L"DCU_SD");

	if ((mp_Sheet_DCU_SDR != NULL) && (mp_Sheet_DCU_SD != NULL)) {		
		return true;
	}
	else {
		AfxMessageBox(L"엑셀 DCU SDR / SD를 읽어오지 못했습니다.");
		return false;
	}

	return false;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+