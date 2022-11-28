#include "EQPasswordCreatorWorker.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

EQPasswordCreatorWorker::EQPasswordCreatorWorker(QObject *parent)
	: QObject(parent), currentAlphabet()
{}

EQPasswordCreatorWorker::~EQPasswordCreatorWorker()
{}

void EQPasswordCreatorWorker::loadAlphabet(const QString & filePath)
{
	QFile file{ filePath };
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		currentAlphabet.clear();
		QTextStream in{ &file };
		QString line{ in.readLine() };
		for (QChar& i : line)
			currentAlphabet.append(i);
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText("File error");
		msgBox.setInformativeText("Error reading file" + filePath);
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		msgBox.exec();
	}
	file.close();
}

void EQPasswordCreatorWorker::generatePassword(const unsigned int passwordSize)
{

}