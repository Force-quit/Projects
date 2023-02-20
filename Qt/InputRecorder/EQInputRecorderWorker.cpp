#include "EQInputRecorderWorker.h"
#include <QTimer>
#include <QString>
#include <Windows.h>
#include <vector>
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
	connect(mouseEventsWorker, &MouseEventsWorker::mouseMoveEventsReady, this, &EQInputRecorderWorker::setMouseMoveEvents);
	connect(mouseEventsWorker, &MouseEventsWorker::mouseClickEventsReady, this, &EQInputRecorderWorker::setMouseClickEvents);

	//connect(this, &EQInputRecorderWorker::startListening, &keyboardEventsHandler, &KeyboardEventsHandler::startListening);
}

void EQInputRecorderWorker::startRecording()
{
	setupTimers(true);
}

void EQInputRecorderWorker::startPlayback()
{
	setupTimers(false);
}

void EQInputRecorderWorker::setMouseClickEvents(QVector<MouseClickEvent>& mouseClickEvents)
{
	this->mouseClickEvents = mouseClickEvents;
	++nbVectorsReceived;
}

void EQInputRecorderWorker::setMouseMoveEvents(QVector<MouseMoveEvent>& mouseMoveEvents)
{
	this->mouseMoveEvents = mouseMoveEvents;
	++nbVectorsReceived;
}

void EQInputRecorderWorker::setKeyboardEvents(QVector<KeyboardEvent>& keyboardEvents)
{
	this->keyboardEvents = keyboardEvents;
	++nbVectorsReceived;
}

void EQInputRecorderWorker::startRealRecording()
{
	clock_t start{ std::clock() };
	recordingTime = start;
	emit startListening();
	
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		recordingTime = std::clock() - start;
	}

	mouseEventsWorker.stopListening();
	keyboardEventsHandler.stopListening();
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

		while (mouseMoveEventsIt != mouseMoveEvents.end() && mouseMoveEventsIt->getPlayTime() <= recordingTime)
		{
			mouseMoveEventsIt->play();
			++mouseMoveEventsIt;
		}

		while (mouseClickEventsIt != mouseClickEvents.end() && mouseClickEventsIt->getPlayTime() <= recordingTime)
		{
			mouseClickEventsIt->play(input);
			++mouseClickEventsIt;
		}
		
		while (keyboardEventsIt != keyboardEvents.end() && keyboardEventsIt->getPlayTime() <= recordingTime)
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