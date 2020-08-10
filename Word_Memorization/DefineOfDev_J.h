#pragma once

#define RCLICK_RGB   RGB(0, 255, 128)
#define LDCLICK_RGB  RGB(255, 128, 255) 
#define WHITE_RGB	 RGB(255, 255, 255)

#define DEf_EVEN_WORD RGB(255, 255, 204)

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