#include "KeyboardEventsWorker.h"
#include <Windows.h>
#include "KeyboardEvent.h"
#include <QThread>

KeyboardEventsWorker::KeyboardEventsWorker(clock_t& currentRecTime, std::vector<uint8_t> keys)
	: currentRecTime(currentRecTime), targetKeys(keys),	pressedKeys(), keysToRemove()
{}

void KeyboardEventsWorker::startListening()
{
	while (!QThread::currentThread()->isInterruptionRequested())
	{
		for (auto currentKey : targetKeys)
		{
			if (GetAsyncKeyState(currentKey))
			{
				if (!pressedKeys.contains(currentKey))
				{
					keyboardEvents.push_front(KeyboardEvent(currentRecTime, currentKey, 0));
					pressedKeys.insert(currentKey);
				}
			}

			for (uint8_t pressedKey : pressedKeys)
			{
				if (!GetAsyncKeyState(pressedKey))
				{
					keyboardEvents.push_front(KeyboardEvent(currentRecTime, currentKey, KEYEVENTF_KEYUP));
					keysToRemove.push_back(pressedKey);
				}
			}

			for (uint8_t keyToRemove : keysToRemove)
				pressedKeys.erase(keyToRemove);
			keysToRemove.clear();
		}

	}
}

KeyboardEventsWorker::~KeyboardEventsWorker()
{}

std::vector<KeyboardEvent> KeyboardEventsWorker::getKeyboardEvents() const
{
	std::vector<KeyboardEvent> events;
	for (auto& i : keyboardEvents)
		events.push_back(i);
	return events;
}
