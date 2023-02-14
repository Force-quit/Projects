#pragma once

#include "Event.h"
#include <Windows.h>

struct MouseMoveEvent : public Event
{
	const POINT position;
	MouseMoveEvent(long time, POINT& position);

	void play(INPUT& input) override;
};