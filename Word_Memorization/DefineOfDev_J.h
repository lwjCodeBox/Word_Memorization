#pragma once

#include <iostream>
#include "libxl.h"
#include <vector>
#include <map>

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
	int colCount; // col °¹¼ö

	int yPos;     // y ½ÃÀÛ ÁÂÇ¥	   //int yPos = 20;    // y ½ÃÀÛ ÁÂÇ¥
	int height;   // ³ôÀÌ		   //int Height = 20; // ³ôÀÌ
	int spacing_H;// y ÁÂÇ¥ °£°Ý    //int spacing_H = 10;   // y ÁÂÇ¥ °£°Ý
	int rowCount; // row °¹¼ö

	std::vector<RECT>/*::iterator */r;
	//std::vector<RECT>::iterator rr;
	//RECT rect;
}TButtonRect;
//--------------------------------------------------------------------------------------------

typedef struct TCaption
{	
	std::map<int, std::wstring> trainBTN_Caption{ {0, L"aDTC"}, {1, L"aMC1"}, {2, L"aMC2"}, {3, L"aMCI"}, 
												  {4, L"bMCI"}, {5, L"bMC2"}, {6, L"bMC1"}, {7, L"bDTC"} };
	std::map<int, std::wstring> srcBTN_Caption{ {0, L"Protocol"}, {1, L"HeartBit"}, {2, L"DU Default"}, {3, L"MyNode"}, {4, L"SetMVB"} };
}TCaption;
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