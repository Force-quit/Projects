#include "EQAutoClickerWorker.h"
#include <QTimer>
#include <Windows.h>

EQAutoClickerWorker::EQAutoClickerWorker()
	: active(), clickHoldTime(DEFAULT_HOLD_TIME), timeBetweenClicks(DEFAULT_BETWEEN_TIME), leftClick(true), input()
{
	input.type = INPUT_MOUSE;
}

void EQAutoClickerWorker::setClickHoldTime(int holdTime)
{
	clickHoldTime = holdTime;
}

void EQAutoClickerWorker::setTimeBetweenClicks(int timeBetween)
{
	timeBetweenClicks = timeBetween;
}

void EQAutoClickerWorker::switchState()
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

EQAutoClickerWorker::~EQAutoClickerWorker() {}