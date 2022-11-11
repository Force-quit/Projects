#pragma once

#include <QWidget>
#include "ui_AutoClicker.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include <vector>
#include "../../QSmartLineEdit.h"
#include <unordered_map>
#include <thread>

class AutoClicker : public QWidget
{
	Q_OBJECT

public:
	AutoClicker(QWidget* parent);
	~AutoClicker();

private:
	Ui::AutoClickerClass ui;

	static const unsigned int defaultClickHoldTime{ 50 };
	static const unsigned int defaultTimeBetweenClicks{ 200 };
	static const QString CONFIGS_PATH;

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
