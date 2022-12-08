#pragma once

#include <QMainWindow>
#include <QThread>
#include <QGroupBox>
#include "EQPasswordCreatorWorker.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QString>
#include <QStringListModel>
#include <QStringList>

class EQPasswordCreator : public QMainWindow
{
	Q_OBJECT

public:
	EQPasswordCreator(QWidget *parent = nullptr);
	~EQPasswordCreator();

public slots:
	void updatePasswordList(const QString newPassword);

private:
	const QString ALPHABETS_DIR{ "character-lists" };
	const QString DEFAULT_ALPHABET_PATH{ ALPHABETS_DIR + "/all.txt" };
	static const unsigned int DEFAULT_PASSWORD_LENGTH{ 25 };
	static const unsigned int MAX_PASSWORD_LENGTH{ 1000000 };
	static const unsigned short MAX_SAVED_PASSWORDS{ 10 };

	QThread workerThread;
	EQPasswordCreatorWorker* passwordCreatorWorker;
	QStringList realPasswordList;

	QGroupBox* initParameters();
	QVBoxLayout* initGenerator();
	
	QLabel* alphabetText;
	QStringListModel* passwordsListModel;

	void loadAlphabet(const QString& filePath);
};
