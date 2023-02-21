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

	void play() const;

protected:
	POINT eventPosition;
};
