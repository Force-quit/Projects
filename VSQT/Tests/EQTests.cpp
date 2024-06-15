#include "EQTests.h"

#include "../EQUtilities/EQIntLineEdit.h"
#include "../EQUtilities/EQTextValidator.h"
#include "../EQUtilities/EQShortcutPicker.h"
#include <QVBoxLayout>
#include <QLineEdit>

EQTests::EQTests()
{
	setCentralWidget(shortcutPickerTest());
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
	QLineEdit* centralWidget{ new QLineEdit };
	centralWidget->setValidator(new EQTextValidator);
	return centralWidget;
}

QWidget* EQTests::shortcutPickerTest()
{
	EQShortcutPicker* centralWidget{ new EQShortcutPicker("Activate testing mode :") };
	centralWidget->startListening();
	connect(centralWidget, &EQShortcutPicker::shortcutPressed, [] {
		static std::uint8_t counter{};
		qDebug() << "Shortcut pressed " << ++counter;
	});
	return centralWidget;
}