#include "EQPasswordCreatorWorker.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

EQPasswordCreatorWorker::EQPasswordCreatorWorker(QObject *parent)
	: QObject(parent), currentAlphabet()
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
	
}