#pragma once

#include <QWidget>
#include "ui_AutoClicker.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QButtonGroup>

class AutoClicker : public QWidget
{
	Q_OBJECT

public:
	AutoClicker(QWidget *parent = nullptr);
	~AutoClicker();

private:
	Ui::AutoClickerClass ui;
	
	QIntValidator* intValidator;

	QLineEdit* clickHoldTimeEdit;
	const unsigned int defaultClickHoldTime = 50;
	unsigned int clickHoldTime;
	bool invalidClickHoldTime;

	QLineEdit* timeBetweenClicksEdit;
	const unsigned int defaultTimeBetweenClicks = 200;
	unsigned int timeBetweenClicks;
	bool invalidTimeBetweenClicks;

	QButtonGroup* clickButtonGroup;
	bool leftClick;

	QGroupBox* initParameters();
	QHBoxLayout* initClickHoldTime();
	QHBoxLayout* initTimeBetweenClicks();
	QHBoxLayout* initClickButton();
	QHBoxLayout* initSaveAndLoad();
};
