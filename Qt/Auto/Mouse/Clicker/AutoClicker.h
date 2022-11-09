#pragma once

#include <QWidget>
#include "ui_AutoClicker.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QButtonGroup>
#include <string>
#include "../../QSmartLineEdit.h"

class AutoClicker : public QWidget
{
	Q_OBJECT

public:
	AutoClicker(const std::string& mainConfigFolder, QWidget *parent = nullptr);
	~AutoClicker();
private:
	Ui::AutoClickerClass ui;
	const std::string CONFIGS_PATH; // Defined in constructor
	QIntValidator* intValidator;

	QSmartLineEdit* clickHoldTimeEdit;
	const unsigned int defaultClickHoldTime = 50;
	unsigned int clickHoldTime;

	QSmartLineEdit* timeBetweenClicksEdit;
	const unsigned int defaultTimeBetweenClicks = 200;
	unsigned int timeBetweenClicks;

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
