#include "../Users/User/Documents/Projects/Qt/Trouveur-de-mots/TrouveurDeMots.h"
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

TrouveurDeMots::TrouveurDeMots(QWidget* parent)
	: QWidget(parent)
{
	std::string defaultFileName("francais.txt");
	wordListFile.open(defaultFileName);
	

	auto* centralLayout{ new QVBoxLayout };

	auto* parametersGroupBox{ new QGroupBox("Parametres") };
	auto* parametersLayout{ new QVBoxLayout };
	auto* wordListLayout{ new QHBoxLayout };
	auto* wordListLabel{ new QLabel("Fichier de reference pour les mots :") };
	auto* wordListValue{ new QLabel(wordListFile.good() ? defaultFileName.c_str() : "")};
	auto* wordListButton{ new QPushButton("Choisir fichier") };
	connect(wordListButton, &QPushButton::clicked, [this, wordListValue]() {
		QString filePath = QFileDialog::getOpenFileName(this, "Choose File", QDir::currentPath(), "text files (*.txt)");
		wordListFile.close();
		wordListFile.open(filePath.toStdString(), std::ifstream::in);
		if (!wordListFile.good())
			MessageBox(NULL, L"Error reading file", L"Error", MB_CANCELTRYCONTINUE);
		else
			wordListValue->setText(filePath);
	});
	wordListLayout->addWidget(wordListLabel);
	wordListLayout->addWidget(wordListValue);
	wordListLayout->addWidget(wordListButton);
	parametersLayout->addLayout(wordListLayout);
	parametersGroupBox->setLayout(parametersLayout);


	centralLayout->addWidget(parametersGroupBox);
	setLayout(centralLayout);
	ui.setupUi(this);
}

TrouveurDeMots::~TrouveurDeMots()
{}