#include "EQPasswordCreatorWorker.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QRandomGenerator>

EQPasswordCreatorWorker::EQPasswordCreatorWorker(QObject *parent, unsigned int passwordLength)
	: QObject(parent), currentAlphabet(), passwordLength(passwordLength), randomIndex(time(0))
{}

EQPasswordCreatorWorker::~EQPasswordCreatorWorker()
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
	QRandomGenerator rand{ randomIndex };
	++randomIndex;
	auto alphabetLength{ currentAlphabet.length() };
	QString password;
	password.resize(passwordLength);
	for (unsigned int i{}; i < passwordLength; ++i)
		password[i] = currentAlphabet[rand.generateDouble() * alphabetLength];
	emit passwordGenerated(password);
}