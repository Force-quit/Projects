#include "EQTests.h"

import eutilities;
#include <EQUtilities/EQShortcutPicker.h>

EQTests::EQTests()
	: QMainWindow()
{
	EQShortcutPicker* centralWidget{ new EQShortcutPicker("Activate bot")};
	QVector<eutilities::Key> keys{eutilities::LEFT_CLICK, eutilities::RIGHT_CLICK};
	centralWidget->setTargetKeys(keys);
	centralWidget->startListening();

	connect(centralWidget, &EQShortcutPicker::shortcutPressed, [centralWidget] {
		static int counter{};
		qDebug() << "Shortcut " << ++counter;
	});
	setCentralWidget(centralWidget);
}