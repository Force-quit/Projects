#pragma once

#include "ui_WordFinder.h"
#include <QMainWindow>
#include <QGroupBox.h>
#include <QBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QString>
#include <QStringList>

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
	int maxResults;

	QLineEdit* resultNbInput;
	QLineEdit* searchInput;
	QComboBox* resultsComboBox;


	QGroupBox* initParameters();
	QHBoxLayout* initSearch();
	QHBoxLayout* initResults();

	void loadWordList(const QString& filePath);
	void initWindow();
};