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
#include <unordered_map>


class AutoClicker : public QWidget
{
	Q_OBJECT

public:
	AutoClicker(QWidget* parent, const std::string& mainConfigFolder, const std::unordered_map<int, std::string>& VIRTUAL_KEYS);
	~AutoClicker();

private:
	Ui::AutoClickerClass ui;

	static const unsigned int defaultClickHoldTime = 50;
	static const unsigned int defaultTimeBetweenClicks = 200;
	static const char DEFAULT_START_CHARACTER = 'X';
	const std::string CONFIGS_PATH; // Defined in constructor

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

	QGroupBox* initActivationLayout();
	QHBoxLayout* initActivationHintLayout();

	void autoClickerThreadFunction();
};
