#pragma once

#include <QMainWindow>
#include "ui_AutoClicker.h"
#include <QLineEdit>

class AutoClicker : public QMainWindow
{
	Q_OBJECT

public:
	AutoClicker(QWidget* parent = nullptr);
private:
	Ui::AutoClickerClass ui;
};

class MyLineEdit : public QLineEdit
{
	Q_OBJECT

signals:
	void focussed(bool hasFocus);


protected:
	void focusInEvent(QFocusEvent* e) override;
	void focusOutEvent(QFocusEvent* e) override;
};
