#pragma once

#define RCLICK_RGB   RGB(0, 255, 128)
#define LDCLICK_RGB  RGB(255, 128, 255) 
#define WHITE_RGB	 RGB(255, 255, 255)

typedef struct DuNode
{
	unsigned char node;
}DuNode;

int binarySearch(WORD *data, int size, WORD d);

