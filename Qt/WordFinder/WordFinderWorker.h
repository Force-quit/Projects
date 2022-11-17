#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QStringList>

class WordFinderWorker : public QObject
{
	Q_OBJECT

public:
	WordFinderWorker(const QStringList& wordList, const unsigned int maxResults);
	~WordFinderWorker();
	void setMaxResults(const unsigned int nbResults);

public slots:
	void findWords(const QString& pattern);

signals:
	void wordsFound(const QStringList& results);

private:
	const QStringList& wordListRef;
	unsigned int maxResults;
};
