#pragma once

#include <QObject>
#include <Windows.h>
#include "../../Utilities/Qt/EQKeyboardListener/EQKeyboardListener.h"

class EQAutoClickerWorker  : public QObject
{
	Q_OBJECT

public:
	EQAutoClickerWorker();
	~EQAutoClickerWorker();

	static const int MIN_INTERVAL{ 1 };
	static const int MAX_INTERVAL{ INT_MAX };
	static const int DEFAULT_HOLD_TIME{ 10 };
	static const int DEFAULT_BETWEEN_TIME{ 30 };

	inline int getClickHoldTime() const
	{
		return clickHoldTime;
	}

	inline int getTimeBetweenClicks() const
	{
		return timeBetweenClicks;
	}

	inline bool isTargetLeftClick() const
	{
		return leftClick;
	}

	inline bool isActive() const
	{
		return active;
	}

	void setLeftClick(bool leftClick);

public slots:
	void setClickHoldTime(int holdTime);
	void setTimeBetweenClicks(int timeBetween);
	void switchState();

signals:
	void activated();
	void deactivated();

private slots:
	void clickDown();
	void clickUp();

private:
	int clickHoldTime;
	int timeBetweenClicks;
	bool leftClick;
	INPUT input;

	bool active;
};