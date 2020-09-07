#pragma once

#include "libxl.h"

#define RCLICK_RGB		RGB(0, 255, 128)
#define LDCLICK_RGB		RGB(255, 255, 204)
#define WHITE_RGB		RGB(255, 255, 255)

#define LIGHTYELLOW_COLOR		RGB(255, 255, 204)
#define ORANGE_COLOR			RGB(255, 200, 100)
#define AQUA_COLOR				RGB(0, 255, 255)
#define PINK_COLOR				RGB(255, 210, 230)

//--------------------------------------------------------------------------------------------
typedef struct DuNode
{
	unsigned char node;
}DuNode;

typedef struct TButtonRect
{
	int xPos;     // x ½ÃÀÛ ÁÂÇ¥    //int xPos = 20;     // x ½ÃÀÛ ÁÂÇ¥
	int width;    // Æø »çÀÌÁî	   //int width = 100;   // Æø »çÀÌÁî
	int spacing_W;// x ÁÂÇ¥ °£°Ý	   //int spacing_W = 5; // x ÁÂÇ¥ °£°Ý
	int rowCount; // row °¹¼ö

	int yPos;     // y ½ÃÀÛ ÁÂÇ¥	   //int yPos = 20;    // y ½ÃÀÛ ÁÂÇ¥
	int height;   // ³ôÀÌ		   //int Height = 20; // ³ôÀÌ
	int spacing_H;// y ÁÂÇ¥ °£°Ý    //int spacing_H = 10;   // y ÁÂÇ¥ °£°Ý
	int colCount; // col °¹¼ö
}TButtonRect;
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
int binarySearch(WORD *data, int size, WORD d);
bool IsBitCheck16(WORD a_Target, WORD a_BitPos);
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
CString GetTextFormExcel(int a_Row, int a_Col, libxl::Sheet *ap_Excel);
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void TrainButtonPos(int a_StartPos, int a_RowCount, int a_ColCount);
//--------------------------------------------------------------------------------------------