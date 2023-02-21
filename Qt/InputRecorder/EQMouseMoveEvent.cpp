#include "EQMouseMoveEvent.h"
#include <Windows.h>

EQMouseMoveEvent::EQMouseMoveEvent(clock_t positionInTime, POINT eventPosition)
	: EQEvent(positionInTime), eventPosition{ eventPosition }
{
}

EQMouseMoveEvent::EQMouseMoveEvent(const EQMouseMoveEvent& other)
	: EQMouseMoveEvent(other.eventPositionInTime, other.eventPosition)
{
}

EQMouseMoveEvent& EQMouseMoveEvent::operator=(const EQMouseMoveEvent& other)
{
	eventPosition = other.eventPosition;
	eventPositionInTime = other.eventPositionInTime;
	return *this;
}

void EQMouseMoveEvent::play() const
{
	SetCursorPos(eventPosition.x, eventPosition.y);
}

EQMouseMoveEvent::~EQMouseMoveEvent()
{}