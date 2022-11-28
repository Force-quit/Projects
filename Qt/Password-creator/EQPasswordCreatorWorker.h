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
	EQPasswordCreatorWorker(QObject *parent);
	~EQPasswordCreatorWorker();
	
	void loadAlphabet(QFile& opennedFile);

public slots:
	void generatePassword();
	void setPasswordLength(const unsigned int passwordLength);

signals:
	void passwordGenerated(QString password);

private:
	QVector<QChar> currentAlphabet;
	unsigned int passwordLength;
};
