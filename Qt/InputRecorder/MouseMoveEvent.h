#pragma once
#include <Windows.h>

class MouseMoveEvent
{
public:
	MouseMoveEvent(long time, POINT& position);
	void play() const;
	MouseMoveEvent& operator=(const MouseMoveEvent& other);
	long getPlayTime() const;
	POINT position;

private:
	long eventPlayTime;
};