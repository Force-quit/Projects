import eutilities;
import EShortcutListener;

#include "EQShortcutPicker.h"
#include <QString>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <initializer_list>
#include <functional>
#include <QVector>
#include <string_view>
#include <array>
#include <algorithm>
#include <set>

EQShortcutPicker::EQShortcutPicker(QString labelText, QWidget* parent)
	: QWidget(parent), mShortcutSetterThread(), changeShortcutButton(), mShortcutLabel{}, wasListening{}
{
	QHBoxLayout* centralLayout{ new QHBoxLayout };

	QLabel* widgetName{ new QLabel(labelText) };

	mShortcutLabel = new QLabel(eutilities::nameOf(DEFAULT_KEY).value().c_str());
	changeShortcutButton = new QPushButton("Change");

	centralLayout->addWidget(widgetName);
	centralLayout->addWidget(mShortcutLabel);
	centralLayout->addWidget(changeShortcutButton);

	setLayout(centralLayout);

	EShortcutListener::setTargetKeys({ eutilities::Key::RIGHT_CONTROL });
	connect(changeShortcutButton, &QPushButton::clicked, this, &EQShortcutPicker::startChangingShortcut);
	connect(this, &EQShortcutPicker::finishedChangingShortcut, this, &EQShortcutPicker::changeShortcut);
}

void EQShortcutPicker::startChangingShortcut()
{
	changeShortcutButton->setEnabled(false);
	emit startedChangingShortcut();
	wasListening = EShortcutListener::isListening();
	EShortcutListener::stopListening();
	mShortcutSetterThread = std::jthread(std::bind_front(&EQShortcutPicker::changingShortcutLoop, this));
}

void EQShortcutPicker::changingShortcutLoop(std::stop_token stopToken)
{
	std::array<bool, eutilities::keys.size()> pressedKeys{};
	int8_t nbPressedKeys{};
	std::clock_t timerStart{ std::clock() };
	std::set<std::string> pressedKeysStrings;

	while (!stopToken.stop_requested())
	{
		for (size_t i{}; i < eutilities::keys.size(); ++i)
		{
			if (eutilities::isPressed(eutilities::keys[i]))
			{
				if (!pressedKeys[i])
				{
					++nbPressedKeys;
					timerStart = std::clock();
					pressedKeys[i] = true;
					pressedKeysStrings.insert(eutilities::nameOf(eutilities::keys[i]).value());
					shortcutTextChanged(pressedKeysStrings);
				}
			}
			else
			{
				if (pressedKeys[i])
				{
					--nbPressedKeys;
					timerStart = std::clock();
					pressedKeys[i] = false;
					pressedKeysStrings.erase(eutilities::nameOf(eutilities::keys[i]).value());
					shortcutTextChanged(pressedKeysStrings);
				}

			}
		}

		if (nbPressedKeys > 0 && std::clock() - timerStart >= SHORTCUT_HOLD_TIME)
		{
			break;
		}

		eutilities::sleepFor(5);
	}

	if (nbPressedKeys > 0)
	{
		std::vector<eutilities::Key> keys;
		for (size_t i{}; i < pressedKeys.size(); ++i)
		{
			if (pressedKeys[i])
			{
				keys.emplace_back(eutilities::keys[i]);
			}
		}
		emit finishedChangingShortcut();

		waitForShortcutRelease(keys);
		EShortcutListener::setTargetKeys(keys);
		if (wasListening)
		{
			startListening();
		}
	}
}

void EQShortcutPicker::waitForShortcutRelease(const std::vector<eutilities::Key>& keys)
{
	auto it(keys.cbegin());
	while (eutilities::isPressed(*it))
	{
		eutilities::sleepFor(1);
		++it;
		if (it == keys.cend())
		{
			it = keys.cbegin();
		}
	}
}

void EQShortcutPicker::shortcutTextChanged(const std::set<std::string>& strings)
{
	std::string newText;

	for (auto& i : strings)
	{
		newText += i + " + ";
	}

	if (newText.size() > 0)
	{
		newText.erase(newText.rfind(" + "));
	}
	
	mShortcutLabel->setText(QString::fromStdString(newText));
}

void EQShortcutPicker::changeShortcut()
{
	emit stoppedChangingShortcut();
	enableButton();
}

void EQShortcutPicker::disableButton()
{
	changeShortcutButton->setDisabled(true);
}

void EQShortcutPicker::enableButton()
{
	changeShortcutButton->setEnabled(true);
}

void EQShortcutPicker::startListening()
{
	EShortcutListener::startListening([=] {emit shortcutPressed(); });
}

void EQShortcutPicker::stopListening()
{
	EShortcutListener::stopListening();
}

QVector<eutilities::Key> EQShortcutPicker::getTargetKeys() const
{
	auto v{ EShortcutListener::targetKeys() };
	return QVector<eutilities::Key>(v.begin(), v.end());
}

void EQShortcutPicker::setTargetKeys(QVector<int>& targetKeys)
{
	//keyboardListener->setTargetKeys(targetKeys);
	// TODO change text
}
