#include "EQAutoClicker.h"
#include "EQAutoClickerWorker.h"
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
#include "../../Utilities/Qt/EQShortcutListener/EQShortcutListener.h"
#include "../../Utilities/Qt/EQIntLineEdit/EQIntLineEdit.h"
#include <QTabBar>
#include <QDir>
#include <QFocusEvent>
#include <Windows.h>
#include <QIcon>
#include <QVector>

const QString EQAutoClicker::CONFIGS_PATH{ "Configs" };

EQAutoClicker::EQAutoClicker(QWidget* parent)
	: QMainWindow(parent),
	clickHoldTimeEdit(), timeBetweenClicksEdit(), leftClickButton(), rightClickButton(),
	saveButton(), loadButton(), widgetsToDisable(), worker(), configurationText(), shortcutListener(), activationStatusText()
{
	QDir().mkdir(CONFIGS_PATH);
	worker = new EQAutoClickerWorker;

	QVBoxLayout* centralLayout{ new QVBoxLayout };
	centralLayout->addWidget(initParameters());
	centralLayout->addWidget(initActivationLayout());

	QWidget* centralWidget{ new QWidget };
	centralWidget->setLayout(centralLayout);
	setCentralWidget(centralWidget);
	setWindowIcon(QIcon("mouse.png"));
	setWindowTitle("AutoClicker(v1.2)");

	widgetsToDisable.append({ clickHoldTimeEdit, timeBetweenClicksEdit,
		leftClickButton, rightClickButton, saveButton, loadButton });

	shortcutListener->startListening();
}

QGroupBox* EQAutoClicker::initParameters()
{
	QGroupBox* parameters{ new QGroupBox("Parameters") };
	QVBoxLayout* parametersLayout{ new QVBoxLayout };
	parametersLayout->addLayout(initClickHoldTime());
	parametersLayout->addLayout(initTimeBetweenClicks());
	parametersLayout->addLayout(initClickButton());
	parametersLayout->addLayout(initSaveAndLoad());
	parameters->setLayout(parametersLayout);
	return parameters;
}

QGroupBox* EQAutoClicker::initActivationLayout()
{
	QGroupBox* activationGroupBox{ new QGroupBox("Activation") };
	QVBoxLayout* groupBoxLayout{ new QVBoxLayout };

	shortcutListener = new EQShortcutListener("Activation shortcut :");

	QHBoxLayout* activationStatusLayout{ new QHBoxLayout };
	activationStatusLayout->setAlignment(Qt::AlignCenter);
	QLabel* activationStatusLabel{ new QLabel("Status :") };
	activationStatusText = new QLabel("Innactive");
	activationStatusLayout->addWidget(activationStatusLabel);
	activationStatusLayout->addWidget(activationStatusText);

	groupBoxLayout->addWidget(shortcutListener);
	groupBoxLayout->addLayout(activationStatusLayout);
	activationGroupBox->setLayout(groupBoxLayout);

	connect(shortcutListener, &EQShortcutListener::startedChangingShortcut, this, &EQAutoClicker::disableWidgets);
	connect(shortcutListener, &EQShortcutListener::stoppedChangingShortcut, this, &EQAutoClicker::enableWidgets);
	connect(shortcutListener, &EQShortcutListener::shortcutPressed, worker, &EQAutoClickerWorker::switchState);

	connect(worker, &EQAutoClickerWorker::activated, this, &EQAutoClicker::disableWidgets);
	connect(worker, &EQAutoClickerWorker::deactivated, this, &EQAutoClicker::enableWidgets);

	connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
	worker->moveToThread(&workerThread);
	workerThread.start();

	return activationGroupBox;
}

QHBoxLayout* EQAutoClicker::initClickHoldTime()
{
	QHBoxLayout* clickHoldTimeLayout{ new QHBoxLayout };

	clickHoldTimeLayout->addWidget(new QLabel("Click hold time :"));

	clickHoldTimeEdit = new EQIntLineEdit(EQAutoClickerWorker::MIN_INTERVAL, EQAutoClickerWorker::MAX_INTERVAL);
	clickHoldTimeEdit->setText(QString::number(EQAutoClickerWorker::DEFAULT_HOLD_TIME));
	clickHoldTimeLayout->addWidget(clickHoldTimeEdit);

	clickHoldTimeLayout->addWidget(new QLabel("ms"));

	connect(clickHoldTimeEdit, &EQIntLineEdit::valueChanged, worker, &EQAutoClickerWorker::setClickHoldTime);

	return clickHoldTimeLayout;
}

