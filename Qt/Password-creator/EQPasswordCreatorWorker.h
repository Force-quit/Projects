#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <QChar>
#include <QFile>

class EQPasswordCreatorWorker  : public QObject
{
	Q_OBJECT

public:
	EQPasswordCreatorWorker(unsigned int passwordLength);
	~EQPasswordCreatorWorker();
	
	void loadAlphabet(QFile& opennedFile);

public slots:
	void generatePassword();
	void setPasswordLength(const unsigned int passwordLength);

signals:
	void passwordGenerated(const QString password);

private:
	QVector<QChar> currentAlphabet;
	unsigned int passwordLength;
	unsigned int randomIndex;
};
