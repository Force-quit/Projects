#include "MouseEventsWorker.h"

#include <Windows.h>
#include <ctime>
#include <vector>
#include <QThread>

#include "MouseMoveEvent.h"
#include "MouseClickEvent.h"

MouseEventsWorker::MouseEventsWorker(clock_t& currentRecTime)
	: currentRecTime{ currentRecTime },
	mouseClickEvents(), mousePressedKeys(), mouseKeysToRemove(),
	mouseMoveEvents(),
	MOUSE_CLICK_VK{ VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2 }
{

}

void MouseEventsWorker::startListening()
{
	POINT initalMousePos{};
	GetCursorPos(&initalMousePos);
	mouseMoveEvents.push_back(MouseMoveEvent(currentRecTime, initalMousePos));

	while (!QThread::currentThread()->isInterruptionRequested())
	{
		checkMouseClickEvents();
		checkMouseMoveEvents();
	}

	if (mouseMoveEvents.size() == 1)
		mouseMoveEvents.clear();
	
	emit mouseMoveEventsReady(mouseMoveEvents);
	emit mouseClickEventsReady(mouseClickEvents);
}

void MouseEventsWorker::checkMouseClickEvents()
{
	/*for (uint8_t targetKey : MOUSE_CLICK_VK)
	{
		if (GetAsyncKeyState(targetKey))
		{
			if (!mousePressedKeys.contains(targetKey))
			{
				POINT position;
				DWORD mouseData{}, dwFlags{};
				GetCursorPos(&position);
				mouseClickEvents.push_back(MouseClickEvent(currentRecTime, position, mouseData, dwFlags));
				mousePressedKeys.insert(targetKey);
			}
		}

		for (uint8_t pressedKey : mousePressedKeys)
		{
			if (!GetAsyncKeyState(pressedKey))
			{
				POINT position;
				DWORD mouseData{}, dwFlags{};
				GetCursorPos(&position);
				mouseClickEvents.push_back(MouseClickEvent(std::clock() - start));
				mouseKeysToRemove.push_back(pressedKey);
			}
		}

		for (uint8_t keyToRemove : mouseKeysToRemove)
			mousePressedKeys.erase(keyToRemove);
		mouseKeysToRemove.clear();
	}*/
}

void MouseEventsWorker::checkMouseMoveEvents()
{
	const POINT* lastMousePosition = &mouseMoveEvents.back().position;
	POINT currentCursorPos{};
	GetCursorPos(&currentCursorPos);
	if (currentCursorPos.x != lastMousePosition->x || currentCursorPos.y != lastMousePosition->y)
		mouseMoveEvents.push_back(MouseMoveEvent(currentRecTime, currentCursorPos));
}