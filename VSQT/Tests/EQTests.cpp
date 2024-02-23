#include "EQTests.h"
#include <EQUtilities/EQShortcutPicker.h>

EQTests::EQTests()
	: QMainWindow()
{
	EQShortcutPicker* centralWidget{ new EQShortcutPicker("Activate bot")};
	
	centralWidget->startListening();
	connect(centralWidget, &EQShortcutPicker::shortcutPressed, [] {
		qDebug() << "Shortcut activated";
	});
	setCentralWidget(centralWidget);
}