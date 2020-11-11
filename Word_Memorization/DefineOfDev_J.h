#pragma once

#include <iostream>
#include <tchar.h>
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

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
struct DuNode
{
	unsigned char node;
};

struct TButtonRect
{
	int xPos;     // x 시작 좌표    //int xPos = 20;     // x 시작 좌표
	int width;    // 폭 사이즈	   //int width = 100;   // 폭 사이즈
	int spacing_W;// x 좌표 간격	   //int spacing_W = 5; // x 좌표 간격
	int colCount; // col 갯수

	int yPos;     // y 시작 좌표	   //int yPos = 20;    // y 시작 좌표
	int height;   // 높이		   //int Height = 20; // 높이
	int spacing_H;// y 좌표 간격    //int spacing_H = 10;   // y 좌표 간격
	int rowCount; // row 갯수

	std::vector<RECT> r;	
};
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

struct TCaption
{	
	// Train Caption.
	std::map<int, std::wstring> trainBTN_Caption{ {0, L"aDTC"}, {1, L"aMC1"}, {2, L"aMC2"}, {3, L"aMCI"}, 
												  {4, L"bMCI"}, {5, L"bMC2"}, {6, L"bMC1"}, {7, L"bDTC"} };
	// Main Screen Button Caption.
	std::map<int, std::wstring> srcBTN_Caption{ {0, L"Protocol"}, {1, L"HeartBit"}, {2, L"DU Default"}, {3, L"MyNode"}, {4, L"SetMVB"} };
	// HeartBit Screen Button Caption.
	std::map<int, std::wstring> HB_BTN_Caption{ // *의 의미는 사용하지 않는 버튼이라는 의미이다. 
		// VAC
		{ 0, L"VAC1"}, { 1, L"VAC3"}, { 2, L"VAC1"}, { 3, L"VAC3"}, { 4, L"VAC3"}, { 5, L"VAC1"}, { 6, L"VAC3"}, { 7, L"VAC1"}, 
		{ 8, L"VAC2"}, { 9, L"VAC4"}, {10, L"VAC2"}, {11, L"VAC4"}, {12, L"VAC4"}, {13, L"VAC2"}, {14, L"VAC4"}, {15, L"VAC2"},
		// DCU
		{16, L"LDCU1"}, {17, L"LDCU2"}, {18, L"LDCU1"}, {19, L"LDCU2"}, {20, L"LDCU2"}, {21, L"LDCU1"}, {22, L"LDCU2"}, {23, L"LDCU1"},
		{24, L"RDCU1"}, {25, L"RDCU2"}, {26, L"RDCU1"}, {27, L"RDCU2"}, {28, L"RDCU2"}, {29, L"RDCU1"}, {30, L"RDCU2"}, {31, L"RDCU1"},
		// ECU
		{32, L"ECU1"}, {33, L"ECU3"}, {34, L"ECU1"}, {35, L"ECU3"}, {36, L"ECU3"}, {37, L"ECU1"}, {38, L"ECU3"}, {39, L"ECU1"},
		{40, L"ECU2"}, {41, L"ECU4"}, {42, L"ECU2"}, {43, L"ECU4"}, {44, L"ECU4"}, {45, L"ECU2"}, {46, L"ECU4"}, {47, L"ECU2"},
		// VVVF
		{48, L"*"}, {49, L"VVVF3"}, {50, L"VVVF1"}, {51, L"VVVF3"}, {52, L"VVVF3"}, {53, L"VVVF1"}, {54, L"VVVF3"}, {55, L"*"},
		{56, L"*"}, {57, L"VVVF4"}, {58, L"VVVF2"}, {59, L"VVVF4"}, {60, L"VVVF4"}, {61, L"VVVF2"}, {62, L"VVVF4"}, {63, L"*"},
		// AAU
		{64, L"AAU"}, {65, L"*"}, {66, L"*"}, {67, L"*"}, {68, L"*"}, {69, L"*"}, {70, L"*"}, {71, L"AAU"},
		// CCTV
		{72, L"CCTV"}, {73, L"*"}, {74, L"*"}, {75, L"*"}, {76, L"*"}, {77, L"*"}, {78, L"*"}, {79, L"CCTV"},
		// FDU
		{80, L"FDU"}, {81, L"*"}, {82, L"*"}, {83, L"*"}, {84, L"*"}, {85, L"*"}, {86, L"*"}, {87, L"FDU"},
		// APU
		{88, L"APU1"}, {89, L"*"}, {90, L"*"}, {91, L"*"}, {92, L"*"}, {93, L"*"}, {94, L"*"}, {95, L"APU1"},
		{96, L"APU2"}, {97, L"*"}, {98, L"*"}, {99, L"*"}, {100, L"*"}, {101, L"*"}, {102, L"*"}, {103, L"APU2"},
		// RADIO
		{104, L"RADIO"}, {105, L"*"}, {106, L"*"}, {107, L"*"}, {108, L"*"}, {109, L"*"}, {110, L"*"}, {111, L"RADIO"},
		// ATC
		{112, L"ATC"}, {113, L"*"}, {114, L"*"}, {115, L"*"}, {116, L"*"}, {117, L"*"}, {118, L"*"}, {119, L"ATC"},
		// EVR
		{120, L"EVR"}, {121, L"*"}, {122, L"*"}, {123, L"*"}, {124, L"*"}, {125, L"*"}, {126, L"*"}, {127, L"EVR"},
		// BC
		{128, L"*"}, {129, L"BC1"}, {130, L"BC2"}, {131, L"*"}, {132, L"*"}, {133, L"BC2"}, {134, L"BC1"}, {135, L"*"}
	};
};

