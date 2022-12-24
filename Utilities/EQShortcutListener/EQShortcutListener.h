#pragma once

#include <QWidget>
#include <QString>
#include <QThread>
#include <QVector>
#include <QPushButton>
#include "EQShortcutListenerWorker.h"
#include "../EQKeyboardListener/EQKeyboardListener.h"
#include <QLabel>

class EQShortcutListener : public QWidget
{
	Q_OBJECT

public:
	EQShortcutListener(QString labelText, QWidget *parent = nullptr);
	~EQShortcutListener();

	QVector<int> getTargetKeys() const;
	void setTargetKeys(QVector<int>& targetKeys);
public slots:
	void startListening();
	void stopListening();
	void disableButton();
	void enableButton();

signals:
	void startedChangingShortcut();
	void stoppedChangingShortcut();
	void shortcutPressed();
	
private slots:
	void shortcutChosen();
	void changingShortcut();
	void shortcutReady(QVector<int> virtualKeys);

private:
	QThread workerThread;
	EQShortcutListenerWorker* worker;
	EQKeyboardListener* keyboardListener;
	QPushButton* changeShortcutButton;
	bool isListening;
};
