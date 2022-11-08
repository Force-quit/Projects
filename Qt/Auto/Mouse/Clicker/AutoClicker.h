#pragma once

#include <QWidget>
#include "ui_AutoClicker.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QButtonGroup>
#include <string>

class AutoClicker : public QWidget
{
	Q_OBJECT

public:
	AutoClicker(const std::string& mainConfigFolder, QWidget *parent = nullptr);
	~AutoClicker();
private:
	Ui::AutoClickerClass ui;
	const std::string CONFIGS_PATH;
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



	QHBoxLayout* initBottomLayout();

	bool keepLookingForInputs;
	void autoClickerThreadFunction();
};
