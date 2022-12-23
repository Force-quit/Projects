#pragma once

#include <QWidget>
#include <unordered_map>
#include <QString>
#include <QVector>

class EQKeyboardListener : public QWidget
{
	Q_OBJECT

public:
	EQKeyboardListener(QVector<int> targetKeys, unsigned short checkInterval = 50);
	~EQKeyboardListener();

public slots:
	void setTargetKeys(QVector<int> virtualKeys);
	void stopListening();
	void startListening();

signals:
	void targetKeysPressed();

private slots:
	void check();

private:
	QVector<int> targetKeys;
	const unsigned short checkInterval;
	unsigned short pressedKeys;
	bool canTrigger;

	bool listening;
};