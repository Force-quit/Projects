#pragma once

#include "EQMouseMoveEvent.h"
#include <Windows.h>

class EQMouseClickEvent  : public EQMouseMoveEvent
{
	Q_OBJECT

public:
	EQMouseClickEvent(clock_t positionInTime, POINT eventPosition, DWORD mouseData, DWORD dwFlags);
	EQMouseClickEvent(const EQMouseClickEvent& other);
	EQMouseClickEvent& operator=(const EQMouseClickEvent& other);

	~EQMouseClickEvent();

	void play(INPUT& input) const;

private:
	DWORD mouseData;
	DWORD dwFlags;
};
