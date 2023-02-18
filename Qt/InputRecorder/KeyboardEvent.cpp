#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent(long time, DWORD vkCode, DWORD dwFlags)
	: eventPlayTime(time), vkCode(vkCode), dwFlags(dwFlags)
{}

void KeyboardEvent::play(INPUT& input) const
{
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = vkCode;
	input.ki.dwFlags = dwFlags;
	SendInput(1, &input, sizeof(INPUT));
}