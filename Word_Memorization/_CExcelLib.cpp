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
