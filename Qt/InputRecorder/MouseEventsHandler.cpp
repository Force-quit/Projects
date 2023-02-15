#include "MouseEventsHandler.h"

#include <Windows.h>
#include <ctime>

const std::vector<uint8_t> MouseEventsHandler::MOUSE_CLICK_VK
{
	VK_LBUTTON,
	VK_RBUTTON,
	VK_MBUTTON,
	VK_XBUTTON1,
	VK_XBUTTON2
};

MouseEventsHandler::MouseEventsHandler(clock_t& currentRecTime, bool& continueListening)
	: currentRecTime{ currentRecTime }, continueListening{ continueListening },
	mouseClickEvents(), mousePressedKeys(), mouseKeysToRemove(),
	mouseMoveEvents()
{

}

void MouseEventsHandler::startListening()
{
	POINT initalMousePos{};
	GetCursorPos(&initalMousePos);
	mouseMoveEvents.push_back(MouseMoveEvent(currentRecTime, initalMousePos));

	while (continueListening)
	{
		checkMouseClickEvents();
		checkMouseMoveEvents();
	}

	if (mouseMoveEvents.size() == 1)
		mouseMoveEvents.clear();
}

std::vector<MouseClickEvent> MouseEventsHandler::getMouseClickEvents() const
{
	return mouseClickEvents;
}

std::vector<MouseMoveEvent> MouseEventsHandler::getMouseMoveEvents() const
{
	return mouseMoveEvents;
}

void MouseEventsHandler::checkMouseClickEvents()
{
	/*for (auto virtualKey : MOUSE_CLICK_VK)
	{
		if (GetAsyncKeyState(virtualKey))
		{
			if (!mousePressedKeys.contains(virtualKey))
			{
				POINT position;
				DWORD mouseData{}, dwFlags{};
				GetCursorPos(&position);
				mouseClickEvents.push_back(MouseClickEvent(std::clock() - start, position, mouseData, dwFlags));
				mousePressedKeys.insert(virtualKey);
			}
		}

		for (uint8_t pressedKey : mousePressedKeys)
		{
			if (!GetAsyncKeyState(pressedKey))
			{
				mouseClickEvents.push_back(Event(std::clock() - start));
				mouseKeysToRemove.push_back(pressedKey);
			}
		}

		for (uint8_t keyToRemove : mouseKeysToRemove)
			mousePressedKeys.erase(keyToRemove);
		mouseKeysToRemove.clear();
	}
	*/
}

void MouseEventsHandler::checkMouseMoveEvents()
{
	const POINT* lastMousePosition = &mouseMoveEvents.back().position;
	POINT currentCursorPos{};
	GetCursorPos(&currentCursorPos);
	if (currentCursorPos.x != lastMousePosition->x || currentCursorPos.y != lastMousePosition->y)
		mouseMoveEvents.push_back(MouseMoveEvent(currentRecTime, currentCursorPos));
}