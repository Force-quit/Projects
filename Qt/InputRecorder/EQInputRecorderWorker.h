#pragma once

#include <QObject>
#include <QString>
#include <vector>
#include <set>
#include <Windows.h>
#include <QThread>

#include "MouseEventsWorker.h"
#include "KeyboardEventsHandler.h"

#include "MouseClickEvent.h"
#include "MouseMoveEvent.h"
#include "KeyboardEvent.h"


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

private:

signals:
	void startListening();

private:
	const uint8_t COUNTDOWN{ 3 };
	void setupTimers(const bool recording);

	void startRealRecording();
	void startRealPlayBack();

	std::vector<MouseClickEvent> mouseClickEvents;
	std::vector<MouseMoveEvent> mouseMoveEvents;
	std::vector<KeyboardEvent> keyboardEvents;


	QThread mouseEventsHandlerThread;
	MouseEventsWorker* mouseEventsWorker;

	KeyboardEventsHandler keyboardEventsHandler;

	bool continueListening;
	clock_t recordingTime;
};