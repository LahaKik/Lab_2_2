#pragma once
#pragma warning(disable : 4996) 

#include <fstream>
#include <string.h>
#include "BMP_Header.h"

using namespace std;

class BMPCoder
{
private:
	unsigned long Size;
	string SourceFileExtension;
	string SourceFileName;

	unsigned long GetSize(FILE* f)//In bytes
	{
		fseek(f, 0, SEEK_END);
		unsigned long size = ftell(f);
		fseek(f, 0, SEEK_SET);
		return size;
	}

public :
	BMPCoder(){}

	~BMPCoder()
	{
		Close();
	}

	void Close()
	{
		_fcloseall();
	}

	string TransformToBMP(string path)
	{
		string NamePlusExtension = path.substr(path.rfind('\\') + 1);
		SourceFileName = NamePlusExtension.substr(0, NamePlusExtension.rfind('.'));
		SourceFileExtension = NamePlusExtension.substr(NamePlusExtension.rfind('.') + 1);

		FILE* oldF = fopen(path.c_str(), "rb");
		if (!oldF)
			throw "Incorrect path";

		Size = GetSize(oldF);
		string tpath = "C:\\Users\\hotki\\Downloads\\" + SourceFileName + ".bmp";
		FILE* newF = fopen(tpath.c_str(), "wb");
		if (!newF)
			throw "Sorry, can't create file";

		unsigned long height, width, DataForName = SourceFileName.length() + 2 * sizeof(LONG) + SourceFileExtension.length();
		width = (unsigned long)ceil(sqrt(ceil((Size / 3.0) + DataForName))) + (4 - (unsigned long)ceil(sqrt(ceil(Size / 3.0) + DataForName)) % 4) % 4;
		height = (unsigned long)ceil(Size / (width*3.0));

		unsigned char Zero = 0;

		BMPHeader header;
		header.biHeight =  height;
		header.biWidth = width;
		header.bfOffBits = 54 + SourceFileName.length() + 2 * sizeof(LONG) + SourceFileExtension.length();
		header.bfSize = height*width + header.bfOffBits;
		header.biSizeImage = Size;
		header.WriteHeaderV3(newF);
		WriteNameAndExtension(newF);

		for (unsigned long i = 0; i < height; i++)
		{
			for (unsigned long j = 1; j <= width*3; j++)
			{
				if (i * width*3 + j <= Size)
				{
					unsigned char Byte;
					fread(&Byte, 1, 1, oldF);
					fwrite(&Byte, 1, 1, newF);
				}
				else
				{
					unsigned char Zero = 0;
					fwrite(&Zero, 1, 1, newF);
				}
			}

		}
		_fcloseall();
		return tpath;
	}

	void DebugTransform()
	{
		FILE* newF = fopen("C:\\Users\\hotki\\Downloads\\TestBMP.bmp", "wb");
		unsigned long height=225, width=225;
		char Zero = 0;
		BMPHeader header = { height*width };
		unsigned char gg[25] = { 255, 255, 255 };
		header.WriteHeaderV3(newF);
		for (size_t i = 1; i <= height*width; i++)
		{
			if (i % width == 0)
				fwrite(&Zero, width % 4, 1, newF);

			for (size_t j = 0; j < 3; j++)
			{
				fwrite(&gg[j], sizeof(char), 1, newF);
			}
			
		}
		fclose(newF);
	}

	void WriteNameAndExtension(FILE* newF)
	{
		long LenName = SourceFileName.length();
		fwrite(&LenName, sizeof(long), 1, newF);
		fwrite(SourceFileName.c_str(), sizeof(char), LenName, newF);

		long LenExt = SourceFileExtension.length();
		fwrite(&LenExt, sizeof(long), 1, newF);
		fwrite(SourceFileExtension.c_str(), sizeof(char), LenExt, newF);
	}

	string TransformFromBMP(string path)
	{
		if (path.substr(path.rfind('.') + 1) != "bmp")
			throw "It's not BMP-file";
		FILE* oldF = fopen(path.c_str(), "rb");

		BMPHeader header;
		header.ReadHeaderV3(oldF);

		unsigned long DataForName;//Optional

		string newFPath = GetPathWithName(oldF, &DataForName);
		FILE* newF = fopen(newFPath.c_str(), "wb");

		for (long i = 0; i < header.biSizeImage; i++)
		{
			unsigned char Byte;
			fread(&Byte, 1, 1, oldF);
			fwrite(&Byte, 1, 1, newF);
		}

		fcloseall();
		return newFPath;
	}

	string GetPathWithName(FILE* oldF, unsigned long* DataLen)
	{
		long LenName;
		fread(&LenName, sizeof(long), 1, oldF);
		char* Name = new char[LenName + 1];
		*(Name + LenName) = 0;
		fread(Name, sizeof(char), LenName, oldF);
		string NameFile = string(Name);

		long LenExt;
		fread(&LenExt, sizeof(long), 1, oldF);
		char* Extension = new char[LenExt + 1];
		*(Extension + LenExt) = 0;
		fread(Extension, sizeof(char), LenExt, oldF);
		string ExtensionFile = string(Extension);

		string rez = "C:\\Users\\hotki\\Downloads\\" + NameFile + "(Encoded)" + "." + ExtensionFile;
		*DataLen = LenName + LenExt + 2 * sizeof(long);
		return rez;
	}
};