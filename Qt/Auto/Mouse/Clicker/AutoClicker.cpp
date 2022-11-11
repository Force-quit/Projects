#include "AutoClicker.h"
#include "../../QSmartLineEdit.h"
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

const QString AutoClicker::CONFIGS_PATH{ AutoUtils::ROOT_CONFIG_PATH + "/AutoClicker" };

AutoClicker::AutoClicker(QWidget* parent)
	: QWidget(parent),
	clickHoldTime(defaultClickHoldTime), timeBetweenClicks(defaultTimeBetweenClicks), leftClick(),
	intValidator(), clickHoldTimeEdit(), timeBetweenClicksEdit(), leftClickButton(), rightClickButton(),
	saveButton(), loadButton()
{
	ui.setupUi(this);
	QDir().mkdir(AutoClicker::CONFIGS_PATH);
	intValidator = new QIntValidator;
	intValidator->setBottom(0);

	auto* centralLayout{ new QVBoxLayout };
	centralLayout->addWidget(initParameters());
	centralLayout->addWidget(initActivationLayout());
	centralLayout->addLayout(initSaveAndLoad());
	setLayout(centralLayout);
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
	clickHoldTimeEdit = new QSmartLineEdit;
	clickHoldTimeEdit->setValidator(intValidator);
	clickHoldTimeEdit->setText(QString::number(defaultClickHoldTime));

	QHBoxLayout* clickHoldTimeLayout{ new QHBoxLayout };
	clickHoldTimeLayout->addWidget(new QLabel("Click hold time :"));
	clickHoldTimeLayout->addWidget(clickHoldTimeEdit);
	clickHoldTimeLayout->addWidget(new QLabel("ms"));

	connect(clickHoldTimeEdit, &QSmartLineEdit::smartFocusOutEvent, [this](const QString& text) {
		auto temp{ text.toULongLong() };
		if (temp > UINT_MAX)
		{
			clickHoldTime = UINT_MAX;
			clickHoldTimeEdit->setText(QString::number(clickHoldTime));
		}
		else if (temp <= 0)
		{
			clickHoldTime = 1;
			clickHoldTimeEdit->setText(QString::number(clickHoldTime));
		}
		else
			clickHoldTime = temp;
	});

	return clickHoldTimeLayout;
}

QHBoxLayout* AutoClicker::initTimeBetweenClicks()
{
	timeBetweenClicksEdit = new QSmartLineEdit;
	timeBetweenClicksEdit->setValidator(intValidator);
	timeBetweenClicksEdit->setText(QString::number(defaultTimeBetweenClicks));

	QHBoxLayout* timeBetweenClickLayout{ new QHBoxLayout };
	timeBetweenClickLayout->addWidget(new QLabel("Clicks interval :"));
	timeBetweenClickLayout->addWidget(timeBetweenClicksEdit);
	timeBetweenClickLayout->addWidget(new QLabel("ms"));

	connect(timeBetweenClicksEdit, &QSmartLineEdit::smartFocusOutEvent, [this](const QString& text) {
		auto temp{ text.toULongLong() };
		if (temp > UINT_MAX)
		{
			timeBetweenClicks = UINT_MAX;
			timeBetweenClicksEdit->setText(QString::number(timeBetweenClicks));
		}
		else if (temp <= 0)
		{
			timeBetweenClicks = 1;
			timeBetweenClicksEdit->setText(QString::number(timeBetweenClicks));
		}
		else
			timeBetweenClicks = temp;
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

	QLabel* saveFileLabel{ new QLabel("Current configuration :") };
	QLabel* saveFileName{ new QLabel("Unsaved") };
	saveButton = new QPushButton("Save");
	loadButton = new QPushButton("Load");
	saveAndLoadLayout->addWidget(saveFileLabel);
	saveAndLoadLayout->addWidget(saveFileName);
	saveAndLoadLayout->addWidget(saveButton);
	saveAndLoadLayout->addWidget(loadButton);

	connect(saveButton, &QPushButton::clicked, [this, saveFileName](bool checked = false) {
		QString filePath = QFileDialog::getSaveFileName(this, "Save your AutoClicker configuration", CONFIGS_PATH, "text files (*.txt)");

		if (!filePath.isEmpty())
		{
			QFile file(filePath);
			if (file.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&file);
				out << clickHoldTime << ',' << timeBetweenClicks << ',' << leftClick;
				saveFileName->setText(CONFIGS_PATH + filePath.mid(filePath.lastIndexOf("/")));
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
	});
	
	connect(loadButton, &QPushButton::clicked, [this, saveFileName]() {
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
				
				saveFileName->setText(CONFIGS_PATH + filePath.mid(filePath.lastIndexOf("/")));
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
	});

	return saveAndLoadLayout;
}

QGroupBox* AutoClicker::initActivationLayout()
{
	QGroupBox* bottomGroupBox{ new QGroupBox("Activation") };
	QVBoxLayout* bottomLayout{ new QVBoxLayout };
	bottomLayout->addLayout(initActivationHintLayout());
	bottomGroupBox->setLayout(bottomLayout);
	return bottomGroupBox;
}

QHBoxLayout* AutoClicker::initActivationHintLayout()
{
	QHBoxLayout* activationHintLayout{ new QHBoxLayout };
	QLabel* activationShortcut{ new QLabel(AutoUtils::DEFAULT_ACTIVATION_KEY) };
	activationShortcut->setAlignment(Qt::AlignCenter);
	QPushButton* changeActivationShortcut{ new QPushButton("Change") };

	activationHintLayout->addWidget(new QLabel("Activation shortcut :"));
	activationHintLayout->addWidget(activationShortcut);
	activationHintLayout->addWidget(changeActivationShortcut);

	QTabWidget* tabWidget{ dynamic_cast<QTabWidget*>(parent()) };

	connect(changeActivationShortcut, &QPushButton::clicked, [this, activationShortcut, changeActivationShortcut, tabWidget]() {
		clickHoldTimeEdit->setEnabled(false);
		timeBetweenClicksEdit->setEnabled(false);
		leftClickButton->setEnabled(false);
		rightClickButton->setEnabled(false);
		saveButton->setEnabled(false);
		loadButton->setEnabled(false);
		changeActivationShortcut->setText("Press and hold");
		changeActivationShortcut->setEnabled(false);

		for (int i = 0; i < tabWidget->count(); ++i)
			if (i != tabWidget->currentIndex())
				tabWidget->setTabVisible(i, false);

		/*std::vector<int> pressedKeys;
		do
		{

			for (auto& i : AutoUtils::VIRTUAL_KEYS)
			{
				if (GetAsyncKeyState(i.first))
				{
					activationShortcut->setText(i.second);
				}
			}
		} while (true);*/
		
	});
	return activationHintLayout;
}

AutoClicker::~AutoClicker() {}