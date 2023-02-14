#include "MouseMoveEvent.h"
#include <Windows.h>

MouseMoveEvent::MouseMoveEvent(long time, POINT& position)
	: Event(time), position(position)
{}

void MouseMoveEvent::play(INPUT& input)
{
	SetCursorPos(position.x, position.y);
}