#pragma once

#include <QObject>
#include <ctime>
#include <forward_list>
#include "KeyboardEvent.h"
#include <vector>
#include <set>

class KeyboardEventsWorker  : public QObject
{
	Q_OBJECT

public:
	KeyboardEventsWorker(clock_t& currentRecTime, std::vector<uint8_t> keys);
	~KeyboardEventsWorker();

	std::vector<KeyboardEvent> getKeyboardEvents() const;

public slots:
	void startListening();

private:
	const clock_t& currentRecTime;
	const std::vector<uint8_t> targetKeys;

	std::set<uint8_t> pressedKeys;
	std::vector<uint8_t> keysToRemove;
	std::forward_list<KeyboardEvent> keyboardEvents;
};