#include "WordFinderWorker.h"
#include <QStringList>
#include <QString>

WordFinderWorker::WordFinderWorker(const QStringList& wordList, const unsigned int maxResults)
	: wordListRef(wordList), maxResults(maxResults), nbCalls()
{}

WordFinderWorker::~WordFinderWorker() {}

void WordFinderWorker::queueWork()
{
	++nbCalls;
}

void WordFinderWorker::setMaxResults(const unsigned int nbResults)
{
	maxResults = nbResults;
}

void WordFinderWorker::findWords(const QString& pattern)
{
	QStringList results;
	if (pattern != "")
	{
		unsigned int counter = 0;
		for (unsigned int i = 0; i < wordListRef.size() && counter != maxResults && nbCalls == 1; ++i)
		{
			if (wordListRef[i].contains(pattern, Qt::CaseInsensitive))
			{
				results.append(wordListRef[i]);
				++counter;
			}
		}
	}

	if (nbCalls > 1)
	{
		--nbCalls;
		return;
	}

	--nbCalls;
	emit wordsFound(results);
}