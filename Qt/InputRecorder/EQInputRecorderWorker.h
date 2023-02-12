#pragma once

#include <QObject>
#include <QString>
#include <forward_list>
#include "Event.h"
#include <set>

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
	const uint8_t COUNTDOWN{ 3 };

	std::forward_list<Event> eventsList;
	std::set<uint8_t> pressedKeys;

	void startRealRecording();
	void startRealPlayBack();

	void setupTimers(const bool recording);
};