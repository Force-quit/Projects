#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <QChar>

class EQPasswordCreatorWorker  : public QObject
{
	Q_OBJECT

public:
	EQPasswordCreatorWorker(QObject *parent);
	~EQPasswordCreatorWorker();
	
	void loadAlphabet(const QString& filePath);

public slots:
	void generatePassword(const unsigned int passwordSize);

signals:
	void passwordGenerated(QString password);

private:
	QVector<QChar> currentAlphabet;
};
