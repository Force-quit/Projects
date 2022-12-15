#pragma once

#include <QObject>
#include <QString>
#include <QVector>

class EQShortcutPickerWorker  : public QObject
{
	Q_OBJECT

public:
	EQShortcutPickerWorker();
	~EQShortcutPickerWorker();

	const static int DEFAULT_CODE{ 0x11 };
	const static QString DEFAULT_SHORTCUT;

public slots:
	void startListening();

signals:
	void shortcutSelected(QVector<int> virtualKeys);
	void shortcutChanged(const QString newShortcutText);
};
