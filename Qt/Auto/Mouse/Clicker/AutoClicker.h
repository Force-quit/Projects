#pragma once

#include <QWidget>
#include "ui_AutoClicker.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QPushButton>
#include <QRadioButton>
#include <string>
#include <vector>
#include "../../QSmartLineEdit.h"

class AutoClicker : public QWidget
{
	Q_OBJECT

public:
	AutoClicker(const std::string& mainConfigFolder, QWidget* parent = nullptr);
	~AutoClicker();
private:
	Ui::AutoClickerClass ui;
	const std::string CONFIGS_PATH; // Defined in constructor
	static const unsigned int defaultClickHoldTime = 50;
	static const unsigned int defaultTimeBetweenClicks = 200;
	static const char DEFAULT_START_CHARACTER = 'X';

	unsigned int clickHoldTime;
	unsigned int timeBetweenClicks;
	bool leftClick;

	QIntValidator* intValidator;
	QSmartLineEdit* clickHoldTimeEdit;
	QSmartLineEdit* timeBetweenClicksEdit;
	QRadioButton* leftClickButton;
	QRadioButton* rightClickButton;
	QPushButton* saveButton;
	QPushButton* loadButton;

	QGroupBox* initParameters();
	QHBoxLayout* initClickHoldTime();
	QHBoxLayout* initTimeBetweenClicks();
	QHBoxLayout* initClickButton();
	QHBoxLayout* initSaveAndLoad();

	QGroupBox* initBottomLayout();
	QHBoxLayout* initActivationHintLayout();

	bool keepLookingForInputs;
	void autoClickerThreadFunction();
};
