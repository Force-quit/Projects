module;

#include <Windows.h>

module eUtilities:Windows;

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