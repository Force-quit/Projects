#pragma once

#include <QObject>
#include "../../Utilities/EQKeyboardListener/EQKeyboardListener.h"
#include <Windows.h>

class EQAutoClickerWorker  : public QObject
{
	Q_OBJECT

public:
	EQAutoClickerWorker();
	~EQAutoClickerWorker();

	static const unsigned int MIN_TIME{ 1 };
	static const unsigned int MAX_TIME{ UINT_MAX };
	static const unsigned int DEFAULT_CLICK_HOLD_TIME{ 10 };
	static const unsigned int DEFAULT_BETWEEN_TIME{ 30 };

	unsigned int getClickHoldTime() const;
	unsigned int getTimeBetweenClicks() const;
	bool isTargetLeftClick() const;
	void setLeftClick(bool leftClick);

public slots:
	void setClickHoldTime(unsigned int holdTime);
	void setTimeBetweenClicks(unsigned int timeBetween);
	void activate();

signals:
	void activated();
	void deactivated();

private slots:
	void clickDown();
	void clickUp();

private:
	unsigned int clickHoldTime;
	unsigned int timeBetweenClicks;
	bool leftClick;
	INPUT input;

	bool active;


};
