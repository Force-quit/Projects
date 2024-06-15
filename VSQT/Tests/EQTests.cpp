#include "EQTests.h"
#include <QVBoxLayout>
#include "../EQUtilities/EQIntLineEdit.h"

EQTests::EQTests()
	: QMainWindow()
{
	QWidget* centralWidget{ new QWidget() };
	QVBoxLayout* layout{ new QVBoxLayout() };

	EQIntLineEdit* intLineEdit{ new EQIntLineEdit(10, 100) };
	layout->addWidget(intLineEdit);
	EQIntLineEdit* intLineEdit2{ new EQIntLineEdit(-10, 100) };
	layout->addWidget(intLineEdit2);

	centralWidget->setLayout(layout);
	setCentralWidget(centralWidget);
}