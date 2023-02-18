#include "EQInputRecorderWorker.h"
#include <QTimer>
#include <QString>
#include <Windows.h>
#include <vector>
#include "MouseEventsHandler.h"

EQInputRecorderWorker::EQInputRecorderWorker()
	: currentRecordingTime{}, continueListening{}, 
	mouseEventsWorker{ new MouseEventsHandler(currentRecordingTime, continueListening)}, mouseEventsThread(),
	allEvents()
{
	mouseEventsWorker->moveToThread(&mouseEventsThread);
	connect(&mouseEventsThread, &QThread::finished, mouseEventsWorker, &QObject::deleteLater);
	mouseEventsThread.start();

	connect(this, &EQInputRecorderWorker::startListening, mouseEventsWorker, &MouseEventsHandler::startListening);
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
	currentRecordingTime = std::clock();
	continueListening = true;
	emit startListening();
	
	while (!GetAsyncKeyState(VK_ESCAPE))
		currentRecordingTime = std::clock();
	continueListening = false;

	mouseEventsThread.wait();
	allEvents.push_back(mouseEventsWorker->getMouseMoveEvents());
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

EQInputRecorderWorker::~EQInputRecorderWorker() 
{
	mouseEventsThread.quit();
	mouseEventsThread.wait();
}