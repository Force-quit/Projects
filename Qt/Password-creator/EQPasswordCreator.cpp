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

EQPasswordCreator::EQPasswordCreator(QWidget *parent)
	: QMainWindow(parent), workerThread(), passwordCreatorWorker()
{
	passwordCreatorWorker = new EQPasswordCreatorWorker(this, DEFAULT_PASSWORD_LENGTH);
	QWidget* centralWidget{ new QWidget };
	QHBoxLayout* centalLayout{ new QHBoxLayout };

	QGroupBox* parameters = initParameters();
	QVBoxLayout* generatorLayout = initGenerator();

	centalLayout->addWidget(parameters);
	centalLayout->addLayout(generatorLayout);

	centralWidget->setLayout(centalLayout);
	setCentralWidget(centralWidget);
	setWindowIcon(QIcon("gears.png"));
	loadAlphabet(DEFAULT_ALPHABET_PATH);
}

QGroupBox* EQPasswordCreator::initParameters()
{
	QGroupBox* parameters{ new QGroupBox("Parameters") };
	QVBoxLayout* parametersLayout{ new QVBoxLayout };

	QHBoxLayout* alphabetLayout{ new QHBoxLayout };
	QLabel* alphabetLabel{ new QLabel("Alphabet :") };
	alphabetText = new QLabel;
	QPushButton* changeAlphabetButton{ new QPushButton("Change") };
	alphabetLayout->addWidget(alphabetLabel);
	alphabetLayout->addWidget(alphabetText);
	alphabetLayout->addWidget(changeAlphabetButton);

	QHBoxLayout* passwordLengthLayout{ new QHBoxLayout };
	QLabel* passwordLengthLabel{ new QLabel("Password length :") };
	EQUIRangedLineEdit* passwordLengthLineEdit{ new EQUIRangedLineEdit(0, UINT_MAX) };
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

	connect(passwordLengthLineEdit, &EQUIRangedLineEdit::valueValidated, passwordCreatorWorker, &EQPasswordCreatorWorker::setPasswordLength); 
	return parameters;
}

QVBoxLayout* EQPasswordCreator::initGenerator()
{
	QVBoxLayout* generatorLayout{ new QVBoxLayout };

	QListView* passwordsListView{ new QListView };
	passwordsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	passwordsListView->setModel(new QStringListModel({ "Hello", "World", "This is a test" }));

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

	connect(copyButton, &QPushButton::clicked, [passwordsListView](){
		QGuiApplication::clipboard()->setText(passwordsListView->currentIndex().data().toString());
	});

	return generatorLayout;
}

void EQPasswordCreator::loadAlphabet(const QString& filePath)
{
	QFile file{ filePath };
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		passwordCreatorWorker->loadAlphabet(file);
		alphabetText->setText(filePath);
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
	qDebug(newPassword.toStdString().c_str());
}

EQPasswordCreator::~EQPasswordCreator()
{}