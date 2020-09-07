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
	int xPos;     // x ���� ��ǥ    //int xPos = 20;     // x ���� ��ǥ
	int width;    // �� ������	   //int width = 100;   // �� ������
	int spacing_W;// x ��ǥ ����	   //int spacing_W = 5; // x ��ǥ ����
	int rowCount; // row ����

	int yPos;     // y ���� ��ǥ	   //int yPos = 20;    // y ���� ��ǥ
	int height;   // ����		   //int Height = 20; // ����
	int spacing_H;// y ��ǥ ����    //int spacing_H = 10;   // y ��ǥ ����
	int colCount; // col ����
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