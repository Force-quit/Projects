#include "MouseEventsWorker.h"

#include <Windows.h>
#include <QVector>
#include <QThread>

#include "EQMouseMoveEvent.h"
#include "EQMouseClickEvent.h"

MouseEventsWorker::MouseEventsWorker(clock_t& currentRecTime)
	: currentRecTime{ currentRecTime }, continueListening{}, readyToShare{}, lastMousePos{}, tempMousePos{},
	mouseClickEvents(), mousePressedKeys(), mouseKeysToRemove(), mouseMoveEvents(),
	MOUSE_CLICK_VK{ VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2 },
	keyUpFlags{
		{VK_LBUTTON, MOUSEEVENTF_LEFTUP},
		{VK_RBUTTON, MOUSEEVENTF_RIGHTUP},
		{VK_MBUTTON, MOUSEEVENTF_MIDDLEUP},
		{VK_XBUTTON1, MOUSEEVENTF_XUP},
		{VK_XBUTTON2, MOUSEEVENTF_XUP}
	},
	keyDownFlags{
		{VK_LBUTTON, MOUSEEVENTF_LEFTDOWN},
		{VK_RBUTTON, MOUSEEVENTF_RIGHTDOWN},
		{VK_MBUTTON, MOUSEEVENTF_MIDDLEDOWN},
		{VK_XBUTTON1, MOUSEEVENTF_XDOWN},
		{VK_XBUTTON2, MOUSEEVENTF_XDOWN}
	},
	mouseData{
		{VK_XBUTTON1, XBUTTON1},
		{VK_XBUTTON2, XBUTTON2}
	}
{

}

void MouseEventsWorker::startListening()
{
	reset();

	while (continueListening)
	{
		checkMouseClickEvents();
		checkMouseMoveEvents();
	}

	readyToShare = true;
}

void MouseEventsWorker::stopListening()
{
	continueListening = false;
}

bool MouseEventsWorker::isReadyToShare() const
{
	return readyToShare;
}

QVector<EQMouseClickEvent> MouseEventsWorker::getMouseClickEvents() const
{
	return mouseClickEvents;
}

QVector<EQMouseMoveEvent> MouseEventsWorker::getMouseMoveEvents() const
{
	return mouseMoveEvents;
}

void MouseEventsWorker::checkMouseClickEvents()
{
	for (uint8_t targetKey : MOUSE_CLICK_VK)
	{
		if (GetAsyncKeyState(targetKey))
		{
			if (!mousePressedKeys.contains(targetKey))
			{
				auto f = keyDownFlags[targetKey];

				GetCursorPos(&tempMousePos);
				mouseClickEvents.push_back(EQMouseClickEvent(currentRecTime, tempMousePos, mouseData[targetKey], keyDownFlags[targetKey]));
				mousePressedKeys.insert(targetKey);
			}
		}

		for (uint8_t pressedKey : mousePressedKeys)
		{
			if (!GetAsyncKeyState(pressedKey))
			{
				GetCursorPos(&tempMousePos);
				mouseClickEvents.push_back(EQMouseClickEvent(currentRecTime, tempMousePos, mouseData[pressedKey], keyUpFlags[pressedKey]));
				mouseKeysToRemove.push_back(pressedKey);
			}
		}

		for (uint8_t keyToRemove : mouseKeysToRemove)
			mousePressedKeys.remove(keyToRemove);
		mouseKeysToRemove.clear();
	}
}

void MouseEventsWorker::checkMouseMoveEvents()
{
	GetCursorPos(&tempMousePos);
	if (tempMousePos.x != lastMousePos.x || tempMousePos.y != lastMousePos.y)
	{
		lastMousePos = tempMousePos;
		mouseMoveEvents.push_back(EQMouseMoveEvent(currentRecTime, lastMousePos));
	}
}

void MouseEventsWorker::reset()
{
	GetCursorPos(&lastMousePos);
	continueListening = true;
	readyToShare = false;
	mouseClickEvents.clear();
	mousePressedKeys.clear();

	for (uint8_t targetKey : MOUSE_CLICK_VK)
		GetAsyncKeyState(targetKey);
}