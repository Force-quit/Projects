#pragma once

#include "EQEvent.h"
#include <Windows.h>

class EQKeyboardEvent  : public EQEvent
{
	Q_OBJECT

public:
	EQKeyboardEvent(clock_t positionInTime, DWORD vkCode, DWORD dwFlags);
	~EQKeyboardEvent();

	EQKeyboardEvent(const EQKeyboardEvent& other);
	EQKeyboardEvent& operator=(const EQKeyboardEvent& other);
	bool operator<(const EQKeyboardEvent& other) const;

	void play(INPUT& input) const;

	inline DWORD getVkCode() const
	{
		return vkCode;
	}

private:
	DWORD vkCode;
	DWORD dwFlags;
};
