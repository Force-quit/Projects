#include "EQTests.h"
#include <EQUtilities/EQShortcutPicker.h>

EQTests::EQTests()
	: QMainWindow()
{
	EQShortcutPicker* centralWidget{ new EQShortcutPicker("Activate bot")};
	QVector<eutilities::Key> keys{eutilities::LEFT_CLICK, eutilities::RIGHT_CLICK};
	centralWidget->setTargetKeys(keys);
	centralWidget->startListening();

	connect(centralWidget, &EQShortcutPicker::shortcutPressed, [centralWidget] {
		auto i = centralWidget->getTargetKeys();
		i.size();
	});
	setCentralWidget(centralWidget);
}