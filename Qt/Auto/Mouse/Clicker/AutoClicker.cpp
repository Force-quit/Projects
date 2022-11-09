#include "AutoClicker.h"
#include "../../QSmartLineEdit.h"
#include <fstream>
#include <string>
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

AutoClicker::AutoClicker(const std::string& mainConfigFolder, QWidget* parent)
	: QWidget(parent), clickHoldTime(defaultClickHoldTime), clickHoldTimeEdit(),
	timeBetweenClicks(defaultTimeBetweenClicks),
	leftClick(), CONFIGS_PATH(mainConfigFolder + '/' + "AutoClicker")
{
	QDir().mkdir(QString::fromStdString(CONFIGS_PATH));
	intValidator = new QIntValidator;
	intValidator->setBottom(0);

	auto* centralLayout{ new QVBoxLayout };
	centralLayout->addWidget(initParameters());
	centralLayout->addWidget(initBottomLayout());
	centralLayout->addLayout(initSaveAndLoad());
	setLayout(centralLayout);
	ui.setupUi(this);
}

AutoClicker::~AutoClicker(){}

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
		auto temp{ text.toULongLong()};
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
	saveAndLoadLayout->addWidget(saveFileLabel);
	saveAndLoadLayout->addWidget(saveFileName);

	saveButton = new QPushButton("Save");
	connect(saveButton, &QPushButton::clicked, [this, saveFileName]() {

		QString filePath = QString::fromStdString("./" + CONFIGS_PATH);
		filePath = QFileDialog::getSaveFileName(this, "Save your AutoClicker configuration", filePath, "text files (*.txt)");

		if (!filePath.isEmpty())
		{
			std::ofstream file(filePath.toStdString());
			if (!file.good())
			{
				QMessageBox msgBox;
				msgBox.setText("File error");
				msgBox.setInformativeText("Error saving file");
				msgBox.setStandardButtons(QMessageBox::Ok);
				msgBox.setDefaultButton(QMessageBox::Ok);
				msgBox.exec();
			}
			else
				file << clickHoldTime << ',' << timeBetweenClicks << ',' << leftClick;
			file.close();

			QString fileName = QString::fromStdString(CONFIGS_PATH + filePath.mid(filePath.lastIndexOf("/")).toStdString());
			saveFileName->setText(fileName);
		}
	});

	loadButton = new QPushButton("Load");
	connect(loadButton, &QPushButton::clicked, [this, saveFileName]() {

		QString filePath = QString::fromStdString("./" + CONFIGS_PATH);
		filePath = QFileDialog::getOpenFileName(this, "Load your AutoClicker configuration", filePath, "text files (*.txt)");

		if (!filePath.isEmpty())
		{
			std::ifstream file(filePath.toStdString());
			if (!file.good())
			{
				QMessageBox msgBox;
				msgBox.setText("File error");
				msgBox.setInformativeText("Error loading file");
				msgBox.setStandardButtons(QMessageBox::Ok);
				msgBox.setDefaultButton(QMessageBox::Ok);
				msgBox.exec();
			}
			else
			{
				char sep;
				file >> clickHoldTime >> sep >> timeBetweenClicks >> sep >> leftClick;
			}
			file.close();

			QString fileName = QString::fromStdString(CONFIGS_PATH + filePath.mid(filePath.lastIndexOf("/")).toStdString());
			saveFileName->setText(fileName);
			clickHoldTimeEdit->clear();
			clickHoldTimeEdit->insert(QString::number(clickHoldTime));
			timeBetweenClicksEdit->clear();
			timeBetweenClicksEdit->insert(QString::number(timeBetweenClicks));
			if (leftClick)
				leftClickButton->click();
			else
				rightClickButton->click();
		}
	});
	saveAndLoadLayout->addWidget(saveButton);
	saveAndLoadLayout->addWidget(loadButton);
	return saveAndLoadLayout;
}

QGroupBox* AutoClicker::initBottomLayout() 
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
	QLabel* activationShortcut{ new QLabel(QString(DEFAULT_START_CHARACTER)) };
	QPushButton* changeActivationShortcut{ new QPushButton("Change") };

	activationHintLayout->addWidget(new QLabel("Activation shortcut :"));
	activationHintLayout->addWidget(activationShortcut);
	activationHintLayout->addWidget(changeActivationShortcut);
	
	QTabWidget* tabWidget{ dynamic_cast<QTabWidget*>(parent()) };

	connect(changeActivationShortcut, &QPushButton::clicked, [this, changeActivationShortcut, tabWidget]() {
		clickHoldTimeEdit->setEnabled(false);
		timeBetweenClicksEdit->setEnabled(false);
		leftClickButton->setEnabled(false);
		rightClickButton->setEnabled(false);
		saveButton->setEnabled(false);
		loadButton->setEnabled(false);
		changeActivationShortcut->setText("Listening...");
		changeActivationShortcut->setEnabled(false);

		for (int i = 0; i < tabWidget->count(); ++i)
			if (i != tabWidget->currentIndex())
				tabWidget->setTabVisible(i, false);

	});
	return activationHintLayout;
}