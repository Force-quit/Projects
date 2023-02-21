#include "EQEvent.h"

EQEvent::EQEvent(clock_t positionInTime)
	: eventPositionInTime{positionInTime}
{}

EQEvent::~EQEvent()
{}

clock_t EQEvent::eventPlayTime() const
{
	return eventPositionInTime;
}
