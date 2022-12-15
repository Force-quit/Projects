#pragma once

#include <QMainWindow>
#include <QGroupBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include <QLabel>
#include <vector>
#include "../../Utilities/EQUIRangedLineEdit.h"
#include <unordered_map>
#include <QThread>
#include <QVector>

class EQAutoClicker : public QMainWindow
{
	Q_OBJECT

public:
	EQAutoClicker(QWidget *parent = nullptr);
	~EQAutoClicker();

private:
	static const QString CONFIGS_PATH;

	static const unsigned int MIN_TIME{ 1 };
	static const unsigned int DEFAULT_CLICK_HOLD_TIME{ 50 };
	static const unsigned int DEFAULT_BETWEEN_TIME{ 200 };

	QThread workerThread;

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
	QVector<QWidget*> widgetsToDisable;

	QGroupBox* initParameters();
	QHBoxLayout* initClickHoldTime();
	QHBoxLayout* initTimeBetweenClicks();
	QHBoxLayout* initClickButton();
	QHBoxLayout* initSaveAndLoad();

	QGroupBox* initActivationLayout();
	QHBoxLayout* initActivationShortcutLayout();




	void saveConfiguration(QLabel& saveFileLabel);
	void loadConfiguration(QLabel& saveFileLabel);
};
