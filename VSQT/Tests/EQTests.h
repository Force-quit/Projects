#pragma once

#include <QMainWindow>

class EQTests : public QMainWindow
{
	Q_OBJECT

public:
	EQTests();
private:
	QWidget* intLineEditTest();
	QWidget* textValidatorTest();
	QWidget* shortcutPickerTest();
};
