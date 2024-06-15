#include "EQTests.h"

#include "../EQUtilities/EQIntLineEdit.h"
#include "../EQUtilities/EQTextValidator.h"
#include <QVBoxLayout>
#include <QLineEdit>

EQTests::EQTests()
{
	setCentralWidget(textValidatorTest());
}

QWidget* EQTests::intLineEditTest()
{
	QWidget* centralWidget{ new QWidget() };
	QVBoxLayout* layout{ new QVBoxLayout() };

	EQIntLineEdit* intLineEdit{ new EQIntLineEdit(10, 100) };
	layout->addWidget(intLineEdit);
	EQIntLineEdit* intLineEdit2{ new EQIntLineEdit(-10, 100) };
	layout->addWidget(intLineEdit2);

	centralWidget->setLayout(layout);
	return centralWidget;
}

QWidget* EQTests::textValidatorTest()
{
	QLineEdit* lineEdit{ new QLineEdit };
	lineEdit->setValidator(new EQTextValidator);
	return lineEdit;
}