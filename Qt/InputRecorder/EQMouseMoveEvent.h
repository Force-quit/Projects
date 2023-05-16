#pragma once

#include "EQEvent.h"
#include <Windows.h>

class EQMouseMoveEvent  : public EQEvent
{
	Q_OBJECT

public:
	EQMouseMoveEvent(clock_t positionInTime, POINT eventPosition);
	~EQMouseMoveEvent();
	EQMouseMoveEvent(const EQMouseMoveEvent& other);
	EQMouseMoveEvent& operator=(const EQMouseMoveEvent& other);

	inline void play() const
	{
		SetCursorPos(eventPosition.x, eventPosition.y);
	}

protected:
	POINT eventPosition;
};
