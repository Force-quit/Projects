#include "../../Utilities/utils.h"
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

WordFinder::WordFinder(QWidget* parent)
	: QMainWindow(parent), maxResults(DEFAULT_NB_RESULTS), wordList()
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
	auto* parametersGroupBox{ new QGroupBox("Parameters") };
	auto* wordListLayout{ new QHBoxLayout };
	auto* wordListLabel{ new QLabel("Word list :") };
	auto* wordListValue{ new QLabel(wordList.size() > 0 ? DEFAULT_WORD_LIST_PATH : "") };
	auto* wordListButton{ new QPushButton("Select file") };
	connect(wordListButton, &QPushButton::clicked, [this, wordListValue]() {
		QString filePath = QFileDialog::getOpenFileName(this, "Select word list", DEFAULT_WORD_LIST_PATH, "text files (*.txt)");
		if (!filePath.isEmpty())
		{
			loadWordList(filePath);
			wordListValue->setText(filePath);
			resultsComboBox->clear();
			searchInput->clear();
		}
	});
	wordListLayout->addWidget(wordListLabel);
	wordListLayout->addWidget(wordListValue);
	wordListLayout->addWidget(wordListButton);
	auto* resultNbLayout{ new QHBoxLayout };
	auto* resultNbLabel{ new QLabel("Max results :") };
	resultNbInput = new QLineEdit;
	resultNbInput->setText(QString::number(DEFAULT_NB_RESULTS));
	auto* intValidator{ new QIntValidator };
	intValidator->setRange(1, INT_MAX);
	resultNbInput->setValidator(intValidator);
	connect(resultNbInput, &QLineEdit::textEdited, [this]() {
		QString text = resultNbInput->text();
		if (text.isEmpty())
			maxResults = 0;
		else
		{
			int result = std::atoi(text.toStdString().c_str());
			if (result == INT_MAX) // If input too big
				resultNbInput->setText(QString::number(result));
			maxResults = result;
		}
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
	connect(searchInput, &QLineEdit::textEdited, [this](const QString& text) {
		searchMutex.lock();
		resultsComboBox->clear();

		if (searching)
		{
			stopSearch = true;
			searchThread->join();
			delete searchThread;

			searching = false;
			stopSearch = false;
		}
		searchMutex.unlock();

		if (maxResults > 0 && !text.isEmpty())
		{
			std::string subString = text.toStdString();
			searchThread = new std::thread([this](std::string s) {searchFunction(s); }, subString);
			searching = true;
		}
		});
	return searchLayout;
}

QHBoxLayout* WordFinder::initResults()
{
	QHBoxLayout* resultsLayout{ new QHBoxLayout };
	resultsComboBox = new QComboBox;
	QPushButton* resultsButton{ new QPushButton("Copy") };
	connect(resultsButton, &QPushButton::clicked, [this]() {
		QString currentText = resultsComboBox->currentText();
		if (!currentText.isEmpty())
		{

			std::wstring wstr = currentText.toStdWString();
			std::string convertedString;
			convertedString.resize(wstr.length());
			size_t size;
			wcstombs_s(&size, &convertedString[0], convertedString.size() + 1, wstr.c_str(), wstr.size());

			emile::copyToClipBoard(convertedString);
		}
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

WordFinder::~WordFinder() {}