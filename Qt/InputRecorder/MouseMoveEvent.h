#pragma once
#include <Windows.h>

struct MouseMoveEvent
{
	const POINT position;
	const long eventPlayTime;
	MouseMoveEvent(long time, POINT& position);
	void play() const;
};