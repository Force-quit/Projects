#pragma once

#include <QObject>
#include <ctime>


class KeyboardEventsWorker  : public QObject
{
	Q_OBJECT

public:
	KeyboardEventsWorker(clock_t& currentRecTime, bool& continueListening);
	~KeyboardEventsWorker();

public slots:
	void startListening();

private:
	const clock_t& currentRecTime;
	const bool& continueListening;
};
