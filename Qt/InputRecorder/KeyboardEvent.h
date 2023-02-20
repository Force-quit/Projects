#pragma once
#include <Windows.h>

class KeyboardEvent
{
public:
	KeyboardEvent(long time, DWORD vkCode, DWORD dwFlags);
	bool operator<(const KeyboardEvent& other) const;
	KeyboardEvent& operator=(const KeyboardEvent& other);
	void play(INPUT& input) const;
	long getPlayTime() const;
private:
	DWORD vkCode, dwFlags;
	long eventPlayTime;
};