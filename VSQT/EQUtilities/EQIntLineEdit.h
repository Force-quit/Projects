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

private:
	int mLastValue;

private slots:
	void verifyValue();

protected:
	void focusOutEvent(QFocusEvent* e) override;
};
