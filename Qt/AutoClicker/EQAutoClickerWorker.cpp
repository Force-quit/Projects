#include "EQAutoClickerWorker.h"
#include <QTimer>
#include <Windows.h>

EQAutoClickerWorker::EQAutoClickerWorker()
	: active(), clickHoldTime(DEFAULT_CLICK_HOLD_TIME), timeBetweenClicks(DEFAULT_BETWEEN_TIME), leftClick(true), input()
{
	input.type = INPUT_MOUSE;
}

void EQAutoClickerWorker::setClickHoldTime(unsigned int holdTime)
{
	clickHoldTime = holdTime;
}

void EQAutoClickerWorker::setTimeBetweenClicks(unsigned int timeBetween)
{
	timeBetweenClicks = timeBetween;
}

void EQAutoClickerWorker::activate()
{
	active = !active;
	if (active)
	{
		emit activated();
		clickDown();
	}
	else
		emit deactivated();
}

void EQAutoClickerWorker::clickDown()
{
	if (active)
	{
		input.mi.dwFlags = leftClick ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN;
		SendInput(1, &input, sizeof(INPUT));
		QTimer::singleShot(clickHoldTime, this, &EQAutoClickerWorker::clickUp);
	}
}

void EQAutoClickerWorker::clickUp()
{
	input.mi.dwFlags = leftClick ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;
	SendInput(1, &input, sizeof(INPUT));
	QTimer::singleShot(timeBetweenClicks, this, &EQAutoClickerWorker::clickDown);
}

void EQAutoClickerWorker::setLeftClick(bool leftClick)
{
	this->leftClick = leftClick;
}

unsigned int EQAutoClickerWorker::getClickHoldTime() const
{
	return clickHoldTime;
}

unsigned int EQAutoClickerWorker::getTimeBetweenClicks() const
{
	return timeBetweenClicks;
}

bool EQAutoClickerWorker::isTargetLeftClick() const
{
	return leftClick;
}

EQAutoClickerWorker::~EQAutoClickerWorker() {}