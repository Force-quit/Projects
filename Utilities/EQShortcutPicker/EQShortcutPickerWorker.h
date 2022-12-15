#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include <QTimer>

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

private slots:
	void listenLoop();
	void emitShortcutSelected();

private:
	static const QMap<int, QString> VIRTUAL_KEYS;
	static const unsigned short HOLD_TIME_TO_CONFIRM{ 3000 };

	bool active;
	QMap<int, QString> pressedKeys;
	QTimer* timer;
};
