#include "pch.h" 
#include "EUtilities.h"
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

void EUtilities::flushTampon()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}

void EUtilities::Console::consoleBundle()
{
	EUtilities::Console::preventConsoleResize();
	EUtilities::Console::hideCursor();
	EUtilities::Console::disableQuickEdit();
	EUtilities::Console::hideScrollingBar();
}

void EUtilities::Console::preventConsoleResize()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void EUtilities::Console::hideCursor()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor{};
	lpCursor.bVisible = false;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void EUtilities::Console::disableQuickEdit()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void EUtilities::Console::hideScrollingBar()
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

void EUtilities::pressKey(const char key)
{
	const short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	EUtilities::pressKey(keyCode);
}

void EUtilities::pressKey(const int keyCode)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;

	EUtilities::pressKey(i);
}

void EUtilities::pressKey(INPUT& input)
{
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
}

void EUtilities::releaseKey(const char key)
{
	const short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	EUtilities::releaseKey(keyCode);
}

void EUtilities::releaseKey(const int keyCode)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;
	EUtilities::releaseKey(i);
}

void EUtilities::releaseKey(INPUT& input)
{
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

void EUtilities::fullKeyPress(const char key, unsigned int pressDuration)
{
	const short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	EUtilities::fullKeyPress(keyCode, pressDuration);
}

void EUtilities::fullKeyPress(const int keyCode, unsigned int pressDuration)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;
	EUtilities::fullKeyPress(i, pressDuration);
}

void EUtilities::fullKeyPress(INPUT& input, unsigned int pressDuration)
{
	EUtilities::pressKey(input);
	Sleep(pressDuration);
	EUtilities::releaseKey(input);
}

void EUtilities::ctrlV()
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

void EUtilities::winR()
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

void EUtilities::humanType(const wchar_t* toWrite, int keyPressInterval)
{
	size_t sizeToWrite{ wcslen(toWrite) };
	INPUT ip{};
	ip.type = INPUT_KEYBOARD;

	for (size_t i{}; i <= sizeToWrite; ++i)
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

void EUtilities::copyToClipBoard(const std::string_view dataToCopy)
{
	if (OpenClipboard(GetActiveWindow()))
	{
		EmptyClipboard();

		HGLOBAL hGlobalAlloc = GlobalAlloc(GMEM_MOVEABLE, dataToCopy.size() + 1);

		if (!hGlobalAlloc)
			std::cout << "Failed to get a handle to the globalAlloc" << '\n';
		else
		{
			memcpy(GlobalLock(hGlobalAlloc), dataToCopy.data(), dataToCopy.size() + 1);
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

void EUtilities::leftClickDown()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void EUtilities::leftClickUp()
{
	INPUT mouseUp{};
	mouseUp.type = INPUT_MOUSE;
	mouseUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &mouseUp, sizeof(INPUT));
}

void EUtilities::leftClick(const int& holdTime)
{
	EUtilities::leftClickDown();
	Sleep(holdTime);
	EUtilities::leftClickUp();
}

// RIGHT CLICK

void EUtilities::rightClickDown()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void EUtilities::rightClickUp()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void EUtilities::rightClick(const int& holdTime)
{
	EUtilities::rightClickDown();
	Sleep(holdTime);
	EUtilities::rightClickUp();
}

void EUtilities::waitForKeyPress(short vKey)
{
	GetAsyncKeyState(vKey); // Reset buffer

	while (!GetAsyncKeyState(vKey))
		Sleep(50);

	while (GetAsyncKeyState(vKey))
		Sleep(50);
}

bool EUtilities::ensureFolderExists(const std::string_view dirName)
{
	bool folderExists = EUtilities::folderExists(dirName);
	if (!folderExists)
		std::filesystem::create_directory(dirName);
	return folderExists;
}

bool EUtilities::folderExists(const std::string_view dirName)
{
	return std::filesystem::is_directory(dirName);
}