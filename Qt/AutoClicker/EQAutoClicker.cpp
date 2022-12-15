#include "EQAutoClicker.h"
#include "../../Utilities/EQUIRangedLineEdit.h"
#include <QFile>
#include <QBoxLayout>
#include <QGroupBox>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFileDialog>
#include <QMessageBox>
#include "../../../../Utilities/EQTabWidget.h"
#include <QTabBar>
#include <QDir>
#include <QFocusEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <Windows.h>
#include <vector>

const QString EQAutoClicker::CONFIGS_PATH{ "Configs" };

EQAutoClicker::EQAutoClicker(QWidget *parent)
	: QMainWindow(parent),
	clickHoldTime(DEFAULT_CLICK_HOLD_TIME), timeBetweenClicks(DEFAULT_BETWEEN_TIME), leftClick(),
	clickHoldTimeEdit(), timeBetweenClicksEdit(), leftClickButton(), rightClickButton(),
	saveButton(), loadButton(), changeShortcutButton(), widgetsToDisable()
{
	
}

QGroupBox* EQAutoClicker::initParameters()
{
	QGroupBox* parameters{ new QGroupBox("Parameters") };
	QVBoxLayout* parametersLayout{ new QVBoxLayout };

	QHBoxLayout* clickHoldTimeLayout = initClickHoldTime();
	QHBoxLayout* timeBetweenClicksLayout = initTimeBetweenClicks();
	QHBoxLayout* clickButtonLayout = initClickButton();

	parametersLayout->addLayout(clickHoldTimeLayout);
	parametersLayout->addLayout(timeBetweenClicksLayout);
	parametersLayout->addLayout(clickButtonLayout);

	parameters->setLayout(parametersLayout);
	return parameters;
}

QHBoxLayout* EQAutoClicker::initClickHoldTime()
{
	clickHoldTimeEdit = new EQUIRangedLineEdit(1, UINT_MAX);
	clickHoldTimeEdit->setText(QString::number(defaultClickHoldTime));

	QHBoxLayout* clickHoldTimeLayout{ new QHBoxLayout };
	clickHoldTimeLayout->addWidget(new QLabel("Click hold time :"));
	clickHoldTimeLayout->addWidget(clickHoldTimeEdit);
	clickHoldTimeLayout->addWidget(new QLabel("ms"));

	connect(clickHoldTimeEdit, &EQUIRangedLineEdit::valueValidated, [this](unsigned int value) {
		clickHoldTime = value;
		});

	return clickHoldTimeLayout;
}

QHBoxLayout* EQAutoClicker::initTimeBetweenClicks()
{
	timeBetweenClicksEdit = new EQUIRangedLineEdit(1, UINT_MAX);
	timeBetweenClicksEdit->setText(QString::number(defaultTimeBetweenClicks));

	QHBoxLayout* timeBetweenClickLayout{ new QHBoxLayout };
	timeBetweenClickLayout->addWidget(new QLabel("Clicks interval :"));
	timeBetweenClickLayout->addWidget(timeBetweenClicksEdit);
	timeBetweenClickLayout->addWidget(new QLabel("ms"));

	connect(timeBetweenClicksEdit, &EQUIRangedLineEdit::valueValidated, [this](unsigned int value) {
		timeBetweenClicks = value;
		});

	return timeBetweenClickLayout;
}

QHBoxLayout* EQAutoClicker::initClickButton()
{
	leftClickButton = new QRadioButton("Left");
	leftClickButton->click();
	rightClickButton = new QRadioButton("Right");

	QButtonGroup* clickButtonGroup{ new QButtonGroup };
	clickButtonGroup->addButton(leftClickButton);
	clickButtonGroup->addButton(rightClickButton);

	connect(clickButtonGroup, &QButtonGroup::buttonClicked, [this](QAbstractButton* button) {
		if (button == leftClickButton)
			leftClick = true;
		else
			leftClick = false;
		});

	QHBoxLayout* clickButtonLayout{ new QHBoxLayout };
	clickButtonLayout->setAlignment(Qt::AlignLeft);
	clickButtonLayout->addWidget(new QLabel("Mouse button"));
	clickButtonLayout->addWidget(leftClickButton);
	clickButtonLayout->addWidget(rightClickButton);

	return clickButtonLayout;
}

