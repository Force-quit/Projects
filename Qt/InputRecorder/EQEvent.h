#pragma once

#include <QObject>

class EQEvent  : public QObject
{
	Q_OBJECT

public:
	EQEvent(clock_t positionInTime);
	~EQEvent();
	
	inline clock_t eventPlayTime() const
	{
		return eventPositionInTime;
	}

protected:
	clock_t eventPositionInTime;
};
