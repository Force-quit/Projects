#pragma once

#include <QWidget>
#include <QString>
#include <QThread>
#include <QVector>
#include <QPushButton>
#include "EQShortcutPickerWorker.h"
#include <QLabel>

class EQShortcutPicker : public QWidget
{
	Q_OBJECT

public:
	EQShortcutPicker(QString labelText, QWidget *parent = nullptr);
	~EQShortcutPicker();


	const static int DEFAULT_CODE{ EQShortcutPickerWorker::DEFAULT_CODE };

signals:
	void shortcutChanged(QVector<int> virtualKeys);
	void startedListening();
	
private slots:
	void shortcutChosen();

private:
	QThread workerThread;
	QPushButton* changeShortcutButton;
	QLabel* shortcutText;

};
