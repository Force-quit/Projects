#include "EQInputRecorderWorker.h"
#include <QTimer>
#include <QString>
#include <Windows.h>
#include "MouseEventsWorker.h"
#include <QVector>

EQInputRecorderWorker::EQInputRecorderWorker()
	: recordingTime{}, nbVectorsReceived{},
	mouseEventsWorker{ new MouseEventsWorker(recordingTime)}, mouseEventsThread(),
	keyboardEventsHandler(this, recordingTime),
	mouseMoveEvents(), mouseClickEvents(), keyboardEvents()
{
	mouseEventsWorker->moveToThread(&mouseEventsThread);
	connect(&mouseEventsThread, &QThread::finished, mouseEventsWorker, &QObject::deleteLater);
	mouseEventsThread.start();

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
	mouseEventsThread.start();
	clock_t start{ std::clock() };
	recordingTime = start;
	emit startListening();
	
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		recordingTime = std::clock() - start;
	}

	mouseEventsWorker->stopListening();
	keyboardEventsHandler.stopListening();

	while (!mouseEventsWorker->isReadyToShare())
		QThread::msleep(5);

    mouseMoveEvents = mouseEventsWorker->getMouseMoveEvents();
	mouseClickEvents = mouseEventsWorker->getMouseClickEvents();

	keyboardEvents = keyboardEventsHandler.getKeyboardEvents();

	emit textChanged("Finished recording");
	emit finishedRecording();
}

void EQInputRecorderWorker::startRealPlayBack()
{
	auto mouseMoveEventsIt = mouseMoveEvents.begin();
	auto mouseClickEventsIt = mouseClickEvents.begin();
	auto keyboardEventsIt = keyboardEvents.begin();

	long currentPlaybackTime{};
	clock_t playbackStart{ std::clock() };

	EQMouseMoveEvent* nextMouseMoveEvent{};
	EQMouseClickEvent* nextMouseClickEvent{};
	EQKeyboardEvent* nextKeyboardEvent{};
	INPUT input{};

	do
	{
		currentPlaybackTime = std::clock() - playbackStart;

		while (mouseMoveEventsIt != mouseMoveEvents.end() && mouseMoveEventsIt->eventPlayTime() <= currentPlaybackTime)
		{
			mouseMoveEventsIt->play();
			++mouseMoveEventsIt;
		}

		while (mouseClickEventsIt != mouseClickEvents.end() && mouseClickEventsIt->eventPlayTime() <= currentPlaybackTime)
		{
			mouseClickEventsIt->play(input);
			++mouseClickEventsIt;
		}
		
		while (keyboardEventsIt != keyboardEvents.end() && keyboardEventsIt->eventPlayTime() <= currentPlaybackTime)
		{
			keyboardEventsIt->play(input);
			++keyboardEventsIt;
		}

	} while (currentPlaybackTime < recordingTime);
	emit textChanged("Finished playback");
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
	mouseEventsThread.quit();
	mouseEventsThread.wait();
}