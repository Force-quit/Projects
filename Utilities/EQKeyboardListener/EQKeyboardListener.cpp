#include "EQKeyboardListener.h"
#include <QString>
#include <QTimer>
#include <Windows.h>
#include <QVector>

EQKeyboardListener::EQKeyboardListener(QVector<int> virtualKeys, unsigned short checkInterval)
	: targetKeys(virtualKeys), checkInterval(checkInterval), canTrigger(true), pressedKeys(), listening()
{

}

void EQKeyboardListener::setTargetKeys(QVector<int> virtualKeys)
{
	targetKeys = virtualKeys;
}

void EQKeyboardListener::setCheckInterval(unsigned short newInterval)
{
	checkInterval = newInterval;
}

void EQKeyboardListener::check()
{
	pressedKeys = 0;

	for (auto& i : targetKeys)
	{
		if (GetAsyncKeyState(i))
			++pressedKeys;
		else
			canTrigger = true;
	}

	if (pressedKeys == targetKeys.size() && canTrigger)
	{
		emit targetKeysPressed();
		canTrigger = false;
	}
	
	if (listening)
		QTimer::singleShot(checkInterval, this, &EQKeyboardListener::check);
}

void EQKeyboardListener::stopListening()
{
	listening = false;
}

void EQKeyboardListener::startListening()
{
	listening = true;
	QTimer::singleShot(checkInterval, this, &EQKeyboardListener::check);
}

EQKeyboardListener::~EQKeyboardListener() {}