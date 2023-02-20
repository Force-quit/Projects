#pragma once

#include <Windows.h>
#include <QObject>
#include <vector>
#include <QThread>

#include "KeyboardEvent.h"
#include "KeyboardEventsWorker.h"

class KeyboardEventsHandler : public QObject
{
	Q_OBJECT

public:
	KeyboardEventsHandler(QObject* parent, clock_t& currentRecTime);
	~KeyboardEventsHandler();
	std::vector<KeyboardEvent> getKeyboardEvents() const;
	void requestInterruption();

public slots:
	void startListening();

private slots:
signals:
	void listen();

private:
	std::vector<QThread*> workersThreads;
	std::vector<KeyboardEventsWorker*> workers;

	const uint8_t KEYS_PER_THREAD{ 4 };
	static std::vector<uint8_t> KEYBOARD_VK;
};
