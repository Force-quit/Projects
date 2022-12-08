#include "EQPasswordCreatorWorker.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QThread>

EQPasswordCreatorWorker::EQPasswordCreatorWorker(unsigned int passwordLength)
	: currentAlphabet(), passwordLength(passwordLength), randomIndex(time(0))
{}

void EQPasswordCreatorWorker::loadAlphabet(QFile& opennedFile)
{
	currentAlphabet.clear();
	QTextStream in{ &opennedFile };
	QString line{ in.readLine() };
	for (QChar& i : line)
		currentAlphabet.append(i);
}

void EQPasswordCreatorWorker::setPasswordLength(const unsigned int passwordLength)
{
	this->passwordLength = passwordLength;
}

void EQPasswordCreatorWorker::generatePassword()
{
	++randomIndex;
	QRandomGenerator rand{ randomIndex };
	auto alphabetLength{ currentAlphabet.length() };
	QString password;
	password.resize(passwordLength);
	for (unsigned int i{}; i < passwordLength; ++i)
		password[i] = currentAlphabet[rand.generateDouble() * alphabetLength];
	emit passwordGenerated(password);
}

EQPasswordCreatorWorker::~EQPasswordCreatorWorker()
{}