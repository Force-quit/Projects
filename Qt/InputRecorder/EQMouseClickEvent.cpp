#include "EQMouseClickEvent.h"
#include <Windows.h>

EQMouseClickEvent::EQMouseClickEvent(clock_t positionInTime, POINT eventPosition, DWORD mouseData, DWORD dwFlags)
	: EQMouseMoveEvent(positionInTime, eventPosition), mouseData{ mouseData }, dwFlags{ dwFlags }
{}

EQMouseClickEvent::EQMouseClickEvent(const EQMouseClickEvent & other)
	: EQMouseClickEvent(other.eventPositionInTime, other.eventPosition, other.mouseData, other.dwFlags)
{
}

EQMouseClickEvent& EQMouseClickEvent::operator=(const EQMouseClickEvent& other)
{
	mouseData = other.mouseData;
	dwFlags = other.dwFlags;
	eventPosition = other.eventPosition;
	eventPositionInTime = other.eventPositionInTime;
	return *this;
}

EQMouseClickEvent::~EQMouseClickEvent()
{}

void EQMouseClickEvent::play(INPUT & input) const
{
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = dwFlags;
	input.mi.dx = eventPosition.x;
	input.mi.dy = eventPosition.y;
	input.mi.mouseData = mouseData;
	SendInput(1, &input, sizeof(INPUT));
}