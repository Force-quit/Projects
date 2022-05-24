/*
TODO:

- Make GetAverage() take in a percentage or decimal value
- Make GetColor() take in a file or image object instead of a path string
- Make the title dynamic with the input file

*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>
#include <Windows.h>
#include <WinUser.h>
#include <inttypes.h>

#define inline __inline

extern "C" {
#include "stb_image.h"

/*
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavfilter/avfilter.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
*/
}

using namespace std;
using namespace std::chrono;
using matrix = vector<vector<int>>;

/*
Searches for an open Notepad.exe instance and creates one if
none is found, then change its title to the parameter given
and returns the handle to the edit window.
*/
HWND GetNotePad(string);

/*
Returns a matrix or 2-dimentional integer vector with values
between 0 and 255 representing the brightness value of each
pixel of an image given as the parameter.
*/
matrix GetColor(string);

/*
Averages rectangular portions of a matrix while taking into
account the height to width ratio of the Consolas police
and returns a smaller matrix of colors. The first parameter
is a matrix of every pixel of an image; the second parameter
is the ratio of the output compared to the input: 0.5 will
return a matrix half the size of the original one.
*/
matrix GetAverage(matrix, float);

/*
Builds a string that can be sent to other functions with the
ascii character that most closely matches the brightness for
each pixel in a given matrix. The first parameter is a matrix
of colors that represents an image; the second parameter is a
boolean that controls whether to use 70 different characters
in the string for more possible colors instead of 10 for
sharper outputs.
*/
string GetText(matrix, bool);

/*
Sends a string to the edit window of a Notepad.exe instance.
The first parameter is a handle to the edit window; the
second parameter is the string to be sent.
*/
void SendToNotePad (HWND, string);


int main ()
{	
	string inputPath;
	char full;
	bool HD;
	float ratio;
	cout << "Directory: ";
	cin >> inputPath;
	cout << "(Y/N) Use more ascii (might be more blurry): ";
	do
	{
		cin >> full;
		full = toupper(full);
	} while (full != 'Y' && full != 'N');
	if (full == 'Y')
		HD = 1;
	else
		HD = 0;
	cout << "Ratio of the resolution in characters over the original resolution: ";
	cin >> ratio;

	//Clear the screen
	DWORD dummy;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), 32, 0xFFFF, {}, &dummy);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });

	HWND hwnd = GetNotePad("Playing - ");



	for (int i = 4; i > 0; --i)
	{
		SendToNotePad(hwnd, to_string(i));
		Sleep(1000);
	}

	int iter = 0;
	//for (auto& p : filesystem::directory_iterator("Y:\\C++\\BadApple\\frames"))
	for (auto& p : filesystem::directory_iterator(inputPath))
	{
		auto begin = high_resolution_clock::now();

		string path = p.path().string();
		matrix color = GetColor(path);
		matrix average = GetAverage(color, ratio);
		string text = GetText(average, HD);
		SendToNotePad(hwnd, text);
		cout << iter++ << ' ';

		auto end = high_resolution_clock::now();
		double framerate = 1.0 / 30.0 - (end - begin).count() / 1e9;
		auto spinStart = high_resolution_clock::now();
		while ((high_resolution_clock::now() - spinStart).count() / 1e9 < framerate);
	}
	return 0;
}


