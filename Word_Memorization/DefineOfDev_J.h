#pragma once

#include <iostream>
#include <tchar.h>
#include "libxl.h"

#include <vector>
#include <map>

#define RCLICK_RGB		RGB(0, 255, 128) // bit
#define LDCLICK_RGB		RGB(255, 255, 204) 
#define WHITE_RGB		RGB(255, 255, 255)

#define LIGHTYELLOW_COLOR		RGB(255, 255, 204) // 2bit ~ 7bit
#define ORANGE_COLOR			RGB(255, 200, 100) // Byte or Word
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
	
	// HeartBit 화면과 Protocol 화면에 같이 사용됨.
	// HeartBit Screen Button Caption. & Protocol Screen Button Caption.
	std::map<int, std::wstring> HB_BTN_Caption{ // *의 의미는 사용하지 않는 버튼이라는 의미이다. 
		// CCU & IO & VCU
		{ 0, L"CCU1"}, { 1, L"IO-M1"}, { 2, L"IO-M1"}, { 3, L"VCU1"}, { 4, L"VCU1"}, { 5, L"IO-M1"}, { 6, L"IO-M1"}, { 7, L"CCU1"},
		{10, L"CCU2"}, {11, L"IO-M2"}, {12, L"IO-M2"}, {13, L"VCU2"}, {14, L"VCU2"}, {15, L"IO-M2"}, {16, L"IO-M2"}, {17, L"CCU2"},
		// VAC
		{20, L"VAC1"}, {21, L"VAC3"}, {22, L"VAC1"}, {23, L"VAC3"}, {24, L"VAC3"}, {25, L"VAC1"}, {26, L"VAC3"}, {27, L"VAC1"}, 
		{30, L"VAC2"}, {31, L"VAC4"}, {32, L"VAC2"}, {33, L"VAC4"}, {34, L"VAC4"}, {35, L"VAC2"}, {36, L"VAC4"}, {37, L"VAC2"},
		// DCU
		{40, L"LDCU1"}, {41, L"LDCU2"}, {42, L"LDCU1"}, {43, L"LDCU2"}, {44, L"LDCU2"}, {45, L"LDCU1"}, {46, L"LDCU2"}, {47, L"LDCU1"},
		{50, L"RDCU1"}, {51, L"RDCU2"}, {52, L"RDCU1"}, {53, L"RDCU2"}, {54, L"RDCU2"}, {55, L"RDCU1"}, {56, L"RDCU2"}, {57, L"RDCU1"},
		// ECU
		{60, L"ECU1"}, {61, L"ECU3"}, {62, L"ECU1"}, {63, L"ECU3"}, {64, L"ECU3"}, {65, L"ECU1"}, {66, L"ECU3"}, {67, L"ECU1"},
		{70, L"ECU2"}, {71, L"ECU4"}, {72, L"ECU2"}, {73, L"ECU4"}, {74, L"ECU4"}, {75, L"ECU2"}, {76, L"ECU4"}, {77, L"ECU2"},
		// VVVF
		{80, L"*"}, {81, L"VVVF3"}, {82, L"VVVF1"}, {83, L"VVVF3"}, {84, L"VVVF3"}, {85, L"VVVF1"}, {86, L"VVVF3"}, {87, L"*"},
		{90, L"*"}, {91, L"VVVF4"}, {92, L"VVVF2"}, {93, L"VVVF4"}, {94, L"VVVF4"}, {95, L"VVVF2"}, {96, L"VVVF4"}, {97, L"*"},
		// AAU
		{100, L"AAU"}, {101, L"*"}, {102, L"*"}, {103, L"*"}, {104, L"*"}, {105, L"*"}, {106, L"*"}, {107, L"AAU"},
		// CCTV
		{110, L"CCTV"}, {111, L"*"}, {112, L"*"}, {113, L"*"}, {114, L"*"}, {115, L"*"}, {116, L"*"}, {117, L"CCTV"},
		// FDU
		{120, L"FDU"}, {121, L"*"}, {122, L"*"}, {123, L"*"}, {124, L"*"}, {125, L"*"}, {126, L"*"}, {127, L"FDU"},
		// APU
		{130, L"APU1"}, {131, L"*"}, {132, L"*"}, {133, L"*"}, {134, L"*"}, {135, L"*"}, {136, L"*"}, {137, L"APU1"},
		{140, L"APU2"}, {141, L"*"}, {142, L"*"}, {143, L"*"}, {144, L"*"}, {145, L"*"}, {146, L"*"}, {147, L"APU2"},
		// RADIO
		{150, L"RADIO"}, {151, L"*"}, {152, L"*"}, {153, L"*"}, {154, L"*"}, {155, L"*"}, {156, L"*"}, {157, L"RADIO"},
		// ATC
		{160, L"ATC1"}, {161, L"*"}, {162, L"*"}, {163, L"*"}, {164, L"*"}, {165, L"*"}, {166, L"*"}, {167, L"ATC1"},
		{170, L"ATC2"}, {171, L"*"}, {172, L"*"}, {173, L"*"}, {174, L"*"}, {175, L"*"}, {176, L"*"}, {177, L"ATC2"},
		// EVR
		{180, L"EVR"}, {181, L"*"}, {182, L"*"}, {183, L"*"}, {184, L"*"}, {185, L"*"}, {186, L"*"}, {187, L"EVR"},
		// BC
		{190, L"*"}, {191, L"BC1"}, {192, L"BC2"}, {193, L"*"}, {194, L"*"}, {195, L"BC2"}, {196, L"BC1"}, {197, L"*"}
	};
};

