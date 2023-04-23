#include <iostream>
#include "BMP_Coder.h"
#include "BMP_Header.h"
#include <string.h>

using namespace std;

enum Mode
{
	decode,
	encode
};

Mode CheckMode(char* inp);
Mode AskMode();
string AskPath();
bool AskExit();

int main(char argc, char* argv[])
{
	setlocale(LC_ALL, "");
	Mode mode;
	string path;
	string outPath;

	if (argc == 2)
	{
		path = argv[1];
		mode = AskMode();
	}
	else if (argc == 3)
	{
		path = argv[1];
		mode = CheckMode(argv[3]);
	}
	else
	{
		path = AskPath();
		mode = AskMode();
	}

	system("cls");
	BMPCoder* Bmp = new BMPCoder();
	bool IsExit = false;
	while (!IsExit) {
		switch (mode)
		{
		case decode:
			try
			{
				outPath = Bmp->TransformFromBMP(path);
				cout << "Decoded file path:" << outPath << endl;
			}
			catch (const char* e)
			{
				cout << e << endl;
			}
			break;
		case encode:
			try
			{
				outPath = Bmp->TransformToBMP(path);
				cout << "Encoded file path:" << outPath << endl;
			}
			catch(const char* e)
			{
				cout << e << endl;
			}
			break;
		default:
			break;
		}
		IsExit = AskExit();
		if (!IsExit)
		{
			path = AskPath();
			mode = AskMode();
		}
	}
	system("cls");
	
}

Mode CheckMode(char* inp)
{
	if (*inp == 'e' && *(inp + 1) == 'n' && *(inp + 2) == 'c')
		return encode;
	if (*inp == 'd' && *(inp + 1) == 'e' && *(inp + 2) == 'c')
		return decode;
	else
		throw "Incorrect input mode";
}

Mode AskMode()
{
	char strMode[4];
	strMode[3] = 0;

	Mode mode;
	bool successReading = false;
	while(!successReading)
	{
		try
		{
			cout << "Input mode(enc or dec):";
			cin >> strMode;
			mode = CheckMode(strMode);
		}
		catch (const char* e)
		{
			cout << e << endl;
			continue;
		}
		
		successReading = true;
	}
	return mode;
}

string AskPath()
{
	string path;
	cout << "Input path:";
	cin >> path;
	path = path.substr(path.find_first_not_of('"'), path.find_last_not_of('"')- path.find_first_not_of('"')+1);
	return path;
}

bool AskExit()
{
	string contAsk;
	bool success = false;
	while(!success)
	{
		cout << "Continue?(Y/N):";
		cin >> contAsk;
		if (contAsk == "Y" || contAsk == "y")
			return false;
		else if (contAsk == "N" || contAsk == "n")
			return true;
		cout << "Incorrect input" << endl;
	}
}