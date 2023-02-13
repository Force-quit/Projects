#pragma once
#include "Event.h"
#include <Windows.h>

struct KeyboardEvent : public Event
{
	DWORD vkCode, dwFlags;
	KeyboardEvent(long time, DWORD vkCode, DWORD dwFlags);
};