struct TMVB_Addr_Info
{
	//today-del
	//WORD port[120]; // myNode 총 갯수가 120개라서 배열의 크기를 120으로 잡음.
	std::map<int, int> used_on_HeartBit{ // *의 의미는 사용하지 않는 버튼이라는 의미이다. 
		// CCU & IO & VCU
		{ 00, 0x120}, { 01, 0x140}, { 02, 0x140}, { 03, 0x120}, { 04, 0x120}, { 05, 0x140}, { 06, 0x140}, { 07, 0x120},
		{ 10, 0x130}, { 11, 0x144}, { 12, 0x144}, { 13, 0x130}, { 14, 0x130}, { 15, 0x144}, { 16, 0x144}, { 17, 0x130},
		// VAC
		{ 20, 0x0B0}, { 21, 0x0F0}, { 22, 0x0B0}, { 23, 0x0F0}, { 24, 0x0F0}, { 25, 0x0B0}, { 26, 0x0F0}, { 27, 0x0B0},
		{ 30, 0x0B4}, { 31, 0x0F4}, { 32, 0x0B4}, { 33, 0x0F4}, { 34, 0x0F4}, { 35, 0x0B4}, { 36, 0x0F4}, { 37, 0x0B4},
		// DCU		    			  			    			  		    	  			   
		{ 40, 0x0D0}, { 41, 0x0E0}, { 42, 0x0D0}, { 43, 0x0E0}, { 44, 0x0E0}, { 45, 0x0D0}, { 46, 0x0E0}, { 47, 0x0D0},
		{ 50, 0x0D4}, { 51, 0x0E4}, { 52, 0x0D4}, { 53, 0x0E4}, { 54, 0x0E4}, { 55, 0x0D4}, { 56, 0x0E4}, { 57, 0x0D4},
		// ECU		    			  			    			  		    	  			   
		{ 60, 0x010}, { 61, 0x030}, { 62, 0x010}, { 63, 0x030}, { 64, 0x030}, { 65, 0x010}, { 66, 0x030}, { 67, 0x010},
		{ 70, 0x020}, { 71, 0x040}, { 72, 0x020}, { 73, 0x040}, { 74, 0x040}, { 75, 0x020}, { 76, 0x040}, { 77, 0x020},
					  // VVVF		    			  			    			  			    			  
					  { 81, 0x070}, { 82, 0x050}, { 83, 0x070}, { 84, 0x070}, { 85, 0x050}, { 86, 0x070},
					  { 91, 0x080}, { 92, 0x060}, { 93, 0x080}, { 94, 0x080}, { 95, 0x060}, { 96, 0x080},
		// AAU		  
		{100, 0x110}, 																					  {107, 0x110},
		// CCTV
		{110, 0x114},																					  {117, 0x114},
		// FDU
		{120, 0x0C0},																					  {127, 0x0C0},
		// APU
		{130, 0x090},																					  {137, 0x090},
		{140, 0x094},																					  {147, 0x094},
		// RADIO																						  
		{150, 0x190},																					  {157, 0x190},
		// ATC																							  
		{160, 0x154},																					  {167, 0x154},		
		{170, 0x168},																					  {177, 0x168},
		// EVR																							  
		{180, 0x180},																					  {187, 0x180},
					  // BC	
					  {191, 0x09C}, {192, 0x09C},							  {195, 0x09C}, {196, 0x09C}				
	};

