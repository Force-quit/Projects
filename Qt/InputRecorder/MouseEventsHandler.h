#pragma once

#include <vector>
#include <set>
#include "MouseClickEvent.h"

class MouseEventsHandler
{
public:
	MouseEventsHandler();
	void checkEvents();

private:
	clock_t start;
	std::vector<MouseClickEvent> mouseClickEvents;
	std::set<uint8_t> mousePressedKeys;
	std::vector<uint8_t> mouseKeysToRemove;
	void checkMouseClickEvents();

	std::vector<MouseMoveEvent> mouseMoveEvents;
	void checkMouseMoveEvents();

	const static std::vector<uint8_t> MOUSE_CLICK_VK;
};