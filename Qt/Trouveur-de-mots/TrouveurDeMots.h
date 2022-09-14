#pragma once

#include <QWidget>
#include "ui_TrouveurDeMots.h"
#include <fstream>
#include <string>
#include <vector>
#include <QGroupBox.h>

class TrouveurDeMots : public QWidget
{
	Q_OBJECT

public:
	TrouveurDeMots(QWidget *parent = nullptr);
	~TrouveurDeMots();
private:
	QGroupBox* initParameters(std::string& defaultFileName);
	std::vector<std::string> wordList;
	unsigned int nbResults;
	Ui::TrouveurDeMotsClass ui;

};