QHBoxLayout* EQAutoClicker::initSaveAndLoad()
{
	QHBoxLayout* saveAndLoadLayout{ new QHBoxLayout };

	QLabel* sectionLabel{ new QLabel("Current configuration :") };
	QLabel* saveFileLabel{ new QLabel("Unsaved") };
	saveButton = new QPushButton("Save");
	loadButton = new QPushButton("Load");
	saveAndLoadLayout->addWidget(sectionLabel);
	saveAndLoadLayout->addWidget(saveFileLabel);
	saveAndLoadLayout->addWidget(saveButton);
	saveAndLoadLayout->addWidget(loadButton);

	connect(saveButton, &QPushButton::clicked, [this, saveFileLabel]() { saveConfiguration(*saveFileLabel); });
	connect(loadButton, &QPushButton::clicked, [this, saveFileLabel]() { loadConfiguration(*saveFileLabel); });

	return saveAndLoadLayout;
}

QGroupBox* EQAutoClicker::initActivationLayout()
{
	QGroupBox* bottomGroupBox{ new QGroupBox("Activation") };
	QVBoxLayout* bottomLayout{ new QVBoxLayout };
	bottomLayout->addLayout(initActivationShortcutLayout());
	bottomGroupBox->setLayout(bottomLayout);
	return bottomGroupBox;
}

QHBoxLayout* EQAutoClicker::initActivationShortcutLayout()
{
	QHBoxLayout* activationHintLayout{ new QHBoxLayout };
	QLabel* activationShortcut{ new QLabel(AutoUtils::DEFAULT_ACTIVATION_KEY) };
	activationShortcut->setAlignment(Qt::AlignCenter);
	changeShortcutButton = new QPushButton("Change");

	activationHintLayout->addWidget(new QLabel("Activation shortcut :"));
	activationHintLayout->addWidget(activationShortcut);
	activationHintLayout->addWidget(changeShortcutButton);

	QtShortcutPicker* worker{ new QtShortcutPicker };
	worker->moveToThread(&workerThread);
	connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
	connect(worker, &QtShortcutPicker::shortcutChanged, activationShortcut, &QLabel::setText);
	connect(changeShortcutButton, &QPushButton::clicked, this, &AutoClicker::beginLookingForInputs);
	connect(changeShortcutButton, &QPushButton::clicked, worker, &QtShortcutPicker::listenForInput);
	connect(worker, &QtShortcutPicker::shortcutChosen, this, &AutoClicker::stopLookingForInputs);

	workerThread.start();
	return activationHintLayout;
}

void EQAutoClicker::saveConfiguration(QLabel& saveFileLabel)
{
	QString filePath = QFileDialog::getSaveFileName(this, "Save your AutoClicker configuration", CONFIGS_PATH, "text files (*.txt)");

	if (!filePath.isEmpty())
	{
		QFile file(filePath);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			QTextStream out(&file);
			out << clickHoldTime << ',' << timeBetweenClicks << ',' << leftClick;
			saveFileLabel.setText(CONFIGS_PATH + filePath.mid(filePath.lastIndexOf("/")));
		}
		else
		{
			QMessageBox msgBox;
			msgBox.setText("File error");
			msgBox.setInformativeText("Error writing to file");
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setDefaultButton(QMessageBox::Ok);
			msgBox.exec();
		}

		file.close();
	}
}

void EQAutoClicker::loadConfiguration(QLabel& saveFileLabel)
{
	QString filePath = QFileDialog::getOpenFileName(this, "Load your AutoClicker configuration", CONFIGS_PATH, "text files (*.txt)");

	if (!filePath.isEmpty())
	{
		QFile file(filePath);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QByteArray line{ file.readLine() };
			auto test{ line.split(',') };
			clickHoldTime = test[0].toUInt();
			timeBetweenClicks = test[1].toUInt();
			leftClick = test[2].toShort();

			saveFileLabel.setText(CONFIGS_PATH + filePath.mid(filePath.lastIndexOf("/")));
			clickHoldTimeEdit->setText(QString::number(clickHoldTime));
			timeBetweenClicksEdit->setText(QString::number(timeBetweenClicks));
			if (leftClick)
				leftClickButton->click();
			else
				rightClickButton->click();
		}
		else
		{
			QMessageBox msgBox;
			msgBox.setText("File error");
			msgBox.setInformativeText("Error reading file");
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.setDefaultButton(QMessageBox::Ok);
			msgBox.exec();
		}
		file.close();
	}
}

EQAutoClicker::~EQAutoClicker() 
{
	workerThread.quit();
	workerThread.wait();
}