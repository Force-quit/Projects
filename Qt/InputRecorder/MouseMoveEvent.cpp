#include "MouseMoveEvent.h"
#include <Windows.h>

MouseMoveEvent::MouseMoveEvent(long time, POINT& position)
	: eventPlayTime(time), position(position)
{}

void MouseMoveEvent::play() const
{
	SetCursorPos(position.x, position.y);
}