	// 엑셀 추가 5
	std::map<int, int> used_on_Protocol{ // *의 의미는 사용하지 않는 버튼이라는 의미이다. 
		// SDR port!!!!
		// CCU & IO & VCU
		{ 00, 0x120}, { 01, 0x140}, { 02, 0x140}, { 03, 0x120}, { 04, 0x120}, { 05, 0x140}, { 06, 0x140}, { 07, 0x120},
		{ 10, 0x130}, { 11, 0x144}, { 12, 0x144}, { 13, 0x130}, { 14, 0x130}, { 15, 0x144}, { 16, 0x144}, { 17, 0x130},
		// VAC
		{ 20, 0x0B8}, { 21, 0x0BC}, { 22, 0x0B8}, { 23, 0x0BC}, { 24, 0x0BC}, { 25, 0x0B8}, { 26, 0x0BC}, { 27, 0x0B8},
		{ 30, 0x0B8}, { 31, 0x0BC}, { 32, 0x0B8}, { 33, 0x0BC}, { 34, 0x0BC}, { 35, 0x0B8}, { 36, 0x0BC}, { 37, 0x0B8},
		// DCU		    		  		    		 			   			  		    
		{ 40, 0x0FC}, { 41, 0x0FC}, { 42, 0x0FC}, { 43, 0x0FC}, { 44, 0x0FC}, { 45, 0x0FC}, { 46, 0x0FC}, { 47, 0x0FC},
		{ 50, 0x0FC}, { 51, 0x0FC}, { 52, 0x0FC}, { 53, 0x0FC}, { 54, 0x0FC}, { 55, 0x0FC}, { 56, 0x0FC}, { 57, 0x0FC},
		// ECU		    		  		    		 			   			  		    
		{ 60, 0x028}, { 61, 0x028}, { 62, 0x028}, { 63, 0x028}, { 64, 0x028}, { 65, 0x028}, { 66, 0x028}, { 67, 0x028},
		{ 70, 0x028}, { 71, 0x028}, { 72, 0x028}, { 73, 0x028}, { 74, 0x028}, { 75, 0x028}, { 76, 0x028}, { 77, 0x028},
					  // VVVF		    			  			    			  			    			  
					  { 81, 0x058}, { 82, 0x058}, { 83, 0x058}, { 84, 0x058}, { 85, 0x058}, { 86, 0x058},
					  { 91, 0x058}, { 92, 0x058}, { 93, 0x058}, { 94, 0x058}, { 95, 0x058}, { 96, 0x058}
		//// AAU		  
		//{ 80, 0x110}, 																				  { 87, 0x110},
		//// CCTV
		//{ 90, 0x114},																					  { 97, 0x114},
		//// FDU
		//{100, 0x0C0},																					  {107, 0x0C0},
		//// APU
		//{110, 0x090},																					  {117, 0x090},
		//{120, 0x094},																					  {127, 0x094},
		//// RADIO																						  
		//{130, 0x190},																					  {137, 0x190},
		//// ATC																							  
		//{140, 0x154},																					  {147, 0x154},
		//{140, 0x168},																					  {147, 0x168},
		//// EVR																							  
		//{150, 0x180},																					  {157, 0x180},
		            // BC	
		//			{161, 0x09C}, {162, 0x09C},							  {165, 0x09C}, {166, 0x09C}
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
// HeartBit screen Button
void Set_HeartBit_OnOffcolor(BYTE a_status, wchar_t *ap_wstr, RECT btnRect, CDC *ap_dc);
// Protocol screen Button
void Set_Protocol_OnOffcolor(BYTE a_status, wchar_t *ap_str, RECT btnRect, CDC *ap_dc);
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+