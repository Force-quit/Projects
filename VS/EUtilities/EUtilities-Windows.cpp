module;

#include <Windows.h>

module eutilities:Windows;

void eutilities::windows::waitForFullKeyPress(short vKey)
{
	GetAsyncKeyState(vKey); // Reset buffer

	eutilities::windows::waitForKeyPress(vKey);

	eutilities::windows::waitForKeyRelease(vKey);
}

void eutilities::windows::waitForKeyPress(short vKey)
{
	while (!GetAsyncKeyState(vKey))
		Sleep(50);
}

void eutilities::windows::waitForKeyRelease(short vKey)
{
	while (GetAsyncKeyState(vKey))
		Sleep(50);
}