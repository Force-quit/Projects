module;

#include <Windows.h>

module eUtilities:windows;

void eUtilities::windows::waitForFullKeyPress(short vKey)
{
	GetAsyncKeyState(vKey); // Reset buffer

	eUtilities::windows::waitForKeyPress(vKey);

	eUtilities::windows::waitForKeyRelease(vKey);
}

void eUtilities::windows::waitForKeyPress(short vKey)
{
	while (!GetAsyncKeyState(vKey))
		Sleep(50);
}

void eUtilities::windows::waitForKeyRelease(short vKey)
{
	while (GetAsyncKeyState(vKey))
		Sleep(50);
}

void eUtilities::windows::Console::consoleBundle()
{
	eUtilities::windows::Console::preventConsoleResize();
	eUtilities::windows::Console::hideCursor();
	eUtilities::windows::Console::disableQuickEdit();
	eUtilities::windows::Console::hideScrollingBar();
}

void eUtilities::windows::Console::preventConsoleResize()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void eUtilities::windows::Console::hideCursor()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor{};
	lpCursor.bVisible = false;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void eUtilities::windows::Console::disableQuickEdit()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void eUtilities::windows::Console::hideScrollingBar()
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