#include "WordFinderWorker.h"
#include <QString>
#include <QStringList>

WordFinderWorker::WordFinderWorker(QObject* parent, const QStringList& wordList, const unsigned int maxResults)
	: QObject(parent), wordListRef(wordList), working(), stopWorking(), maxResults(maxResults)
{}

WordFinderWorker::~WordFinderWorker() {}

void WordFinderWorker::setMaxResults(const unsigned int nbResults)
{
	maxResults = nbResults;
}

void WordFinderWorker::findWords(const QString& pattern)
{
	//if (working)
	//{
	//	stopWorking = true;
	//	while (working)
	//		QThread::yieldCurrentThread();
	//}

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