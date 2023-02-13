#include "MouseClickEvent.h"

MouseClickEvent::MouseClickEvent(long time, POINT& position, DWORD mouseData, DWORD dwFlags)
	: MouseMoveEvent(time, position), mouseData(mouseData), dwFlags(dwFlags)
{
}