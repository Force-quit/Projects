#pragma once

#include <QTabWidget>
#include <QTabBar>

class EQTabWidget : public QTabWidget
{
	Q_OBJECT

public:
	EQTabWidget(QWidget* parent = nullptr);
	~EQTabWidget();

	void lock();
	void unlock();

private:
	bool locked;
	int previousTab;
private slots:
	void checkIfLocked(int index);
};