HWND GetNotePad(const string title)
{
	HWND editHwnd = 0;
	HWND mainHwnd;
	//ShellExecuteA(0, "open", "notepad.exe", NULL, NULL, 0);	//creates hidden window for testing
	while (1) {
		mainHwnd = FindWindowA("Notepad", NULL);
		if (mainHwnd != NULL)
		{
			cout << "Found open notepad window...\n";
			if (IsWindowVisible(mainHwnd))
			{
				cout << "Checking if the window is valid...\n";
				char* title = new char[11];
				GetWindowTextA(mainHwnd, title, 11);
				editHwnd = FindWindowEx(mainHwnd, NULL, L"Edit", NULL);
				if (string(title) == "Playing - ")
				{
					delete[] title;
					cout << "Window was created by this program, reusing it...\n";
					break;
				}
				else if (GetWindowTextLength(editHwnd) == 0)
				{
					delete[] title;
					cout << "Window is empty, using it...\n";
					break;
				}
				else
				{
					delete[] title;
					cout << "Window is invalid, opening a new notepad window...\n";
					break;
				}
			}
			else
			{
				cout << "Hidden window found, terminating it...\n";
				SendMessage(mainHwnd, WM_CLOSE, NULL, NULL);
				continue;
			}
		}
		else
		{
			cout << "No valid window found, creating a new one...\n";
			break;
		}
	}

	if (editHwnd != 0)
	{
		SetWindowTextA(mainHwnd, title.c_str());
		return editHwnd;
	}


	STARTUPINFOW startupInfo;
	PROCESS_INFORMATION procInfo;

	ZeroMemory(&startupInfo, sizeof(startupInfo));
	ZeroMemory(&procInfo, sizeof(procInfo));

	wchar_t NOTEPATH[] = L"C:/Windows/System32/Notepad.exe";

	CreateProcess(NOTEPATH,
		NULL,
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
		NULL,
		NULL,
		&startupInfo,
		&procInfo
	);

	WaitForInputIdle(procInfo.hProcess, 20000);

	mainHwnd = FindWindowW(L"Notepad", NULL);				//The newly created window should be top level
	editHwnd = FindWindowEx(mainHwnd, NULL, L"Edit", NULL);

	CloseHandle(procInfo.hProcess);
	CloseHandle(procInfo.hThread);

	SetWindowTextA(mainHwnd, title.c_str());
	return editHwnd;
}


void SendToNotePad (HWND hwnd, string msg)
{
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, msg.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wchars_num];
	MultiByteToWideChar(CP_UTF8, 0, msg.c_str(), -1, wstr, wchars_num);

	SendMessage(hwnd, WM_SETTEXT, NULL, (LPARAM)wstr);

	delete[] wstr;
	return;
}


string GetText(matrix colors, const bool FULL)
{

	string text = "";
	const int valuesFull = 71;
	const char asciiFull[valuesFull] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B$@";
	const int valuesSmall = 11;
	char asciiSmall[valuesSmall] = " .:-=+*#%@";
	int a;

	for (auto x : colors)
	{
		for (auto y : x)
		{
			a = (255 - y) * ((FULL == 1 ? valuesFull : valuesSmall) - 1) / 256;
			text += (FULL == 1 ? asciiFull : asciiSmall)[a];
		}
		text += '\n';
	}
	
	return text;
}


matrix GetAverage(matrix Pixels, const float xside)
{
	const float fontratio = 0.5;			//2 pixels height for 1 pixel width
	int height = Pixels.size(), width = Pixels[0].size();
	const int yside = xside / fontratio;
	//const int yside = 1.0 / ratio;
	//const int xside = 1.0 / ratio * fontratio;
	matrix average(Pixels.size() / (yside > 0 ? yside : 1), vector<int>(Pixels[0].size() / (xside > 0 ? xside : 1), 0));
	int ix = 0, iy = 0;

	for (int y = 0; y < Pixels.size() - yside + 1; y += yside)
	{
		for (int x = 0; x < Pixels[0].size() - xside + 1; x += xside)
		{
			int sum = 0;
			for (int ys = y; ys < y + yside; ++ys)
				for (int xs = x; xs < x + xside; ++xs)
					sum += Pixels[ys][xs];
			average[iy][ix] = sum / (xside * yside);
			ix += 1;
		}
		ix = 0;
		iy += 1;
	}
	return average;
}


matrix GetColor(string path)
{
	int x, y, n;
	unsigned char* data = stbi_load(path.c_str(), &x, &y, &n, 1);

	//matrix pixels(ROWS, vector<int>(COLUMNS));
	matrix pixels (y, vector<int> (x));

	int p = 0;
	if (data != nullptr && x > 0 && y > 0)
	{
		for (int yp = 0; yp < y; ++yp)
		{
			for (int xp = 0; xp < x; ++xp)
			{
				int color = static_cast<int>(data[p]);
				pixels[yp][xp] = color;
				++p;
			}
		}
	}
	else cout << "failed";
	stbi_image_free(data);

	return pixels;
}