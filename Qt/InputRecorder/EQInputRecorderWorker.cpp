#include "EQInputRecorderWorker.h"
#include <QTimer>
#include <QString>
#include <Windows.h>
#include <vector>
#include "MouseEventsWorker.h"

EQInputRecorderWorker::EQInputRecorderWorker()
	: recordingTime{}, continueListening{}, 
	mouseEventsWorker{ new MouseEventsWorker(recordingTime, continueListening)}, mouseEventsHandlerThread(),
	keyboardEventsHandler(this, recordingTime, continueListening),
	mouseMoveEvents(), mouseClickEvents(), keyboardEvents()
{
	mouseEventsWorker->moveToThread(&mouseEventsHandlerThread);
	connect(&mouseEventsHandlerThread, &QThread::finished, mouseEventsWorker, &QObject::deleteLater);
	mouseEventsHandlerThread.start();

	connect(this, &EQInputRecorderWorker::startListening, mouseEventsWorker, &MouseEventsWorker::startListening);
	connect(this, &EQInputRecorderWorker::startListening, &keyboardEventsHandler, &KeyboardEventsHandler::startListening);
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
	clock_t start{ std::clock() };
	recordingTime = start;
	continueListening = true;
	emit startListening();
	
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		recordingTime = std::clock() - start;
	}
	continueListening = false;

	mouseEventsHandlerThread.wait();
	mouseMoveEvents = mouseEventsWorker->getMouseMoveEvents();
	mouseClickEvents = mouseEventsWorker->getMouseClickEvents();

}

void EQInputRecorderWorker::startRealPlayBack()
{
	auto mouseMoveEventsIt = mouseMoveEvents.begin();
	auto mouseClickEventsIt = mouseClickEvents.begin();
	auto keyboardEventsIt = keyboardEvents.begin();

	long currentPlaybackTime{};
	clock_t playbackStart{ std::clock() };

	MouseMoveEvent* nextMouseMoveEvent{};
	MouseClickEvent* nextMouseClickEvent{};
	KeyboardEvent* nextKeyboardEvent{};
	INPUT input{};

	do
	{
		currentPlaybackTime = std::clock() - playbackStart;

		while (mouseMoveEventsIt != mouseMoveEvents.end() && mouseMoveEventsIt->eventPlayTime <= recordingTime)
		{
			mouseMoveEventsIt->play();
			++mouseMoveEventsIt;
		}

		while (mouseClickEventsIt != mouseClickEvents.end() && mouseClickEventsIt->eventPlayTime <= recordingTime)
		{
			mouseClickEventsIt->play(input);
			++mouseClickEventsIt;
		}
		
		while (keyboardEventsIt != keyboardEvents.end() && keyboardEventsIt->eventPlayTime <= recordingTime)
		{
			keyboardEventsIt->play(input);
			++keyboardEventsIt;
		}

	} while (currentPlaybackTime < recordingTime);
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

EQInputRecorderWorker::~EQInputRecorderWorker() 
{
	mouseEventsHandlerThread.quit();
	mouseEventsHandlerThread.wait();
}