struct TMVB_Addr_Info
{
	//today-del
	//WORD port[120]; // myNode 총 갯수가 120개라서 배열의 크기를 120으로 잡음.

	std::map<int, int> mvb_addr{ // *의 의미는 사용하지 않는 버튼이라는 의미이다. 
		// VAC
		{ 00, 0x0B0}, { 01, 0x0F0}, { 02, 0x0B0}, { 03, 0x0F0}, { 04, 0x0F0}, { 05, 0x0B0}, { 06, 0x0F0}, { 07, 0x0B0},
		{ 10, 0x0B4}, { 11, 0x0F4}, { 12, 0x0B4}, { 13, 0x0F4}, { 14, 0x0F4}, { 15, 0x0B4}, { 16, 0x0F4}, { 17, 0x0B4},
		// DCU		    			  			    			  			    			  			    
		{ 20, 0x0D0}, { 21, 0x0E0}, { 22, 0x0D0}, { 23, 0x0E0}, { 24, 0x0D0}, { 25, 0x0D0}, { 26, 0x0E0}, { 27, 0x0D0},
		{ 30, 0x0D4}, { 31, 0x0E4}, { 32, 0x0D4}, { 33, 0x0E4}, { 34, 0x0E4}, { 35, 0x0D4}, { 36, 0x0E4}, { 37, 0x0D4},
		// ECU		    			  			    			  			    			  			    
		{ 40, 0x010}, { 41, 0x030}, { 42, 0x010}, { 43, 0x030}, { 44, 0x030}, { 45, 0x010}, { 46, 0x030}, { 47, 0x010},
		{ 50, 0x020}, { 51, 0x040}, { 52, 0x020}, { 53, 0x040}, { 54, 0x040}, { 55, 0x020}, { 56, 0x040}, { 57, 0x020},
		// VVVF		    			  			    			  			    			  
					  { 61, 0x070}, { 62, 0x050}, { 63, 0x070}, { 64, 0x070}, { 65, 0x050}, { 66, 0x070},
					  { 71, 0x080}, { 72, 0x060}, { 73, 0x080}, { 74, 0x080}, { 75, 0x060}, { 76, 0x080},
		// AAU		  
		{ 80, 0x110}, 																					  { 87, 0x110},
		// CCTV
		{ 90, 0x114},																					  { 97, 0x114},
		// FDU
		{100, 0x0C0},																					  {107, 0x0C0},
		// APU
		{110, 0x090},																					  {117, 0x090},
		{120, 0x094},																					  {127, 0x094},
		// RADIO																						  
		{130, 0x190},																					  {137, 0x190},
		// ATC																							  
		{140, 0x154},																					  {147, 0x154},
		// EVR																							  
		{150, 0x180},																					  {157, 0x180},
		// BC	
					  {161, 0x09C}, {162, 0x09C},							  {165, 0x09C}, {166, 0x09C}				
	};

};
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 120의 의미는 myNode의 총 갯수를 의미 한다. 계산 법은 다음과 같다.
// int dataSize = sizeof(p_ExcelLib->mvb_Addr) / sizeof(WORD);	
int binarySearch(WORD *data, int size, WORD d);
bool IsBitCheck16(WORD a_Target, WORD a_BitPos);
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
CString GetTextFormExcel(int a_Row, int a_Col, libxl::Sheet *ap_Excel);
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DbgLog(LPCSTR ap_str, ...);
void DbgLogW(LPCWSTR ap_str, ...);
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+