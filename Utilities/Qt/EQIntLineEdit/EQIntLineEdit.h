#pragma once

#include <QLineEdit>

class EQIntLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	EQIntLineEdit(int minimum, int maximum, QWidget *parent = nullptr);
	~EQIntLineEdit();

signals:
	void valueChanged(int newValue);

private slots:
	void emitValueChanged();
};
