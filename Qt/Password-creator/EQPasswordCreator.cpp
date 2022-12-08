#include "EQPasswordCreator.h"
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QGroupBox>
#include "../../Utilities/EQUIRangedLineEdit.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QListView>
#include <QStringListModel>
#include <QGuiApplication>
#include <QClipboard>
#include <QFile>
#include <QDir>
#include <QStringList>

EQPasswordCreator::EQPasswordCreator(QWidget* parent)
	: QMainWindow(parent), workerThread(), passwordCreatorWorker(), passwordsListModel(), realPasswordList(), alphabetText()
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

	QHBoxLayout* alphabetLayout{ new QHBoxLayout };
	QLabel* alphabetLabel{ new QLabel("Character list :") };
	alphabetText = new QLabel;
	QPushButton* changeAlphabetButton{ new QPushButton("Change") };
	alphabetLayout->addWidget(alphabetLabel);
	alphabetLayout->addWidget(alphabetText);
	alphabetLayout->addWidget(changeAlphabetButton);

	QHBoxLayout* passwordLengthLayout{ new QHBoxLayout };
	QLabel* passwordLengthLabel{ new QLabel("Password length :") };
	EQUIRangedLineEdit* passwordLengthLineEdit{ new EQUIRangedLineEdit(0, MAX_PASSWORD_LENGTH) };
	passwordLengthLineEdit->insert(QString::number(DEFAULT_PASSWORD_LENGTH));
	passwordLengthLayout->addWidget(passwordLengthLabel);
	passwordLengthLayout->addWidget(passwordLengthLineEdit);

	parametersLayout->addLayout(alphabetLayout);
	parametersLayout->addLayout(passwordLengthLayout);
	parameters->setLayout(parametersLayout);

	connect(changeAlphabetButton, &QPushButton::clicked, [this]() {
		QString filePath = QFileDialog::getOpenFileName(this, "Select character list", ALPHABETS_DIR, "text files (*.txt)");
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
		alphabetText->setText(QDir().relativeFilePath(filePath));
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
		QString temp;
		for (short i = 0; i < 10; ++i)
			temp += newPassword[i];
		temp += " [...] ";
		for (unsigned int i = newPassword.length() - 10; i < newPassword.length(); ++i)
			temp += newPassword[i];
		passwordList.append(temp);
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