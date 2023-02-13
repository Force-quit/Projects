#include "MouseMoveEvent.h"

MouseMoveEvent::MouseMoveEvent(long time, POINT& position)
	: Event(time), position(position)
{
}