#pragma once
#include <Windows.h>
#include <math.h>


struct BMPHeader 
{
private:
	//BITMAPFILEHEADER
	const WORD bfType = 0x424D/*BM*/, bfReserved1 = 0, bfReserved2 = 0, bfOffBits = 28;
	//BITMAPINFO
	//Core ver
	DWORD bcSize = 12, bcPlanes = 1, bcBitCount = 24;

public:
	//BITMAPFILEHEADER
	DWORD bfSize;

	//BITMAPINFO
	//Core ver
	WORD  bcWidth, bcHeight;

	BMPHeader(unsigned long size)
	{
		bfSize = size + 28;
		bcWidth = bcHeight = (unsigned short)ceil(sqrt(size));
	}

	void WriteHeader(FILE* f)
	{
		fwrite(&bfType, sizeof(WORD), 1, f);
		fwrite(&bfSize, sizeof(DWORD), 1, f);
		fwrite(&bfReserved1, sizeof(WORD), 1, f);
		fwrite(&bfReserved2, sizeof(WORD), 1, f);
		fwrite(&bfOffBits, sizeof(DWORD), 1, f);

		fwrite(&bcSize, sizeof(DWORD), 1, f);
		fwrite(&bcWidth, sizeof(WORD), 1, f);
		fwrite(&bcHeight, sizeof(WORD), 1, f);
		fwrite(&bcPlanes, sizeof(WORD), 1, f);
		fwrite(&bcBitCount, sizeof(WORD), 1, f);
	}
};