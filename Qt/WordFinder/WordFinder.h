#pragma once

#include <QMainWindow>
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

class WordFinder : public QMainWindow
{
	Q_OBJECT

public:
	WordFinder(QWidget *parent = nullptr);
	~WordFinder();

private:
	Ui::WordFinderClass ui;
	
	const unsigned int DEFAULT_NB_RESULTS{ 25 };
	const std::string DEFAULT_WORD_LIST_FOLDER = "Word-lists";
	const std::string DEFAULT_WORD_LIST_PATH = DEFAULT_WORD_LIST_FOLDER + '/' + "francais.txt";

	std::vector<std::string> wordList;
	int maxResults;

	QLineEdit* resultNbInput;
	QLineEdit* searchInput;
	QComboBox* resultsComboBox;

	std::thread* searchThread;
	std::mutex searchMutex;
	bool searching;
	bool stopSearch;
	void searchFunction(const std::string subString);
	QGroupBox* initParameters();
	QHBoxLayout* initSearch();
	QHBoxLayout* initResults();

	void initWindow();
};
