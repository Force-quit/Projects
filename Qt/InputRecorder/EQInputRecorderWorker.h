#pragma once

#include <Windows.h>
#include <QObject>
#include <QThread>

#include <QString>
#include <QVector>
#include <QSet>

#include "MouseEventsWorker.h"
#include "KeyboardEventsHandler.h"

#include "EQMouseClickEvent.h"
#include "EQMouseMoveEvent.h"
#include "EQKeyboardEvent.h"


class EQInputRecorderWorker  : public QObject
{
	Q_OBJECT

public:
	EQInputRecorderWorker();
	~EQInputRecorderWorker();

public slots:
	void startRecording();
	void startPlayback();


signals:
	void textChanged(const QString& newText);
	void finishedRecording();

private slots:

signals:
	void startListening();

private:
	const uint8_t COUNTDOWN{ 1 };
	void setupTimers(const bool recording);

	void startRealRecording();
	void startRealPlayBack();

	uint8_t nbVectorsReceived;

	QVector<EQMouseClickEvent> mouseClickEvents;
	QVector<EQMouseMoveEvent> mouseMoveEvents;
	QVector<EQKeyboardEvent> keyboardEvents;

	QThread mouseEventsThread;
	MouseEventsWorker* mouseEventsWorker;

	KeyboardEventsHandler keyboardEventsHandler;

	clock_t recordingTime;
};