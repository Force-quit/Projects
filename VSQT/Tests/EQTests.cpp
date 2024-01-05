#include "EQTests.h"
#include <QLabel>

EQTests::EQTests()
	: QMainWindow()
{
	QLabel* centralWidget{ new QLabel("Testing123") };
	setCentralWidget(centralWidget);
}