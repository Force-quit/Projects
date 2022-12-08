#include "EQPasswordCreator.h"
#include <QMainWindow>
#include "EQPasswordCreatorWorker.h"
#include <QBoxLayout>
#include <QGroupBox>
#include <QIcon>
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include "../../Utilities/EQUIRangedLineEdit.h"
#include <QString>
#include <QFileDialog>
#include <QListView>
#include <QStringListModel>
#include <QThread>
#include <QGUIApplication>
#include <QClipboard>
#include <QDir>
#include <QMessageBox>
#include <QStringList>

EQPasswordCreator::EQPasswordCreator(QWidget* parent)
	: QMainWindow(parent), workerThread(), passwordCreatorWorker(), passwordsListModel(), realPasswordList(), characterSetText()
{
	passwordCreatorWorker = new EQPasswordCreatorWorker(DEFAULT_PASSWORD_LENGTH);

	QWidget* centralWidget{ new QWidget };
	QHBoxLayout* centalLayout{ new QHBoxLayout };

	QGroupBox* parameters = initParameters();
	QVBoxLayout* generatorLayout = initGenerator();

	centalLayout->addWidget(parameters);
	centalLayout->addLayout(generatorLayout);

	centralWidget->setLayout(centalLayout);
	setCentralWidget(centralWidget);
	setWindowIcon(QIcon("gears.png"));

	if (QFile::exists(DEFAULT_ALPHABET_PATH))
		loadAlphabet(DEFAULT_ALPHABET_PATH);
}

QGroupBox* EQPasswordCreator::initParameters()
{
	QGroupBox* parameters{ new QGroupBox("Parameters") };
	QVBoxLayout* parametersLayout{ new QVBoxLayout };

	QHBoxLayout* characterSetLayout{ new QHBoxLayout };
	QLabel* characterSetLabel{ new QLabel("Character list :") };
	characterSetText = new QLabel;
	QPushButton* characterSetButton{ new QPushButton("Change") };
	characterSetLayout->addWidget(characterSetLabel);
	characterSetLayout->addWidget(characterSetText);
	characterSetLayout->addWidget(characterSetButton);

	QHBoxLayout* passwordLengthLayout{ new QHBoxLayout };
	QLabel* passwordLengthLabel{ new QLabel("Password length :") };
	EQUIRangedLineEdit* passwordLengthLineEdit{ new EQUIRangedLineEdit(0, MAX_PASSWORD_LENGTH) };
	passwordLengthLineEdit->insert(QString::number(DEFAULT_PASSWORD_LENGTH));
	passwordLengthLayout->addWidget(passwordLengthLabel);
	passwordLengthLayout->addWidget(passwordLengthLineEdit);

	parametersLayout->addLayout(characterSetLayout);
	parametersLayout->addLayout(passwordLengthLayout);
	parameters->setLayout(parametersLayout);

	connect(characterSetButton, &QPushButton::clicked, [this]() {
		QString filePath{ QFileDialog::getOpenFileName(this, "Select character list", ALPHABETS_DIR, "text files (*.txt)") };
		if (!filePath.isEmpty())
			loadAlphabet(filePath);
	});
	connect(passwordLengthLineEdit, &EQUIRangedLineEdit::valueValidated,
		passwordCreatorWorker, &EQPasswordCreatorWorker::setPasswordLength);
	return parameters;
}

QVBoxLayout* EQPasswordCreator::initGenerator()
{
	QVBoxLayout* generatorLayout{ new QVBoxLayout };

	QListView* passwordsListView{ new QListView };
	passwordsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	passwordsListModel = new QStringListModel;
	passwordsListView->setModel(passwordsListModel);
	
	QPushButton* generateButton{ new QPushButton("Generate") };
	QPushButton* copyButton{ new QPushButton("Copy") };

	generatorLayout->addWidget(passwordsListView);
	generatorLayout->addWidget(generateButton);
	generatorLayout->addWidget(copyButton);

	connect(generateButton, &QPushButton::clicked, passwordCreatorWorker, &EQPasswordCreatorWorker::generatePassword);
	connect(passwordCreatorWorker, &EQPasswordCreatorWorker::passwordGenerated, this, &EQPasswordCreator::updatePasswordList);
	connect(&workerThread, &QThread::finished, passwordCreatorWorker, &QObject::deleteLater);
	passwordCreatorWorker->moveToThread(&workerThread);
	workerThread.start();

	connect(copyButton, &QPushButton::clicked, [this, passwordsListView]() {
		QString& password{ realPasswordList[passwordsListView->currentIndex().row()] };
		QGuiApplication::clipboard()->setText(password);
	});
	return generatorLayout;
}

void EQPasswordCreator::loadAlphabet(const QString& filePath)
{
	QFile file{ filePath };
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		passwordCreatorWorker->loadAlphabet(file);
		characterSetText->setText(QDir().relativeFilePath(filePath));
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("File error");
		msgBox.setInformativeText("Error reading file" + filePath);
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		msgBox.exec();
	}
	file.close();
}

void EQPasswordCreator::updatePasswordList(const QString newPassword)
{
	realPasswordList.append(newPassword);
	QStringList passwordList{ passwordsListModel->stringList() };
	if (realPasswordList.length() > MAX_SAVED_PASSWORDS)
	{
		realPasswordList.removeFirst();
		passwordList.removeFirst();
	}

	if (newPassword.length() > 30)
	{
		QString shortennedPassword;
		for (short i = 0; i < 10; ++i)
			shortennedPassword += newPassword[i];

		shortennedPassword += " [...] ";

		for (unsigned int i = newPassword.length() - 10; i < newPassword.length(); ++i)
			shortennedPassword += newPassword[i];

		passwordList.append(shortennedPassword);
	}
	else
		passwordList.append(newPassword);
	passwordsListModel->setStringList(passwordList);
}

EQPasswordCreator::~EQPasswordCreator()
{
	workerThread.quit();
	workerThread.wait();
}