QHBoxLayout* EQAutoClicker::initTimeBetweenClicks()
{
	QHBoxLayout* timeBetweenClickLayout{ new QHBoxLayout };

	timeBetweenClickLayout->addWidget(new QLabel("Clicks interval :"));

	timeBetweenClicksEdit = new EQIntLineEdit(EQAutoClickerWorker::MIN_INTERVAL, EQAutoClickerWorker::MAX_INTERVAL);
	timeBetweenClicksEdit->setText(QString::number(EQAutoClickerWorker::DEFAULT_BETWEEN_TIME));
	timeBetweenClickLayout->addWidget(timeBetweenClicksEdit);

	timeBetweenClickLayout->addWidget(new QLabel("ms"));

	connect(timeBetweenClicksEdit, &EQIntLineEdit::valueChanged, worker, &EQAutoClickerWorker::setTimeBetweenClicks);

	return timeBetweenClickLayout;
}

QHBoxLayout* EQAutoClicker::initClickButton()
{
	QHBoxLayout* clickButtonLayout{ new QHBoxLayout };
	clickButtonLayout->setAlignment(Qt::AlignLeft);

	clickButtonLayout->addWidget(new QLabel("Mouse button"));

	QButtonGroup* clickButtonGroup{ new QButtonGroup };
	leftClickButton = new QRadioButton("Left");
	leftClickButton->click();
	rightClickButton = new QRadioButton("Right");
	clickButtonGroup->addButton(leftClickButton);
	clickButtonGroup->addButton(rightClickButton);

	clickButtonLayout->addWidget(leftClickButton);
	clickButtonLayout->addWidget(rightClickButton);

	connect(clickButtonGroup, &QButtonGroup::buttonClicked, [this](QAbstractButton* pressedButton) {
		worker->setLeftClick(pressedButton == leftClickButton);
		});

	return clickButtonLayout;
}

QHBoxLayout* EQAutoClicker::initSaveAndLoad()
{
	QHBoxLayout* saveAndLoadLayout{ new QHBoxLayout };

	QLabel* configurationLabel{ new QLabel("Current configuration :") };
	configurationText = new QLabel("Unsaved");
	saveButton = new QPushButton("Save");
	loadButton = new QPushButton("Load");
	saveAndLoadLayout->addWidget(configurationLabel);
	saveAndLoadLayout->addWidget(configurationText);
	saveAndLoadLayout->addWidget(saveButton);
	saveAndLoadLayout->addWidget(loadButton);

	connect(saveButton, &QPushButton::clicked, this, &EQAutoClicker::saveConfiguration);
	connect(loadButton, &QPushButton::clicked, this, &EQAutoClicker::loadConfiguration);

	return saveAndLoadLayout;
}

void EQAutoClicker::disableWidgets()
{
	for (auto i : widgetsToDisable)
		i->setDisabled(true);
	shortcutListener->disableButton();
	if (worker->isActive())
		activationStatusText->setText("Active");
}

void EQAutoClicker::enableWidgets()
{
	for (auto i : widgetsToDisable)
		i->setEnabled(true);
	shortcutListener->enableButton();
	activationStatusText->setText("Innactive");
}

void EQAutoClicker::saveConfiguration()
{
	QString filePath = QFileDialog::getSaveFileName(this, "Save your AutoClicker configuration", CONFIGS_PATH, "text files (*.txt)");

	if (!filePath.isEmpty())
	{
		QFile file(filePath);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			QTextStream out(&file);
			out << worker->getClickHoldTime() << ',' << worker->getTimeBetweenClicks() << ',' << worker->isTargetLeftClick() << '\n';

			QVector<int> shortcutKeys = shortcutListener->getTargetKeys();
			for (int i = 0; i < shortcutKeys.size() - 1; ++i)
				out << i << ',';
			out << shortcutKeys[shortcutKeys.size() - 1];

			configurationText->setText(QDir().relativeFilePath(filePath));
		}
		else
		{
			QMessageBox::critical(this, 
				"File error",
				"Can't open " + filePath + " for writing.",
				QMessageBox::Ok);
		}


		file.close();
	}
}

void EQAutoClicker::loadConfiguration()
{
	QString filePath = QFileDialog::getOpenFileName(this, "Load your AutoClicker configuration", CONFIGS_PATH, "text files (*.txt)");

	if (!filePath.isEmpty())
	{
		QFile file(filePath);
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QByteArrayList valuesList{ file.readLine().split(',') };
			worker->setClickHoldTime(valuesList[0].toUInt());
			worker->setTimeBetweenClicks(valuesList[1].toUInt());

			configurationText->setText(QDir().relativeFilePath(filePath));
			clickHoldTimeEdit->setText(QString::number(worker->getClickHoldTime()));
			timeBetweenClicksEdit->setText(QString::number(worker->getTimeBetweenClicks()));
			if (valuesList[2].toShort())
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