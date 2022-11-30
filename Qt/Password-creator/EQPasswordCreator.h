#pragma once

#include <QMainWindow>
#include <QThread>
#include <QGroupBox>
#include "EQPasswordCreatorWorker.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QString>

class EQPasswordCreator : public QMainWindow
{
	Q_OBJECT

public:
	EQPasswordCreator(QWidget *parent = nullptr);
	~EQPasswordCreator();

public slots:
	void updatePasswordList(const QString newPassword);

private:
	const QString ALPHABETS_DIR{ "alphabets" };
	const QString DEFAULT_ALPHABET_PATH{ ALPHABETS_DIR + "/allphabet.txt" };
	const unsigned int DEFAULT_PASSWORD_LENGTH{ 20 };

	QThread workerThread;
	EQPasswordCreatorWorker* passwordCreatorWorker;
	
	QGroupBox* initParameters();
	QVBoxLayout* initGenerator();
	
	QLabel* alphabetText;

	void loadAlphabet(const QString& filePath);
};
