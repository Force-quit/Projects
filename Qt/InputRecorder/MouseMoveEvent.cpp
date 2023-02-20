#include "MouseMoveEvent.h"
#include <Windows.h>

MouseMoveEvent::MouseMoveEvent(long time, POINT& position)
	: eventPlayTime(time), position(position)
{}

void MouseMoveEvent::play() const
{
	SetCursorPos(position.x, position.y);
}

MouseMoveEvent& MouseMoveEvent::operator=(const MouseMoveEvent& other)
{
	position = other.position;
	eventPlayTime = other.eventPlayTime;
	return *this;
}

long MouseMoveEvent::getPlayTime() const
{
	return eventPlayTime;
}
