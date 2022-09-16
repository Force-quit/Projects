#if true
#include "C:\Users\User\Documents\MY-STUFF\Projects\Qt\WordFinder\WordFinder.h"
#include "C:\Users\User\Documents\MY-STUFF\Projects\Utilities\utils.h"
#else
#include "../Users/User/Documents/Projects/Qt/WordFinder/WordFinder.h"
#endif

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

WordFinder::WordFinder(QWidget* parent)
	: QWidget(parent), maxResults(DEFAULT_NB_RESULTS), wordList(), searching(), stopSearch(), searchThread(), searchMutex()
{
	std::ifstream defaultFile(DEFAULT_WORD_LIST_NAME);
	if (defaultFile.good())
	{
		std::string temp;
		while (std::getline(defaultFile, temp))
			wordList.push_back(temp);
	}
	defaultFile.close();

	QVBoxLayout* centralLayout{ new QVBoxLayout };

	QGroupBox* parametersGroupBox = initParameters();
	QHBoxLayout* searchLayout = initSearch();
	QHBoxLayout* resultsLayout = initResults();

	centralLayout->addWidget(parametersGroupBox);
	centralLayout->addLayout(searchLayout);
	centralLayout->addLayout(resultsLayout);
	setLayout(centralLayout);
	ui.setupUi(this);
}


void searchFunction(int& maxResults, std::vector<std::string>& wordList, bool& stopSearch, QComboBox& resultsComboBox, std::string subString, bool& searching, std::mutex& searchMutex)
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
	resultsComboBox.addItems(results);
	if (resultsComboBox.count() > 0)
		resultsComboBox.setCurrentIndex(0);
	searching = false;
	stopSearch = false;
	searchMutex.unlock();
}

QGroupBox* WordFinder::initParameters()
{
	auto* parametersGroupBox{ new QGroupBox("Parameters") };
	auto* parametersLayout{ new QVBoxLayout };
	auto* wordListLayout{ new QHBoxLayout };
	auto* wordListLabel{ new QLabel("Word list :") };
	auto* wordListValue{ new QLabel(DEFAULT_WORD_LIST_NAME.c_str()) };
	auto* wordListButton{ new QPushButton("Select file") };
	connect(wordListButton, &QPushButton::clicked, [this, wordListValue]() {

		QString filePath = QFileDialog::getOpenFileName(this, "Select word list", QDir::currentPath(), "text files (*.txt)");

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

	parametersLayout->addLayout(wordListLayout);
	parametersLayout->addLayout(resultNbLayout);
	parametersLayout->setAlignment(Qt::AlignTop);
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
	connect(searchInput, &QLineEdit::textEdited, [this]() {
		if (maxResults != 0)
		{
			searchMutex.lock();
			resultsComboBox->clear();

			if (searching)
				stopSearch = true;
			searchMutex.unlock();

			if (searchThread != nullptr)
				searchThread->join();

			delete searchThread;
			std::string subString = searchInput->text().toStdString();
			searchThread = new std::thread(searchFunction, std::ref(maxResults), std::ref(wordList), std::ref(stopSearch), std::ref(*resultsComboBox), subString, std::ref(searching), std::ref(searchMutex));
			searching = true;
		}
		else
			resultsComboBox->clear();
		});
	return searchLayout;
}

QHBoxLayout* WordFinder::initResults()
{
	auto* resultsLayout{ new QHBoxLayout };
	resultsComboBox = new QComboBox;
	auto* resultsButton{ new QPushButton("Copy") };
	connect(resultsButton, &QPushButton::clicked, [this]() {
		QString currentText = resultsComboBox->currentText();
		if (!currentText.isEmpty())
		{
			// What is this dark magic
			std::wstring wstr = currentText.toStdWString();
			std::string convertedString;
			size_t size;
			convertedString.resize(wstr.length());
			wcstombs_s(&size, &convertedString[0], convertedString.size() + 1, wstr.c_str(), wstr.size());
			//


			emile::copyToClipBoard(convertedString);
		}
		});
	resultsLayout->addWidget(resultsComboBox);
	resultsLayout->addWidget(resultsButton);
	return resultsLayout;
}

WordFinder::~WordFinder()
{

}