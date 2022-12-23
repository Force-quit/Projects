#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include "EQAutoClickerWorker.h"
#include <QThread>
#include "../../Utilities/EQUIRangedLineEdit.h"
#include "../../Utilities/EQShortcutListener/EQShortcutListener.h"
#include <QRadioButton>
#include <QPushButton>
#include <QVector>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>

class EQAutoClicker : public QMainWindow
{
	Q_OBJECT

public:
	EQAutoClicker(QWidget *parent = nullptr);
	~EQAutoClicker();

private slots:
	void disableWidgets();
	void enableWidgets();
	void saveConfiguration();
	void loadConfiguration();

private:
	static const QString CONFIGS_PATH;

	EQAutoClickerWorker* worker;
	QThread workerThread;


	EQShortcutListener* shortcutListener;
	EQUIRangedLineEdit* clickHoldTimeEdit;
	EQUIRangedLineEdit* timeBetweenClicksEdit;
	QRadioButton* leftClickButton;
	QRadioButton* rightClickButton;
	QPushButton* saveButton;
	QPushButton* loadButton;
	QLabel* configurationText;
	QVector<QWidget*> widgetsToDisable;

	QGroupBox* initParameters();
	QHBoxLayout* initClickHoldTime();
	QHBoxLayout* initTimeBetweenClicks();
	QHBoxLayout* initClickButton();
	QHBoxLayout* initSaveAndLoad();

	QGroupBox* initActivationLayout();

};
