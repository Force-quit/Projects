#pragma once

#include <QObject>
#include <QStringList>
#include <QString>

class WordFinderWorker : public QObject
{
	Q_OBJECT

public:
	WordFinderWorker(const QStringList& wordList, const unsigned int maxResults);
	~WordFinderWorker();

	void queueWork();
public slots:
	void findWords(const QString& pattern);
	void setMaxResults(const unsigned int nbResults);

signals:
	void wordsFound(const QStringList& results);

private:
	const QStringList& wordListRef;
	unsigned int maxResults;
	unsigned short nbCalls;
};
