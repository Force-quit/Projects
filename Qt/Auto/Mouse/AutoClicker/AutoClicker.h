#pragma once

#include <QMainWindow>
#include "ui_AutoClicker.h"

class AutoClicker : public QMainWindow
{
	Q_OBJECT

public:
	AutoClicker(QWidget* parent = nullptr);
private:
	Ui::AutoClickerClass ui;
};