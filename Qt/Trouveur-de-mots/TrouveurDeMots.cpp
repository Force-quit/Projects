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
#include <thread>

TrouveurDeMots::TrouveurDeMots(QWidget* parent)
	: QWidget(parent)
{
	std::string defaultFileName("francais.txt");
	std::ifstream defaultFile(defaultFileName);
	if (defaultFile.good())
	{
		std::string temp;
		while (std::getline(defaultFile, temp))
			wordList.push_back(temp);
	}
	else
		defaultFileName.clear();
	defaultFile.close();

	auto* centralLayout{ new QVBoxLayout };

	auto* parametersGroupBox{ new QGroupBox("Parametres") };
	auto* parametersLayout{ new QVBoxLayout };
	auto* wordListLayout{ new QHBoxLayout };
	auto* wordListLabel{ new QLabel("Fichier de reference pour les mots :") };
	auto* wordListValue{ new QLabel(defaultFileName.c_str()) };
	auto* wordListButton{ new QPushButton("Choisir fichier") };
	connect(wordListButton, &QPushButton::clicked, [this, wordListValue]() {
		QString filePath = QFileDialog::getOpenFileName(this, "Choose File", QDir::currentPath(), "text files (*.txt)");
		std::ifstream file(filePath.toStdString());
		if (!file.good())
			MessageBox(NULL, L"Error reading file", L"Error", MB_CANCELTRYCONTINUE);
		else
		{
			wordList.clear();
			std::string temp;
			while (std::getline(file, temp))
				wordList.push_back(temp);
			wordListValue->setText(filePath);
		}

		file.close();

	});
	wordListLayout->addWidget(wordListLabel);
	wordListLayout->addWidget(wordListValue);
	wordListLayout->addWidget(wordListButton);
	auto* resultNbLabel{ new QLabel("Nombre de resultats :") };
	auto* resultNbValue{ new QLabel("25") };
	auto* resultNbInput{new };
	parametersLayout->addLayout(wordListLayout);
	parametersGroupBox->setLayout(parametersLayout);


	centralLayout->addWidget(parametersGroupBox);
	setLayout(centralLayout);
	ui.setupUi(this);
}

TrouveurDeMots::~TrouveurDeMots()
{}