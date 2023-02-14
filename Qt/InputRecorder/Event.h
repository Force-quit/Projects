#pragma once

#include <Windows.h>

struct Event
{
	const long positionInTime;
	Event(long time);

	virtual void play(INPUT& input) = 0;
};