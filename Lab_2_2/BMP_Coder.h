#pragma once
#pragma warning(disable : 4996) 

#include <fstream>
#include <string.h>
#include "BMP_Header.h"

using namespace std;

enum Mode
{
	Decode,
	Encode
};

enum VerBMP
{
	Core,
	Ver3,
	Ver4,
	Ver5
};

class BMPCoder
{
	Mode mode;
	VerBMP ver;
	FILE* f;
	unsigned long Size;

	unsigned long GetSize()//In bytes
	{
		fseek(f, 0, SEEK_END);
		unsigned long size = ftell(f);
		fseek(f, 0, SEEK_SET);
		return size;
	}

public :
	BMPCoder(std::string path, Mode mode, VerBMP version = Core)
	{
		this->mode = mode;
		ver = version;

		f = fopen(path.c_str(), "rb");
		Size = GetSize();

		
	}
	~BMPCoder()
	{
		Close();
	}
	void Close()
	{
		_fcloseall();
	}

	void TransformToBMP()
	{

	}

	void DebugTransform()
	{
		FILE* newF = fopen("C:\\Users\\hotki\\Downloads\\TestBMP.bmp", "wb");
		BMPHeader header = { 16 };
		unsigned char gg[4][4] = {{255, 255, 255, 255},
								  {255, 255, 255, 255},
								  {255, 255, 255, 255},
								  {255, 255, 255, 255} };
		header.WriteHeader(newF);
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				fwrite(&gg[i][j], sizeof(char), 1, newF);
			}
		}
	}
};

