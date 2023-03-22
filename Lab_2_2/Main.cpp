#include <iostream>
#include "BMP_Coder.h"
#include "BMP_Header.h"
#include "UI_Writer.h"
#include <string.h>

using namespace std;

int main(char argc, char* argv[])
{
	string path = "C:\\Users\\hotki\\Downloads\\var_2376 (1).PNG";

	BMPCoder* Bmp = new BMPCoder(path, Encode);
	Bmp->DebugTransform();
	
}