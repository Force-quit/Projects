#pragma once

#include <QWidget>
#include "ui_TrouveurDeMots.h"
#include <fstream>
#include <string>
#include <vector>
#include <QGroupBox.h>
#include <QBoxLayout.h>
#include <QComboBox.h>
#include <QLineEdit.h>
#include <thread>

class TrouveurDeMots : public QWidget
{
	Q_OBJECT

public:
	TrouveurDeMots(QWidget *parent = nullptr);
	~TrouveurDeMots();
private:
	const unsigned int DEFAULT_NB_RESULTS{ 25 };
	const std::string DEFAULT_WORD_LIST_NAME = "francais.txt";
	std::vector<std::string> wordList;
	int maxResults;
	Ui::TrouveurDeMotsClass ui;

	QLineEdit* resultNbInput;
	QLineEdit* searchInput;
	QComboBox* resultsComboBox;

	std::thread* searchThread;

	bool searching;
	bool stopSearch;

	QGroupBox* initParameters();
	QHBoxLayout* initSearch();
	QHBoxLayout* initResults();

};
