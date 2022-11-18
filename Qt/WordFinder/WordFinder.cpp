#include "WordFinder.h"
#include <qlabel.h>
#include <qboxlayout.h>
#include <qgroupbox.h>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <qpushbutton.h>
#include <fstream>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <QLineEdit.h>
#include <QIntValidator>
#include <qcombobox.h>
#include <thread>
#include <cstdlib>
#include <mutex>
#include <QDir>
#include <QMessageBox>
#include <QThread>
#include "WordFinderWorker.h"
#include <QClipboard>
#include <QGuiApplication>

WordFinder::WordFinder(QWidget* parent)
	: QMainWindow(parent), maxResults(DEFAULT_NB_RESULTS), wordList(), worker(), workerThread()
{
	ui.setupUi(this);
	if (!QDir().mkdir(DEFAULT_WORD_LIST_FOLDER))
		loadWordList(DEFAULT_WORD_LIST_PATH);

	QVBoxLayout* centralLayout{ new QVBoxLayout };

	QGroupBox* parametersGroupBox = initParameters();
	QHBoxLayout* searchLayout = initSearch();
	QHBoxLayout* resultsLayout = initResults();

	centralLayout->addWidget(parametersGroupBox);
	centralLayout->addLayout(searchLayout);
	centralLayout->addLayout(resultsLayout);
	centralLayout->setAlignment(Qt::AlignTop);

	QWidget* centralWidget{ new QWidget };
	centralWidget->setLayout(centralLayout);
	setCentralWidget(centralWidget);
	initWindow();
}

QGroupBox* WordFinder::initParameters()
{
	QGroupBox* parametersGroupBox{ new QGroupBox("Parameters") };

	QHBoxLayout* wordListLayout{ new QHBoxLayout };
	QLabel* wordListLabel{ new QLabel("Word list :") };
	QLabel* wordListPath{ new QLabel(wordList.size() > 0 ? DEFAULT_WORD_LIST_PATH : "None") };
	QPushButton* wordListButton{ new QPushButton("Select file") };
	wordListLayout->addWidget(wordListLabel);
	wordListLayout->addWidget(wordListPath);
	wordListLayout->addWidget(wordListButton);
	connect(wordListButton, &QPushButton::clicked, [this, wordListPath]() {
		QString filePath = QFileDialog::getOpenFileName(this, "Select word list", DEFAULT_WORD_LIST_PATH, "text files (*.txt)");
		if (!filePath.isEmpty())
		{
			loadWordList(filePath);
			wordListPath->setText(filePath);
			resultsComboBox->clear();
			searchInput->clear();
		}
	});

	QHBoxLayout* resultNbLayout{ new QHBoxLayout };
	QLabel* resultNbLabel{ new QLabel("Max results :") };
	QLineEdit* resultNbInput{ new QLineEdit };
	resultNbInput->setText(QString::number(DEFAULT_NB_RESULTS));
	QIntValidator* intValidator{ new QIntValidator };
	intValidator->setRange(1, INT_MAX);
	resultNbInput->setValidator(intValidator);
	connect(resultNbInput, &QLineEdit::textEdited, [this, resultNbInput]() {
		QString text = resultNbInput->text();
		if (text.isEmpty())
			maxResults = 0;
		else
		{
			int result = std::atoi(text.toStdString().c_str());
			if (result == INT_MAX)
				resultNbInput->setText(QString::number(result));
			maxResults = result;
		}

		worker->setMaxResults(maxResults);
		});
	resultNbLayout->addWidget(resultNbLabel);
	resultNbLayout->addWidget(resultNbInput);

	auto* parametersLayout{ new QVBoxLayout };
	parametersLayout->addLayout(wordListLayout);
	parametersLayout->addLayout(resultNbLayout);
	parametersGroupBox->setLayout(parametersLayout);
	return parametersGroupBox;
}

QHBoxLayout* WordFinder::initSearch()
{
	auto* searchLayout{ new QHBoxLayout };
	auto* searchLabel{ new QLabel("Pattern to find :") };
	searchInput = new QLineEdit;
	searchInput->setValidator(new QRegularExpressionValidator(QRegularExpression(QString::fromUtf8("\\p{L}+"))));
	searchLayout->addWidget(searchLabel);
	searchLayout->addWidget(searchInput);
	worker = new WordFinderWorker(wordList, maxResults);
	connect(searchInput, &QLineEdit::textEdited, worker, &WordFinderWorker::findWords);
	worker->moveToThread(&workerThread);
	connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
	connect(worker, &WordFinderWorker::wordsFound, [this](const QStringList& result) {
		resultsComboBox->clear();
		resultsComboBox->addItems(result);
		});
	workerThread.start();
	return searchLayout;
}

QHBoxLayout* WordFinder::initResults()
{
	QHBoxLayout* resultsLayout{ new QHBoxLayout };
	resultsComboBox = new QComboBox;
	QPushButton* resultsButton{ new QPushButton("Copy") };
	connect(resultsButton, &QPushButton::clicked, [this]() {
		QGuiApplication::clipboard()->setText(resultsComboBox->currentText());
		});
	resultsLayout->addWidget(resultsComboBox);
	resultsLayout->addWidget(resultsButton);
	return resultsLayout;
}

void WordFinder::initWindow()
{
	setWindowTitle("Word finder");
	resize(minimumSizeHint());
	setWindowIcon(QIcon("program-icon.png"));
}

void WordFinder::loadWordList(const QString& filePath)
{
	QFile file{ filePath };
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		wordList.clear();
		QTextStream in{ &file };
		while (!in.atEnd())
			wordList.append(in.readLine());
		wordList.squeeze();
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

WordFinder::~WordFinder()
{
	workerThread.quit();
	workerThread.wait();
}