#pragma once

#include <QWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include <QTabWidget>
#include <QLabel>
#include <vector>
#include "../../../../Utilities/EQUIRangedLineEdit.h"
#include <unordered_map>
#include <QThread>

class AutoClicker : public QWidget
{
	Q_OBJECT

public:
	AutoClicker(QWidget* parent);
	~AutoClicker();

private:
	QThread workerThread;

	static const unsigned int defaultClickHoldTime{ 50 };
	static const unsigned int defaultTimeBetweenClicks{ 200 };
	static const QString CONFIGS_PATH;

	unsigned int clickHoldTime;
	unsigned int timeBetweenClicks;
	bool leftClick;

	EQUIRangedLineEdit* clickHoldTimeEdit;
	EQUIRangedLineEdit* timeBetweenClicksEdit;
	QRadioButton* leftClickButton;
	QRadioButton* rightClickButton;
	QPushButton* saveButton;
	QPushButton* loadButton;
	QPushButton* changeShortcutButton;
	QTabWidget* parent;

	QGroupBox* initParameters();
	QHBoxLayout* initClickHoldTime();
	QHBoxLayout* initTimeBetweenClicks();
	QHBoxLayout* initClickButton();
	QHBoxLayout* initSaveAndLoad();

	QGroupBox* initActivationLayout();
	QHBoxLayout* initActivationShortcutLayout();


	void autoClickerThreadFunction();

	void saveConfiguration(QLabel& saveFileLabel);
	void loadConfiguration(QLabel& saveFileLabel);
private slots:

	void beginLookingForInputs();
	void stopLookingForInputs();

};