#pragma once

#include <Windows.h>
#include <QObject>
#include <QThread>
#include <QVector>

#include "EQKeyboardEvent.h"
#include "KeyboardEventsWorker.h"

class KeyboardEventsHandler : public QObject
{
	Q_OBJECT

public:
	KeyboardEventsHandler(QObject* parent, clock_t& currentRecTime);
	~KeyboardEventsHandler();
	
	void stopListening();
	QVector<EQKeyboardEvent> getKeyboardEvents() const;

public slots:
	void startListening();

private slots:

signals:
	void listen();

private:
	QVector<QThread*> workersThreads;
	QVector<KeyboardEventsWorker*> workers;

	const uint8_t KEYS_PER_THREAD{ 4 };
	static QVector<uint8_t> KEYBOARD_VK;
};
