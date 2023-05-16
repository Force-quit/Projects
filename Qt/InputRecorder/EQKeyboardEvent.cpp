#include "EQKeyboardEvent.h"
#include <Windows.h>

EQKeyboardEvent::EQKeyboardEvent(clock_t positionInTime, DWORD vkCode, DWORD dwFlags)
	: EQEvent(positionInTime), vkCode{vkCode}, dwFlags{dwFlags}
{
}

void EQKeyboardEvent::play(INPUT & input) const
{
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = vkCode;
	input.ki.dwFlags = dwFlags;
	SendInput(1, &input, sizeof(INPUT));
}

EQKeyboardEvent::~EQKeyboardEvent()
{}

EQKeyboardEvent::EQKeyboardEvent(const EQKeyboardEvent & other)
	: EQKeyboardEvent(other.eventPositionInTime, other.vkCode, other.dwFlags)
{
}

EQKeyboardEvent& EQKeyboardEvent::operator=(const EQKeyboardEvent& other)
{
	eventPositionInTime = other.eventPositionInTime;
	vkCode = other.vkCode;
	dwFlags = other.dwFlags;
	return *this;
}

bool EQKeyboardEvent::operator<(const EQKeyboardEvent& other) const
{
	return eventPositionInTime < other.eventPositionInTime;
}
