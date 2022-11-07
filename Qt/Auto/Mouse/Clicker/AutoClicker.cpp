#include "AutoClicker.h"
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
#include "../../../Utilities/utils.h"

AutoClicker::AutoClicker(const std::string& mainConfigFolder, QWidget* parent)
	: QWidget(parent), clickHoldTime(defaultClickHoldTime), invalidClickHoldTime(),
	timeBetweenClicks(defaultTimeBetweenClicks), invalidTimeBetweenClicks(),
	leftClick(), CONFIGS_PATH(mainConfigFolder + '/' + "AutoClicker")
{
	emile::ensureFolderExists(CONFIGS_PATH);
	intValidator = new QIntValidator;
	intValidator->setBottom(0);

	QHBoxLayout* centralLayout{ new QHBoxLayout };
	QGroupBox* parameters = initParameters();
	//QHBoxLayout * bottomLayout = initBottomLayout();
	centralLayout->addWidget(parameters);
	//centralLayout->addLayout(bottomLayout);
	setLayout(centralLayout);
	ui.setupUi(this);
}

AutoClicker::~AutoClicker()
{}

QGroupBox* AutoClicker::initParameters()
{
	QGroupBox* parameters{ new QGroupBox("Parameters") };
	QVBoxLayout* parametersLayout{ new QVBoxLayout };

	QHBoxLayout* clickHoldTimeLayout = initClickHoldTime();
	QHBoxLayout* timeBetweenClicksLayout = initTimeBetweenClicks();
	QHBoxLayout* clickButtonLayout = initClickButton();
	QHBoxLayout* saveAndLoadLayout = initSaveAndLoad();

	parametersLayout->addLayout(clickHoldTimeLayout);
	parametersLayout->addLayout(timeBetweenClicksLayout);
	parametersLayout->addLayout(clickButtonLayout);
	parametersLayout->addLayout(saveAndLoadLayout);
	
	parameters->setLayout(parametersLayout);
	return parameters;
}

QHBoxLayout* AutoClicker::initClickHoldTime()
{
	QHBoxLayout* clickHoldTimeLayout{ new QHBoxLayout };
	clickHoldTimeLayout->addWidget(new QLabel("Click hold time > 0 :"));
	clickHoldTimeEdit = new QLineEdit;
	clickHoldTimeEdit->setValidator(intValidator);
	clickHoldTimeEdit->setText(QString::number(defaultClickHoldTime));
	connect(clickHoldTimeEdit, &QLineEdit::textEdited, [this](const QString& text) {
		clickHoldTime = text.toUInt();
		if (clickHoldTime == 0)
		{
			if (std::atoi(text.toStdString().c_str()) > 0)
			{
				clickHoldTimeEdit->setText(QString::number(UINT_MAX));
				clickHoldTime = UINT_MAX;
			}
			else
				clickHoldTimeEdit->setStyleSheet("QLineEdit { background: rgb(255, 0, 0); }");
			invalidClickHoldTime = true;
		}
		else
		{
			clickHoldTimeEdit->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); }");
			invalidClickHoldTime = false;
		}
	});
	clickHoldTimeLayout->addWidget(clickHoldTimeEdit);
	clickHoldTimeLayout->addWidget(new QLabel("ms"));
	return clickHoldTimeLayout;
}

QHBoxLayout* AutoClicker::initTimeBetweenClicks()
{
	QHBoxLayout* timeBetweenClickLayout{ new QHBoxLayout };
	timeBetweenClickLayout->addWidget(new QLabel("Clicks interval :"));
	timeBetweenClicksEdit = new QLineEdit;
	timeBetweenClicksEdit->setValidator(intValidator);
	timeBetweenClicksEdit->setText(QString::number(defaultTimeBetweenClicks));
	connect(timeBetweenClicksEdit, &QLineEdit::textEdited, [this](const QString& text) {
		timeBetweenClicks = text.toUInt();
		if (timeBetweenClicks == 0)
		{
			timeBetweenClicksEdit->setStyleSheet("QLineEdit { background: rgb(255, 0, 0); }");
			invalidTimeBetweenClicks = true;
		}
		else
		{
			timeBetweenClicksEdit->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); }");
			invalidTimeBetweenClicks = false;
		}
	});
	timeBetweenClickLayout->addWidget(timeBetweenClicksEdit);
	timeBetweenClickLayout->addWidget(new QLabel("ms"));
	return timeBetweenClickLayout;
}

QHBoxLayout* AutoClicker::initClickButton()
{
	QHBoxLayout* clickButtonLayout{ new QHBoxLayout };
	clickButtonLayout->setAlignment(Qt::AlignLeft);
	clickButtonLayout->addWidget(new QLabel("Mouse button"));

	clickButtonGroup = new QButtonGroup;
	QRadioButton* leftClickButton{ new QRadioButton("Left") };
	leftClickButton->click();
	QRadioButton* rightClickButton{ new QRadioButton("Right") };
	clickButtonGroup->addButton(leftClickButton);
	clickButtonGroup->addButton(rightClickButton);
	connect(clickButtonGroup, &QButtonGroup::buttonClicked, [this, leftClickButton](QAbstractButton* button) {
		leftClick = (button == leftClickButton) ? false : true;
	});

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

	QPushButton* saveButton{ new QPushButton("Save") };
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

	QPushButton* loadButton{ new QPushButton("Load") };
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
			clickButtonGroup->buttons()[leftClick]->click();
		}
	});
	saveAndLoadLayout->addWidget(saveButton);
	saveAndLoadLayout->addWidget(loadButton);
	return saveAndLoadLayout;
}
