#pragma once

#include "libxl.h"

#define RCLICK_RGB		RGB(0, 255, 128)
#define LDCLICK_RGB		RGB(255, 255, 204)
#define WHITE_RGB		RGB(255, 255, 255)

#define LIGHTYELLOW_COLOR		RGB(255, 255, 204)
#define AQUA_COLOR				RGB(0, 255, 255)
#define PINK_COLOR				RGB(255, 210, 230)

//--------------------------------------------------------------------------------------------
typedef struct DuNode
{
	unsigned char node;
}DuNode;
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
int binarySearch(WORD *data, int size, WORD d);
bool IsBitCheck16(WORD a_Target, WORD a_BitPos);
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
CString GetTextFormExcel(int a_Row, int a_Col, libxl::Sheet *ap_Excel);
//--------------------------------------------------------------------------------------------