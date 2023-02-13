#include "EQInputRecorderWorker.h"
#include <QTimer>
#include <QString>
#include <Windows.h>
#include <vector>
#include "MouseEvent.h"

EQInputRecorderWorker::EQInputRecorderWorker()
	: start(), keyboardEvents(), keyboardPressedKeys(), keyboardKeysToRemove(),
	mouseEvents(), mousePressedKeys(), mouseKeysToRemove()
{

}

void EQInputRecorderWorker::startRecording()
{
	setupTimers(true);
}

void EQInputRecorderWorker::startPlayback()
{
	setupTimers(false);
}

void EQInputRecorderWorker::startRealRecording()
{
	keyboardEvents.clear();
	keyboardPressedKeys.clear();
	keyboardKeysToRemove.clear();

	mouseEvents.clear();
	mousePressedKeys.clear();
	mouseKeysToRemove.clear();

	start = std::clock();

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		checkKeyboardEvents();
		checkMouseEvents();
	}
	Event a(3);
}

void EQInputRecorderWorker::startRealPlayBack()
{
	qDebug("play");
}

void EQInputRecorderWorker::setupTimers(const bool recording)
{
	QString textToShow;

	if (recording)
		textToShow = "Recording";
	else
		textToShow = "Playback";

	for (uint8_t i{}; i < COUNTDOWN; ++i)
	{
		QTimer::singleShot(i * 1000, [=]() {
			emit textChanged(textToShow + " in " + QString::number(COUNTDOWN - i) + "...");
		});
	}

	QTimer::singleShot(COUNTDOWN * 1000, [=]() {
		emit textChanged(textToShow + " started");
		if (recording)
			startRealRecording();
		else
			startRealPlayBack();
	});
}

void EQInputRecorderWorker::checkKeyboardEvents()
{
	for (uint8_t virtualKey : KEYBOARD_VK)
	{
		if (GetAsyncKeyState(virtualKey))
		{
			if (!keyboardPressedKeys.contains(virtualKey))
			{
				keyboardEvents.push_back(Event(std::clock() - start));
				keyboardPressedKeys.insert(virtualKey);
			}
		}

		for (uint8_t pressedKey : keyboardPressedKeys)
		{
			if (!GetAsyncKeyState(pressedKey))
			{
				keyboardEvents.push_back(Event(std::clock() - start));
				keyboardKeysToRemove.push_back(pressedKey);
			}
		}

		for (uint8_t keyToRemove : keyboardKeysToRemove)
			keyboardPressedKeys.erase(keyToRemove);
		keyboardKeysToRemove.clear();
	}
}

EQInputRecorderWorker::~EQInputRecorderWorker() {}