#pragma once

#include <QObject>
#include <vector>
#include <set>
#include "MouseClickEvent.h"

class MouseEventsHandler : public QObject
{
	Q_OBJECT

public:
	MouseEventsHandler(clock_t& currentRecTime, bool& continueListening);
	void checkEvents();
	std::vector<MouseClickEvent> getMouseClickEvents() const;
	std::vector<MouseMoveEvent> getMouseMoveEvents() const;

private:
	const clock_t& currentRecTime;
	const bool& continueListening;

	std::vector<MouseClickEvent> mouseClickEvents;
	std::set<uint8_t> mousePressedKeys;
	std::vector<uint8_t> mouseKeysToRemove;
	void checkMouseClickEvents();

	std::vector<MouseMoveEvent> mouseMoveEvents;
	POINT& lastMousePosition;
	POINT& currentMousePosition;
	void checkMouseMoveEvents();

	const static std::vector<uint8_t> MOUSE_CLICK_VK;
};