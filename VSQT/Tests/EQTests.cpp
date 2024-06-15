#include "EQTests.h"

#include "../EQUtilities/EQIntLineEdit.h"

EQTests::EQTests()
	: QMainWindow()
{
	EQIntLineEdit* intLineEdit{ new EQIntLineEdit(10, 100) };
	setCentralWidget(intLineEdit);
}