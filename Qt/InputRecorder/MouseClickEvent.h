#pragma once

#include "MouseMoveEvent.h"
#include <Windows.h>

struct MouseClickEvent : public MouseMoveEvent
{
	const DWORD mouseData, dwFlags;
	MouseClickEvent(long time, POINT& position, DWORD mouseData, DWORD dwFlags);

	void play(INPUT& input) override;
};