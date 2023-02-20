#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent(long time, DWORD vkCode, DWORD dwFlags)
	: eventPlayTime(time), vkCode(vkCode), dwFlags(dwFlags)
{}

bool KeyboardEvent::operator<(const KeyboardEvent & other) const
{
	return eventPlayTime < other.eventPlayTime;
}

KeyboardEvent& KeyboardEvent::operator=(const KeyboardEvent& other)
{
	vkCode = other.vkCode;
	dwFlags = other.dwFlags;
	eventPlayTime = other.eventPlayTime;
	return *this;
}

void KeyboardEvent::play(INPUT& input) const
{
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = vkCode;
	input.ki.dwFlags = dwFlags;
	SendInput(1, &input, sizeof(INPUT));
}

long KeyboardEvent::getPlayTime() const
{
	return eventPlayTime;
}
