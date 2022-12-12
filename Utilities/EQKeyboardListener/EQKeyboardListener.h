#pragma once

#include <QWidget>
#include <unordered_map>
#include <QString>

class EQKeyboardListener : public QWidget
{
	Q_OBJECT

public:
    enum VIRTUAL_KEY {
		LCONTROL = 0xA2
    };
	
	EQKeyboardListener(VIRTUAL_KEY key, unsigned short checkInterval = 50);
	~EQKeyboardListener();

	void setTargetKey(VIRTUAL_KEY newKey);
	void setCheckInterval(unsigned short newInterval);

signals:
	void keyPressed();

private slots:
	void check();

private:
	static const std::unordered_map<int, QString> VK_NAME;

	VIRTUAL_KEY targetKey;
	unsigned short checkInterval;
	bool isPressing;
};