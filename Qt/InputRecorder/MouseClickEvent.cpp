#include "MouseClickEvent.h"
#include <Windows.h>

MouseClickEvent::MouseClickEvent(long time, POINT& position, DWORD mouseData, DWORD dwFlags)
	: eventPlayTime(time), eventPosition(position), mouseData(mouseData), dwFlags(dwFlags)
{}

void MouseClickEvent::play(INPUT& input) const
{
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = dwFlags;
	input.mi.dx = eventPosition.x;
	input.mi.dy = eventPosition.y;
	input.mi.mouseData = mouseData;
	SendInput(1, &input, sizeof(INPUT));
}

MouseClickEvent& MouseClickEvent::operator=(const MouseClickEvent& other)
{
	eventPlayTime = other.eventPlayTime;
	eventPosition = other.eventPosition;
	mouseData = other.mouseData;
	dwFlags = other.dwFlags;
	return *this;
}

long MouseClickEvent::getPlayTime() const
{
	return eventPlayTime;
}
