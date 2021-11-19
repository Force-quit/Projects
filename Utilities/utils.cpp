#include "utils.h"
#include <string>
#include <Windows.h>
#include <vector>
#include <iostream>

void emile::flushTampon()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}

void emile::consoleBundle()
{
	emile::preventConsoleResize();
	emile::hideCursor();
	emile::disableQuickEdit();
	emile::hideScrollingBar();
}

void emile::preventConsoleResize()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void emile::hideCursor()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor{};
	lpCursor.bVisible = false;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void emile::disableQuickEdit()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void emile::hideScrollingBar()
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

std::string emile::passwordGenerator(const std::string& alphabet, const unsigned short& passwordLength)
{
	unsigned short randNb;
	std::string password{};
	for (UINT16 i = 0; i < passwordLength; ++i)
	{
		randNb = rand();
		randNb %= alphabet.size();
		password += alphabet[randNb];
	}
	return password;
}

/**************************/
/*     KEYBOARD UTILS     */
/**************************/

void emile::pressKey(const char& key)
{
	const short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	emile::pressKey(keyCode);
}

void emile::pressKey(const int& keyCode)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;

	emile::pressKey(i);
}

void emile::pressKey(INPUT& input)
{
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
}

void emile::releaseKey(const char& key)
{
	const short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	emile::releaseKey(keyCode);
}

void emile::releaseKey(const int& keyCode)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;
	emile::releaseKey(i);
}

void emile::releaseKey(INPUT& input)
{
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

void emile::fullKeyPress(const char& key)
{
	const short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	emile::fullKeyPress(keyCode);
}

void emile::fullKeyPress(const int& keyCode)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;

	emile::fullKeyPress(i);
}

void emile::fullKeyPress(INPUT& input)
{
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
	Sleep(40);
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

void emile::humanType(const std::string &toWrite)
{
	const HKL currentKBL = GetKeyboardLayout(0);
	std::vector<short> keys{};
	for (short i = 0; i < toWrite.length(); ++i)
		keys.push_back(VkKeyScanExA(toWrite.at(i), currentKBL));
	

	INPUT input{};
	input.type = INPUT_KEYBOARD;
	for (UINT16 i = 0; i < keys.size(); ++i)
	{
		input.ki.wVk = keys[i];
		emile::pressKey(input);
		Sleep(50);
	}
}

void emile::copyToClipBoard(const std::string& dataToCopy)
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

// LEFT CLICK

void emile::leftClickDown()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void emile::leftClickUp()
{
	INPUT mouseUp{};
	mouseUp.type = INPUT_MOUSE;
	mouseUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &mouseUp, sizeof(INPUT));
}

void emile::leftClick(const int& holdTime)
{
	emile::leftClickDown();
	Sleep(holdTime);
	emile::leftClickUp();
}

// RIGHT CLICK

void emile::rightClickDown()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void emile::rightClickUp()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void emile::rightClick(const int& holdTime)
{
	emile::rightClickDown();
	Sleep(holdTime);
	emile::rightClickUp();
}