#include "WordFinderWorker.h"
#include <QString>
#include <QStringList>
#include <QThread>
#include <QDebug>

WordFinderWorker::WordFinderWorker(const QStringList& wordList, const unsigned int maxResults)
	: wordListRef(wordList), maxResults(maxResults)
{}

WordFinderWorker::~WordFinderWorker() {}

void WordFinderWorker::setMaxResults(const unsigned int nbResults)
{
	maxResults = nbResults;
}

void WordFinderWorker::findWords(const QString& pattern)
{
	unsigned int counter = 0;
	QStringList results;
	for (unsigned int i = 0; i < wordListRef.size() && counter != maxResults; ++i)
	{
		if (wordListRef[i].contains(pattern, Qt::CaseInsensitive))
		{
			results.append(wordListRef[i]);
			++counter;
		}
	}
	emit wordsFound(results);
}