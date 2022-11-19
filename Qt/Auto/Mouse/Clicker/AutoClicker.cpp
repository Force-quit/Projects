#include "AutoClicker.h"
#include "../../../../Utilities/EQUIRangedLineEdit.h"
#include "../../AutoUtils.h"
#include <string>
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
#include <QTabWidget>
#include <QTabBar>
#include <QDir>
#include <QFocusEvent>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <Windows.h>
#include <vector>
#include "../../QtShortcutPicker.h"

const QString AutoClicker::CONFIGS_PATH{ AutoUtils::ROOT_CONFIG_PATH + "/AutoClicker" };

AutoClicker::AutoClicker(QWidget* parent)
	: QWidget(parent),
	clickHoldTime(defaultClickHoldTime), timeBetweenClicks(defaultTimeBetweenClicks), leftClick(),
	clickHoldTimeEdit(), timeBetweenClicksEdit(), leftClickButton(), rightClickButton(),
	saveButton(), loadButton(), changeShortcutButton(), parent()
{
	QDir().mkdir(AutoClicker::CONFIGS_PATH);
	this->parent = dynamic_cast<QTabWidget*>(parent);

	auto* centralLayout{ new QVBoxLayout };
	centralLayout->addWidget(initParameters());
	centralLayout->addWidget(initActivationLayout());
	centralLayout->addLayout(initSaveAndLoad());
	setLayout(centralLayout);
}

AutoClicker::~AutoClicker()
{
	workerThread.quit();
	workerThread.wait();
}

QGroupBox* AutoClicker::initParameters()
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

QHBoxLayout* AutoClicker::initClickHoldTime()
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

QHBoxLayout* AutoClicker::initTimeBetweenClicks()
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

QHBoxLayout* AutoClicker::initClickButton()
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

QHBoxLayout* AutoClicker::initSaveAndLoad()
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

QGroupBox* AutoClicker::initActivationLayout()
{
	QGroupBox* bottomGroupBox{ new QGroupBox("Activation") };
	QVBoxLayout* bottomLayout{ new QVBoxLayout };
	bottomLayout->addLayout(initActivationShortcutLayout());
	bottomGroupBox->setLayout(bottomLayout);
	return bottomGroupBox;
}

QHBoxLayout* AutoClicker::initActivationShortcutLayout()
{
	QHBoxLayout* activationHintLayout{ new QHBoxLayout };
	QLabel* activationShortcut{ new QLabel(AutoUtils::DEFAULT_ACTIVATION_KEY) };
	activationShortcut->setAlignment(Qt::AlignCenter);
	changeShortcutButton = new QPushButton("Change") ;

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

void AutoClicker::saveConfiguration(QLabel& saveFileLabel)
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

void AutoClicker::loadConfiguration(QLabel& saveFileLabel)
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

/*
	 _______    ___        _______    _______    _______ 
	|       |  |   |      |       |  |       |  |       |
	|  _____|  |   |      |   _   |  |_     _|  |  _____|
	| |_____   |   |      |  | |  |    |   |    | |_____ 
	|_____  |  |   |___   |  |_|  |    |   |    |_____  |
	 _____| |  |       |  |       |    |   |     _____| |
	|_______|  |_______|  |_______|    |___|    |_______|

*/

void AutoClicker::beginLookingForInputs()
{
	clickHoldTimeEdit->setEnabled(false);
	timeBetweenClicksEdit->setEnabled(false);
	leftClickButton->setEnabled(false);
	rightClickButton->setEnabled(false);
	saveButton->setEnabled(false);
	loadButton->setEnabled(false);
	changeShortcutButton->setText("Press and hold");
	changeShortcutButton->setEnabled(false);

	for (int i = 0; i < parent->count(); ++i)
		if (i != parent->currentIndex())
			parent->setTabVisible(i, false);
}

void AutoClicker::stopLookingForInputs()
{
	clickHoldTimeEdit->setEnabled(true);
	timeBetweenClicksEdit->setEnabled(true);
	leftClickButton->setEnabled(true);
	rightClickButton->setEnabled(true);
	saveButton->setEnabled(true);
	loadButton->setEnabled(true);
	changeShortcutButton->setText("Change");
	changeShortcutButton->setEnabled(true);

	for (int i = 0; i < parent->count(); ++i)
		if (i != parent->currentIndex())
			parent->setTabVisible(i, true);
}