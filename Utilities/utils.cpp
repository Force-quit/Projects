#include "utils.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <vector>

void consoleBundle()
{
	preventConsoleResize();
	hideCursor();
	disableQuickEdit();
	hideScrollingBar();
}

void preventConsoleResize()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void hideCursor()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor{};
	lpCursor.bVisible = false;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void disableQuickEdit()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void hideScrollingBar()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

void pressKey(INPUT& input)
{
	SendInput(1, &input, sizeof(INPUT));
	Sleep(40);
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	input.ki.dwFlags = 0;
}

void humanType(const std::string &toWrite)
{
	HKL currentKBL = GetKeyboardLayout(0);
	std::vector<short> keys{};
	for (short i = 0; i < toWrite.length(); ++i)
		keys.push_back(VkKeyScanExA(toWrite.at(i), currentKBL));
	

	INPUT input{};
	input.type = INPUT_KEYBOARD;
	for (UINT16 i = 0; i < keys.size(); ++i)
	{
		input.ki.wVk = keys[i];
		pressKey(input);
		Sleep(50);
	}
}

void copyToClipBoard(const std::string& dataToCopy)
{
	if (OpenClipboard(GetActiveWindow()))
	{
		EmptyClipboard();

		HGLOBAL hGlobalAlloc = GlobalAlloc(GMEM_MOVEABLE, dataToCopy.size() + 1);

		if (!hGlobalAlloc)
			std::cout << "Failed to get a handle to the globalAlloc" << '\n';
		else
		{
			memcpy(GlobalLock(hGlobalAlloc), dataToCopy.c_str(), dataToCopy.size() + 1);
			GlobalUnlock(hGlobalAlloc);

			if (!SetClipboardData(CF_TEXT, hGlobalAlloc))
				std::cout << "Failed to copy to clipboard :(" << '\n';

			GlobalFree(hGlobalAlloc);
		}

		CloseClipboard();
	}
	else
		std::cout << "Failed to open clipboard" << '\n';
}


/***********************/
/*     MOUSE UTILS     */
/***********************/
void leftClickDown()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void leftClickUp()
{
	INPUT mouseUp{};
	mouseUp.type = INPUT_MOUSE;
	mouseUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &mouseUp, sizeof(INPUT));
}

void e_click(const int& holdTime)
{
	leftClickDown();
	Sleep(holdTime);
	leftClickUp();
}
