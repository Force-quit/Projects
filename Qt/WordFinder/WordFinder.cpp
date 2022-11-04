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

WordFinder::WordFinder(QWidget *parent)
	: QMainWindow(parent), maxResults(DEFAULT_NB_RESULTS), wordList(), searching(), stopSearch(), searchMutex(), searchThread()
{
	ui.setupUi(this);

	if (emile::folderExists(DEFAULT_WORD_LIST_FOLDER))
	{
		std::ifstream defaultFile(DEFAULT_WORD_LIST_PATH);
		if (defaultFile.good())
		{
			std::string temp;
			while (std::getline(defaultFile, temp))
				wordList.push_back(temp);
		}
		defaultFile.close();
	}

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

	int width = size().width() / 2;
	int height = minimumSizeHint().height();
	resize(width, height);
}

void WordFinder::searchFunction(std::string subString)
{
	unsigned int counter = 0;
	QStringList results;
	for (unsigned int i = 0; i < wordList.size() && !stopSearch; ++i)
	{
		if (wordList[i].find(subString) != std::string::npos)
		{
			results.append(QString::fromUtf8(wordList[i]));
			++counter;
			if (counter == maxResults)
				break;
		}
	}

	searchMutex.lock();
	resultsComboBox->addItems(results);
	if (resultsComboBox->count() > 0)
		resultsComboBox->setCurrentIndex(0);
	searching = false;
	stopSearch = false;
	searchMutex.unlock();
}

QGroupBox* WordFinder::initParameters()
{
	auto* parametersGroupBox{ new QGroupBox("Parameters") };
	auto* wordListLayout{ new QHBoxLayout };
	auto* wordListLabel{ new QLabel("Word list :") };
	auto* wordListValue{ new QLabel(wordList.size() > 0 ? DEFAULT_WORD_LIST_PATH.c_str() : "") };
	auto* wordListButton{ new QPushButton("Select file") };
	connect(wordListButton, &QPushButton::clicked, [this, wordListValue]() {
		QString filePath = QString::fromStdString(DEFAULT_WORD_LIST_PATH);
		filePath = QFileDialog::getOpenFileName(this, "Select word list", filePath, "text files (*.txt)");

		if (!filePath.isEmpty())
		{
			std::ifstream file(filePath.toStdString());
			if (!file.good())
				MessageBox(NULL, L"Error reading file", L"File error", MB_ICONERROR);
			else
			{
				wordList.clear();
				std::string temp;
				while (std::getline(file, temp))
					wordList.push_back(temp);
				wordListValue->setText(filePath);
				resultsComboBox->clear();
				searchInput->clear();
			}

			file.close();
		}
		});
	wordListLayout->addWidget(wordListLabel);
	wordListLayout->addWidget(wordListValue);
	wordListLayout->addWidget(wordListButton);
	auto* resultNbLayout{ new QHBoxLayout };
	auto* resultNbLabel{ new QLabel("Result number :") };
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
	auto* searchLabel{ new QLabel("Substring to find :") };
	searchInput = new QLineEdit;
	searchInput->setValidator(new QRegularExpressionValidator(QRegularExpression(QString::fromUtf8("\\p{L}+"))));
	searchLayout->addWidget(searchLabel);
	searchLayout->addWidget(searchInput);
	connect(searchInput, &QLineEdit::textEdited, [this](const QString& text) {
		searchMutex.lock();
		resultsComboBox->clear();

		if (searching)
			stopSearch = true;
		searchMutex.unlock();

		if (maxResults > 0 && !text.isEmpty())
		{
			if (searchThread != nullptr)
				searchThread->join();

			delete searchThread;
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

WordFinder::~WordFinder() {}