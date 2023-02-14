#include "MouseClickEvent.h"
#include <Windows.h>

MouseClickEvent::MouseClickEvent(long time, POINT& position, DWORD mouseData, DWORD dwFlags)
	: MouseMoveEvent(time, position), mouseData(mouseData), dwFlags(dwFlags)
{}

void MouseClickEvent::play(INPUT& input)
{
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = dwFlags;
	input.mi.dx = position.x;
	input.mi.dy = position.y;
	input.mi.mouseData = mouseData;
	SendInput(1, &input, sizeof(INPUT));
}