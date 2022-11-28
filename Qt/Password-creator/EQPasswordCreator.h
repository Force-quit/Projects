#pragma once

#include <QMainWindow>
#include <QThread>
#include <QGroupBox>
#include "EQPasswordCreatorWorker.h"

class EQPasswordCreator : public QMainWindow
{
	Q_OBJECT

public:
	EQPasswordCreator(QWidget *parent = nullptr);
	~EQPasswordCreator();

public slots:
	void setAlphabetText(const QString& text);

private:
	const QString ALPHABETS_DIR{ "alphabets" };
	const QString DEFAULT_ALPHABET_PATH{ ALPHABETS_DIR + "/allphabets.txt" };


	QThread workerThread;
	EQPasswordCreatorWorker* passwordCreatorWorker;
	
	QGroupBox* initParameters();
	
	QLabel* alphabetText;

	void loadAlphabet(const QString& filePath);
};
