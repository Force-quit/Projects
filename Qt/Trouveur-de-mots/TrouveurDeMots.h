#pragma once

#include <QWidget>
#include "ui_TrouveurDeMots.h"
#include <fstream>
#include <string>
#include <vector>

class TrouveurDeMots : public QWidget
{
	Q_OBJECT

public:
	TrouveurDeMots(QWidget *parent = nullptr);
	~TrouveurDeMots();
private:
	std::vector<std::string> wordList;
	Ui::TrouveurDeMotsClass ui;
};
