#pragma once

#include <QObject>
#include <QString>
#include <vector>
#include <QVector>
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

private slots:
	void setMouseClickEvents(QVector<MouseClickEvent>& mouseClickEvents);
	void setMouseMoveEvents(QVector<MouseMoveEvent>& mouseMoveEvents);
	void setKeyboardEvents(QVector<KeyboardEvent>& keyboardEvents);

signals:
	void startListening();

private:
	const uint8_t COUNTDOWN{ 1 };
	void setupTimers(const bool recording);

	void startRealRecording();
	void startRealPlayBack();

	uint8_t nbVectorsReceived;
	QVector<MouseClickEvent> mouseClickEvents;
	QVector<MouseMoveEvent> mouseMoveEvents;
	QVector<KeyboardEvent> keyboardEvents;

	QThread mouseEventsThread;
	MouseEventsWorker* mouseEventsWorker;
	KeyboardEventsHandler keyboardEventsHandler;

	clock_t recordingTime;
};