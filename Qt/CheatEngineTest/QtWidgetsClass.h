#pragma once

#include <QMainWindow>
#include <QBoxLayout>
#include <QLabel>

class QtWidgetsClass : public QMainWindow
{
	Q_OBJECT

public:
	QtWidgetsClass(QWidget *parent = nullptr);
	~QtWidgetsClass();

private slots:
	void refreshLabel();
private:
	const int MONEY_INCREMENT{ 100 };
	int money;
	QLabel* moneyLabel;
	QHBoxLayout* initButtonsLayout();
	QHBoxLayout* initLabelsLayout();
};
