#pragma once

#include <QObject>
#include <ctime>
#include <forward_list>
#include "KeyboardEvent.h"


class KeyboardEventsWorker  : public QObject
{
	Q_OBJECT

public:
	KeyboardEventsWorker(clock_t& currentRecTime, bool& continueListening);
	~KeyboardEventsWorker();

	std::vector<KeyboardEvent> getKeyboardEvents() const;

public slots:
	void startListening();

private:
	const clock_t& currentRecTime;
	const bool& continueListening;

	std::forward_list<KeyboardEvent> keyboardEvents;

};
