#pragma once

#include <QWidget>
#include "ui_WordFinder.h"
#include <fstream>
#include <string>
#include <vector>
#include <QGroupBox.h>
#include <QBoxLayout.h>
#include <QComboBox.h>
#include <QLineEdit.h>
#include <thread>
#include <mutex>

class WordFinder : public QWidget
{
	Q_OBJECT

public:
	WordFinder(QWidget* parent = nullptr);
	~WordFinder();
private:
	const unsigned int DEFAULT_NB_RESULTS{ 25 };
	const std::string DEFAULT_WORD_LIST_NAME = "francais.txt";
	std::vector<std::string> wordList;
	int maxResults;
	Ui::WordFinderClass ui;

	QLineEdit* resultNbInput;
	QLineEdit* searchInput;
	QComboBox* resultsComboBox;

	std::thread* searchThread;
	std::mutex searchMutex;
	bool searching;
	bool stopSearch;

	QGroupBox* initParameters();
	QHBoxLayout* initSearch();
	QHBoxLayout* initResults();

};
