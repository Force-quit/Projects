#pragma once
#include <Windows.h>

class MouseClickEvent
{
public:
	MouseClickEvent(long time, POINT& position, DWORD mouseData, DWORD dwFlags);
	void play(INPUT& input) const;
	MouseClickEvent& operator=(const MouseClickEvent& other);
	long getPlayTime() const;

private:
	POINT eventPosition;
	DWORD mouseData, dwFlags;
	long eventPlayTime;
};