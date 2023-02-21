#pragma once

#include <QObject>

class EQEvent  : public QObject
{
	Q_OBJECT

public:
	EQEvent(clock_t positionInTime);
	~EQEvent();
	
	clock_t eventPlayTime() const;

protected:
	clock_t eventPositionInTime;
};
