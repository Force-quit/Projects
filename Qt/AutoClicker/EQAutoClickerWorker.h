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

	int getClickHoldTime() const;
	int getTimeBetweenClicks() const;
	bool isTargetLeftClick() const;
	bool isActive() const;

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