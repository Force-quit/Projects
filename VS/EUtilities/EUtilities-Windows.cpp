module;

#include <Windows.h>

module EUtilities:Windows;

void EUtilities::waitForFullKeyPress(short vKey)
{
	GetAsyncKeyState(vKey); // Reset buffer

	EUtilities::waitForKeyPress(vKey);

	EUtilities::waitForKeyRelease(vKey);
}

void EUtilities::waitForKeyPress(short vKey)
{
	while (!GetAsyncKeyState(vKey))
		Sleep(50);
}

void EUtilities::waitForKeyRelease(short vKey)
{
	while (GetAsyncKeyState(vKey))
		Sleep(50);
}