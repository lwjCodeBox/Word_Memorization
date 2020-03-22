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

		//int readFcode = 0; 

		//byte t_data_buf[500] = { 7, };

		//for (int node = 2; node < 6; node++) // 1 is myNode 
		//{		
		//	for (int i = t_col_start; i < t_col_end + 1; i++)
		//	{
		//		readFcode = m_pSheet2->readNum(i, 5, &format);
		//		if (readFcode != 0)
		//		{
		//			//memcpy(&(ap_SM_Data->data[t_mem_row_idx][0]), t_data_buf, FCODE[readFcode]);
		//			//memset(t_data_buf, 7, 500
		//			memset(&(ap_SM_Data->data[t_mem_row_idx][0]), 7, FCODE[readFcode]);
		//			t_mem_row_idx++;
		//		}
		//		else // fcod가 0인 경우
		//		{
		//			//t_col_end += 1;
		//		}
		//	}
		//}

		/*unsigned char buf[10][10];
		unsigned char arr[5] = { 1,2,3,4,5 };

		
		memcpy(buf, arr, 5);
		memset(buf, 9, sizeof(buf));*/
		return true;
	}

	return false;
}


//bool __fastcall tformmain::loadsavedata(book **p_book) {
//
//	libxl::format *format = null;
//
//	sheet *t_sheet = getsheetbyname(*p_book, l"save");
//	if (!t_sheet) return false;
//
//	const int t_row_start = 4;    // user define
//	const int t_col_start = 6;    // user define
//	int t_row_idx = t_row_start;
//	int t_col_idx = t_col_start;
//	int t_mem_row_idx = 0;
//
//	int t_limit = port_count_per_node * (m_nodecnt + 1);
//
//	byte t_data_buf[max_data_count_per_port] = { 0, };
//	for (int i = 0; i < t_limit; i++) {
//
//		if (!m_signal[i].enabled) {
//			t_row_idx++;
//			continue;
//		}
//
//		for (int j = 0; j < max_data_count_per_port; j++) {
//			t_data_buf[j] = getcellvaluei(t_sheet, t_row_idx, t_col_idx);
//			t_col_idx++;
//		}
//		memcpy(&(m_pdata->data[t_mem_row_idx][0]), t_data_buf, max_data_count_per_port);
//		memset(t_data_buf, 0, max_data_count_per_port);
//		t_col_idx = t_col_start;
//		t_row_idx++;
//		t_mem_row_idx++; // the final count of used port.
//	}
//}

//void _CExcelLib::MVB_Init(TSharedMemory *ap_SM_Data)
//{
//	PWORD pdwLinAdr;
//	HANDLE hPhysicalMemory;
//
//	unsigned short FCODE[4] = { 4, 8, 16, 32 };
//	unsigned short fCode;
//	unsigned short portAdrs;
//	unsigned short sTmpAdrs, sTmpNode;
//	BYTE t_byte[32];
//
//	for (int realCnt = 0; realCnt < MvbCfg.RealPcsCnt; realCnt++) {
//		fCode = ((MvbCfg.Pcs[realCnt].PortCfg[0] >> 12) & 0x000F);
//		portAdrs = MvbCfg.Pcs[realCnt].PortCfg[1];
//
//		//pdwLinAdr = (PWORD)MapPhysToLin((PBYTE)(ADDR_MVB_DPRAM + 0x0000+(portAdrs*8)), 4, &hPhysicalMemory);
//		//pdwLinAdr = (PWORD)g_sm_pData->data[realCnt];
//
//		for (int i = 0; i < FCODE[fCode - 1]; ) {
//			t_byte[i] = ap_SM_Data->data[realCnt][i + 1];
//			t_byte[i + 1] = ap_SM_Data->data[realCnt][i];
//			i += 2;
//		}
//
//		//        if(IntToStr(pdwLinAdr) == "1"){
//		if (portAdrs > 0x1FF) { /* Node Memory mapping */
//			sTmpNode = (portAdrs / 0x200) - 1;
//			sTmpAdrs = (portAdrs % ((portAdrs / 0x200) * 0x200));
//			//                memcpy( &vglo_lcData.allNode[sTmpNode].port[sTmpAdrs],  pdwLinAdr, FCODE[fCode-1]);
//			memcpy(&vglo_lcData.allNode[sTmpNode].Port[sTmpAdrs], t_byte, FCODE[fCode - 1]);
//		}
//		else { /* My Node */
////                memcpy( &vglo_lcData.myNode.port[portAdrs], pdwLinAdr, FCODE[fCode-1]);
//			memcpy(&vglo_lcData.myNode.Port[portAdrs], t_byte, FCODE[fCode - 1]);
//		}
//
//		//UnmapPhysicalMemory(hPhysicalMemory, (PBYTE)pdwLinAdr);
////        }
////        else{
////            UnmapPhysicalMemory(hPhysicalMemory, (PBYTE)pdwLinAdr);
//
////            continue;
////        }
//	}
//
//}
