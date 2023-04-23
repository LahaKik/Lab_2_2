#pragma once
#include <Windows.h>
#include <math.h>


struct BMPHeader 
{
	//BITMAPFILEHEADER
	const WORD bfType = 0x4D42/*BM*/, bfReserved1 = 0, bfReserved2 = 0;
	DWORD bfOffBits = 54;
	//BITMAPINFO
	//Ver3
	const DWORD biSize = 40, biPlanes = 1, biBitCount = 24, biClrUsed = 0, biClrImportant = 0, biCompression = 0;


	//BITMAPFILEHEADER
	DWORD bfSize;

	//BITMAPINFO
	//Ver3
	LONG biHeight, biWidth, biSizeImage = 0, biXPelsPerMeter = 1181, biYPelsPerMeter = 1181;

	BMPHeader(){}
	BMPHeader(unsigned long size)
	{
		bfSize = size + 54;
		biSizeImage = size;
		biWidth = biHeight = (long)ceil(sqrt(size));
	}

	void WriteHeaderV3(FILE* f)
	{
		fwrite(&bfType, sizeof(WORD), 1, f);
		fwrite(&bfSize, sizeof(DWORD), 1, f);
		fwrite(&bfReserved1, sizeof(WORD), 1, f);
		fwrite(&bfReserved2, sizeof(WORD), 1, f);
		fwrite(&bfOffBits, sizeof(DWORD), 1, f);

		fwrite(&biSize, sizeof(DWORD), 1, f);
		fwrite(&biWidth, sizeof(LONG), 1, f);
		fwrite(&biHeight, sizeof(LONG), 1, f);
		fwrite(&biPlanes, sizeof(WORD), 1, f);
		fwrite(&biBitCount, sizeof(WORD), 1, f);
		fwrite(&biCompression, sizeof(DWORD), 1, f);
		fwrite(&biSizeImage, sizeof(DWORD), 1, f);
		fwrite(&biXPelsPerMeter, sizeof(LONG), 1, f);
		fwrite(&biYPelsPerMeter, sizeof(LONG), 1, f);
		fwrite(&biClrUsed, sizeof(DWORD), 1, f);
		fwrite(&biClrImportant, sizeof(DWORD), 1, f);
	}

	void ReadHeaderV3(FILE* f)
	{
		WORD Type, Reserved1, Reserved2, Planes, BitCount;
		DWORD Size, OffBits, biSize, Compression, SizeImage, ClrUsed, ClrImportant;
		LONG Width, Height, XPelsPerMeter, YPelsPerMeter;

		fread(&Type, sizeof(WORD), 1, f);
		fread(&Size, sizeof(DWORD), 1, f);
		fread(&Reserved1, sizeof(WORD), 1, f);
		fread(&Reserved2, sizeof(WORD), 1, f);
		fread(&OffBits, sizeof(DWORD), 1, f);

		fread(&biSize, sizeof(DWORD), 1, f);
		fread(&Width, sizeof(LONG), 1, f);
		fread(&Height, sizeof(LONG), 1, f);
		fread(&Planes, sizeof(WORD), 1, f);
		fread(&BitCount, sizeof(WORD), 1, f);
		fread(&Compression, sizeof(DWORD), 1, f);
		fread(&SizeImage, sizeof(DWORD), 1, f);
		fread(&XPelsPerMeter, sizeof(LONG), 1, f);
		fread(&YPelsPerMeter, sizeof(LONG), 1, f);
		fread(&ClrUsed, sizeof(DWORD), 1, f);
		fread(&ClrImportant, sizeof(DWORD), 1, f);

		if ((Type == 0x4D42 || Type == 0x424D) && (Reserved1 == bfReserved1) && (Reserved2 == bfReserved2)
		    && (biSize == this->biSize)
			&& (Planes == biPlanes) && (Compression == biCompression)
			&& (ClrUsed == biClrUsed) && (ClrImportant == biClrImportant))
		{
			biWidth = Width;
			biHeight = Height;
			biSizeImage = SizeImage;
		}
	}
};