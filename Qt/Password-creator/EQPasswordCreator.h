#pragma once

#include <QMainWindow>
#include <QString>
#include <QThread>
#include "EQPasswordCreatorWorker.h"
#include <QStringList>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QStringListModel>

class EQPasswordCreator : public QMainWindow
{
	Q_OBJECT

public:
	EQPasswordCreator(QWidget *parent = nullptr);
	~EQPasswordCreator();

public slots:
	void updatePasswordList(const QString newPassword);

private:
	static const unsigned int DEFAULT_PASSWORD_LENGTH{ 25 };
	static const unsigned int MAX_PASSWORD_LENGTH{ 1000000 };
	static const unsigned short MAX_SAVED_PASSWORDS{ 10 };
	const QString ALPHABETS_DIR{ "character-lists" };
	const QString DEFAULT_ALPHABET_PATH{ ALPHABETS_DIR + "/all.txt" };

	QThread workerThread;
	EQPasswordCreatorWorker* passwordCreatorWorker;
	QStringList realPasswordList;
	QLabel* characterSetText;
	QStringListModel* passwordsListModel;

	QGroupBox* initParameters();
	QVBoxLayout* initGenerator();
	
	void loadAlphabet(const QString& filePath);
};
