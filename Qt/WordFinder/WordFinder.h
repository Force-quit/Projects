#pragma once

#include "ui_WordFinder.h"
#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QStringList>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QBoxLayout>
#include "WordFinderWorker.h"
#include <QThread>

class WordFinder : public QMainWindow
{
	Q_OBJECT

public:
	WordFinder(QWidget *parent = nullptr);
	~WordFinder();

private:
	Ui::WordFinderClass ui;
	
	const unsigned int DEFAULT_NB_RESULTS{ 25 };
	const QString DEFAULT_WORD_LIST_FOLDER{ "Word-lists" };
	const QString DEFAULT_WORD_LIST_PATH{ DEFAULT_WORD_LIST_FOLDER + '/' + "francais.txt" };

	QStringList wordList;
	unsigned int maxResults;

	QLineEdit* resultNbInput;
	QLineEdit* searchInput;
	QComboBox* resultsComboBox;

	QGroupBox* initParameters();
	QHBoxLayout* initSearch();
	QHBoxLayout* initResults();

	WordFinderWorker* worker;
	QThread workerThread;
	void loadWordList(const QString& filePath);
	void initWindow();
};