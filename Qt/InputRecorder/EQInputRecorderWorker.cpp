#include "EQInputRecorderWorker.h"
#include <QTimer>
#include <QString>

EQInputRecorderWorker::EQInputRecorderWorker()
	: eventsList(), pressedKeys()
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
	eventsList.clear();
	pressedKeys.clear();
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

	for (uint8_t i = 0; i < COUNTDOWN; ++i)
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

EQInputRecorderWorker::~EQInputRecorderWorker() {}