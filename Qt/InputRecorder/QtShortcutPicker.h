#pragma once

#include <QObject>
#include <QString>
#include <vector>
#include <QLabel>

class QtShortcutPicker  : public QObject
{
	Q_OBJECT
	
	static const std::unordered_map<int, QString> VIRTUAL_KEYS;

public slots:
	void listenForInput();

signals:
	void shortcutChosen(const std::vector<int> pressedKeys);
	void shortcutChanged(const QString shortcutText);
};
