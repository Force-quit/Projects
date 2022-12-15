#include "EQShortcutPickerWorker.h"


const QString EQShortcutPickerWorker::DEFAULT_SHORTCUT{ "CTRL" };

EQShortcutPickerWorker::EQShortcutPickerWorker()
{
	
}


void EQShortcutPickerWorker::startListening()
{
	emit shortcutChanged("A+B");
	emit shortcutSelected(QVector<int>{1, 2});
}


EQShortcutPickerWorker::~EQShortcutPickerWorker() {}