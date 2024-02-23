import EShortcutListener;

#include "EQShortcutListenerWorker.h"
#include <QThread>
#include <QTimer>
#include <QMapIterator>
#include <Windows.h>

EQShortcutListenerWorker::EQShortcutListenerWorker()
	: timer(), pressedKeys(), active(), inputChanged()
{
	
}

void EQShortcutListenerWorker::startListening()
{
	pressedKeys.clear();
	if (timer == nullptr)
	{
		timer = new QTimer;
		timer->setSingleShot(true);
		connect(timer, &QTimer::timeout, this, &EQShortcutListenerWorker::emitShortcutSelected);
	}

	// Clear current input buffer
	QMapIterator<int, QString> i(VIRTUAL_KEYS);
	while (i.hasNext()) 
	{
		i.next();
		GetAsyncKeyState(i.key());
	}

	active = true;
	QTimer::singleShot(10, this, &EQShortcutListenerWorker::listenLoop);
}

void EQShortcutListenerWorker::listenLoop()
{
	inputChanged = false;

	QMapIterator<int, QString> i(VIRTUAL_KEYS);
	while (i.hasNext()) 
	{
		i.next();
		if (GetAsyncKeyState(i.key()))
		{
			if (!pressedKeys.contains(i.key()))
			{
				inputChanged = true;
				pressedKeys[i.key()] = i.value();
				timer->start(HOLD_TIME_TO_CONFIRM);
			}
		}
		else if (pressedKeys.contains(i.key()))
		{
			inputChanged = true;
			pressedKeys.remove(i.key());
			if (pressedKeys.size() == 0)
				timer->stop();
			else
				timer->start(HOLD_TIME_TO_CONFIRM);
		}
	}

	if (inputChanged)
	{
		QString textToShow;
		for (QString text : pressedKeys.values())
			textToShow += text + " + ";
		textToShow.chop(3);
		emit shortcutTextChanged(textToShow);
	}

	if (active)
		QTimer::singleShot(10, this, &EQShortcutListenerWorker::listenLoop);
}

void EQShortcutListenerWorker::emitShortcutSelected()
{
	active = false;
	emit shortcutSelected();
	QTimer::singleShot(10, this, &EQShortcutListenerWorker::waitForShortcutRelease);
}

void EQShortcutListenerWorker::waitForShortcutRelease()
{
	for (auto& i : pressedKeys.keys())
	{
		if (!GetAsyncKeyState(i))
		{
			/*EShortcutListener::setTargetKeys();
			EShortcutListener::startListening();*/
			emit shortcutReady(pressedKeys.keys());
			return;
		}
	}

	QTimer::singleShot(10, this, &EQShortcutListenerWorker::waitForShortcutRelease);
}