#pragma once
#include <Windows.h>

struct MouseClickEvent
{
	const POINT eventPosition;
	const DWORD mouseData, dwFlags;
	const long eventPlayTime;
	MouseClickEvent(long time, POINT& position, DWORD mouseData, DWORD dwFlags);
	void play(INPUT& input) const;
};