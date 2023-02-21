#pragma once

#include <QObject>
#include <QVector>
#include <QSet>
#include "EQKeyboardEvent.h"
#include <forward_list>


class KeyboardEventsWorker  : public QObject
{
	Q_OBJECT

public:
	KeyboardEventsWorker(clock_t& currentRecTime, QVector<uint8_t> keys);
	~KeyboardEventsWorker();

	void stopListening();
	QVector<EQKeyboardEvent> getKeyboardEvents() const;
	bool isReadyToShare() const;

public slots:
	void startListening();

private:
	const clock_t& currentRecTime;
	bool continueListening;
	const QVector<uint8_t> targetKeys;
	bool readyToShare;
	void reset();
	QSet<uint8_t> pressedKeys;
	QVector<uint8_t> keysToRemove;
	std::forward_list<EQKeyboardEvent> keyboardEvents;
};