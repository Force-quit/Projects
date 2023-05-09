#include "utils.h"
#include <string>
#include <Windows.h>
#include <vector>
#include <filesystem>
#include <iostream>

void emile::flushTampon()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}

void emile::Console::consoleBundle()
{
	emile::Console::preventConsoleResize();
	emile::Console::hideCursor();
	emile::Console::disableQuickEdit();
	emile::Console::hideScrollingBar();
}

void emile::Console::preventConsoleResize()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void emile::Console::hideCursor()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor{};
	lpCursor.bVisible = false;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void emile::Console::disableQuickEdit()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void emile::Console::hideScrollingBar()
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

/**************************/
/*     KEYBOARD UTILS     */
/**************************/

void emile::pressKey(const char key)
{
	const short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	emile::pressKey(keyCode);
}

void emile::pressKey(const int keyCode)
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

void emile::releaseKey(const char key)
{
	const short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	emile::releaseKey(keyCode);
}

void emile::releaseKey(const int keyCode)
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

void emile::fullKeyPress(const char key, unsigned int pressDuration)
{
	const short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	emile::fullKeyPress(keyCode, pressDuration);
}

void emile::fullKeyPress(const int keyCode, unsigned int pressDuration)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;
	emile::fullKeyPress(i, pressDuration);
}

void emile::fullKeyPress(INPUT& input, unsigned int pressDuration)
{
	emile::pressKey(input);
	Sleep(pressDuration);
	emile::releaseKey(input);
}

void emile::ctrlV()
{
	const short NB_INPUTS = 4;

	INPUT inputs[NB_INPUTS]{};
	
	for (INPUT& i : inputs)
		i.type = INPUT_KEYBOARD;

	inputs[0].ki.wVk = VK_CONTROL;
	inputs[1].ki.wVk = 0x56;

	inputs[2].ki.wVk = 0x56;
	inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

	inputs[3].ki.wVk = VK_CONTROL;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(NB_INPUTS, inputs, sizeof(INPUT));
}

void emile::winR()
{
	const short NB_INPUTS = 4;

	INPUT inputs[NB_INPUTS]{};

	for (INPUT& i : inputs)
		i.type = INPUT_KEYBOARD;

	inputs[0].ki.wVk = VK_LWIN;
	inputs[1].ki.wVk = 0x52;

	inputs[2].ki.wVk = 0x52;
	inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

	inputs[3].ki.wVk = VK_LWIN;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(NB_INPUTS, inputs, sizeof(INPUT));
}

void emile::humanType(const wchar_t* toWrite, size_t sizeToWrite, int keyPressInterval)
{
	INPUT ip{};
	ip.type = INPUT_KEYBOARD;

	for (size_t i{}; i < sizeToWrite; ++i)
	{
		ip.ki.dwFlags = KEYEVENTF_UNICODE;
		ip.ki.wScan = toWrite[i];
		SendInput(1, &ip, sizeof(INPUT));

		Sleep(10);

		ip.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(keyPressInterval);
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

void emile::waitForKeyPress(short vKey)
{
	bool keyDown{};
	while (true)
	{
		if (GetAsyncKeyState(vKey))
			keyDown = true;
		else if (keyDown)
			break;
		Sleep(1);
	}
}

bool emile::ensureFolderExists(const std::string& dirName)
{
	bool folderExists = emile::folderExists(dirName);
	if (!folderExists)
		std::filesystem::create_directory(dirName);
	return folderExists;
}

bool emile::folderExists(const std::string& dirName) 
{
	return std::filesystem::is_directory(dirName);
}