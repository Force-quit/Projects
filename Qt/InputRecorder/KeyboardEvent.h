#pragma once
#include <Windows.h>

struct KeyboardEvent
{
	const DWORD vkCode, dwFlags;
	const long eventPlayTime;
	KeyboardEvent(long time, DWORD vkCode, DWORD dwFlags);
	void play(INPUT& input) const;
};