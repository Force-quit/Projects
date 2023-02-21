#include "KeyboardEventsWorker.h"
#include <Windows.h>
#include "EQKeyboardEvent.h"
#include <QThread>
#include <QVector>
#include <forward_list>

KeyboardEventsWorker::KeyboardEventsWorker(clock_t& currentRecTime, QVector<uint8_t> keys)
	: currentRecTime(currentRecTime), targetKeys(keys), pressedKeys(), keysToRemove(), continueListening{}, keyboardEvents(),
	readyToShare{}
{}

void KeyboardEventsWorker::startListening()
{
	reset();
	
	while (continueListening)
	{
		for (uint8_t currentKey : targetKeys)
		{
			if (GetAsyncKeyState(currentKey))
			{
				if (!pressedKeys.contains(currentKey))
				{
					keyboardEvents.push_front(EQKeyboardEvent(currentRecTime, currentKey, 0));
					pressedKeys.insert(currentKey);
				}
			}

			for (uint8_t pressedKey : pressedKeys)
			{
				if (!GetAsyncKeyState(pressedKey))
				{
					keyboardEvents.push_front(EQKeyboardEvent(currentRecTime, pressedKey, KEYEVENTF_KEYUP));
					keysToRemove.push_back(pressedKey);
				}
			}

			for (uint8_t keyToRemove : keysToRemove)
				pressedKeys.remove(keyToRemove);
			keysToRemove.clear();
		}

		QThread::msleep(1);
	}

	readyToShare = true;
}

KeyboardEventsWorker::~KeyboardEventsWorker()
{}

QVector<EQKeyboardEvent> KeyboardEventsWorker::getKeyboardEvents() const
{
	QVector<EQKeyboardEvent> events;
	for (auto& i : keyboardEvents)
		events.push_back(i);
	return events;
}

bool KeyboardEventsWorker::isReadyToShare() const
{
	return readyToShare;
}

void KeyboardEventsWorker::reset()
{
	pressedKeys.clear();
	keyboardEvents.clear();
	readyToShare = false;
	continueListening = true;
}

void KeyboardEventsWorker::stopListening()
{
	continueListening = false;
}