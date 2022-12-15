#pragma once

#include <QWidget>
#include <QString>
#include <QThread>
#include <QVector>

class EQShortcutPicker : public QWidget
{
	Q_OBJECT

public:
	EQShortcutPicker(QString labelText, QWidget *parent = nullptr);
	~EQShortcutPicker();

signals:
	void shortcutChanged(QVector<int> virtualKeys);
	
private:
	QThread workerThread;
};
