#include "pch.h"
#include "_CExcelLib.h"

_CExcelLib::_CExcelLib()
{
	 ExcelCertified();
	 InitReadExcel(m_ExcelList);
}

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


bool _CExcelLib::InitReadExcel(CString(*ap_ExcelList)[9])
{
	libxl::Format* format = NULL;

	m_pSheet1 = getSheetByName(m_Book, L"Sheet2");

	if (m_pSheet1) {
		int t_col_start = 2; // (열 시작 위치)
		int t_col_end = 17;
		int t_row_start = 2; // (행 시작 위치)
		int t_row_end = 9;

		for (int i = t_col_start; i < t_col_end + 1; i++) {
			for (int j = t_row_start; j < t_row_end + 1; j++) {
				ap_ExcelList[i - 2][9 - j] = m_pSheet1->readStr(i, j, &format);
			}
		}
		
		m_TotalNode = (int)m_pSheet1->readNum(2, 15, &format);

		return true;
	}

	return false;
}

CString _CExcelLib::getExcelValue(int a_Row, int a_Col)
{
	return m_ExcelList[a_Row][a_Col];
}

CString _CExcelLib::getExclSheetName(int a_Sheet)
{
	return m_Book->getSheet(a_Sheet)->name();
}

int _CExcelLib::getTotalNode()
{
	return m_TotalNode;
}

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

		unsigned short FCODE[5] = {0, 4, 8, 16, 32 };

		int readFcode = 0; 

		for (int i = t_col_start; i < t_col_end + 1; i++)
		{
			readFcode = m_pSheet2->readNum(i, 5, &format);
			if (readFcode != 0)
			{
				memset(&(ap_SM_Data->data[t_mem_row_idx][0]), 8, FCODE[readFcode]);
				t_mem_row_idx++;
			}
			else // fcod가 0인 경우
			{
				//t_col_end += 1;
			}
		}
		return true;
	}

	return false;
}

//bool __fastcall TFormMain::LoadSaveData(Book **p_book) {
//
//	libxl::Format *format = NULL;
//
//	Sheet *t_sheet = getSheetByName(*p_book, L"Save");
//	if (!t_sheet) return false;
//
//	const int t_row_start = 4;    // USER DEFINE
//	const int t_col_start = 6;    // USER DEFINE
//	int t_row_idx = t_row_start;
//	int t_col_idx = t_col_start;
//	int t_mem_row_idx = 0;
//
//	int t_limit = PORT_COUNT_PER_NODE * (m_NodeCnt + 1);
//
//	BYTE t_data_buf[MAX_DATA_COUNT_PER_PORT] = { 0, };
//	for (int i = 0; i < t_limit; i++) {
//
//		if (!m_signal[i].Enabled) {
//			t_row_idx++;
//			continue;
//		}
//
//		for (int j = 0; j < MAX_DATA_COUNT_PER_PORT; j++) {
//			t_data_buf[j] = getCellValueI(t_sheet, t_row_idx, t_col_idx);
//			t_col_idx++;
//		}
//		memcpy(&(m_pData->data[t_mem_row_idx][0]), t_data_buf, MAX_DATA_COUNT_PER_PORT);
//		memset(t_data_buf, 0, MAX_DATA_COUNT_PER_PORT);
//		t_col_idx = t_col_start;
//		t_row_idx++;
//		t_mem_row_idx++; // The Final Count of Used Port.
//	}
//}
