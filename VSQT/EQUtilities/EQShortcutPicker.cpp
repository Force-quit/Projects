#include "EQShortcutPicker.h"

#pragma warning(disable:5050)
import eutilities;
import EShortcutListener;


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
#include <vector>
#include <ranges>

EQShortcutPicker::EQShortcutPicker(QString labelText)
	: QWidget(), mShortcutSetterThread(), mChangeShortcutButton(), mShortcutLabel{}, wasListening{}, mPressedKeys(), mPressedKeysIndicator{}
{
	QHBoxLayout* centralLayout{ new QHBoxLayout };

	QLabel* widgetName{ new QLabel(labelText) };

	mShortcutLabel = new QLabel(eutilities::nameOf(DEFAULT_KEY).c_str());
	mChangeShortcutButton = new QPushButton("Change");
	mChangeShortcutButton->setFocusPolicy(Qt::NoFocus);

	centralLayout->addWidget(widgetName);
	centralLayout->addWidget(mShortcutLabel);
	centralLayout->addWidget(mChangeShortcutButton);

	setLayout(centralLayout);

	EShortcutListener::setTargetKeys(DEFAULT_KEY);
	connect(mChangeShortcutButton, &QPushButton::clicked, this, &EQShortcutPicker::startChangingShortcut);
	connect(mChangeShortcutButton, &QPushButton::clicked, mChangeShortcutButton, &QWidget::setEnabled);
	connect(this, &EQShortcutPicker::shortcutSelected, this, &EQShortcutPicker::enableButton);
}

void EQShortcutPicker::startChangingShortcut()
{
	emit startedChangingShortcut();
	wasListening = EShortcutListener::isListening();
	EShortcutListener::stopListening();
	mShortcutSetterThread = std::jthread(std::bind_front(&EQShortcutPicker::changingShortcutLoop, this));
}

void EQShortcutPicker::processKey(std::clock_t& timer, std::size_t keyIndex)
{
	if (eutilities::isPressed(eutilities::keys[keyIndex]))
	{
		if (!mPressedKeysIndicator[keyIndex])
		{
			timer = std::clock();
			mPressedKeysIndicator[keyIndex] = true;
			mPressedKeys.emplace_back(eutilities::keys[keyIndex]);
			updateShortcutText(mPressedKeys);
		}
	}
	else
	{
		if (mPressedKeysIndicator[keyIndex])
		{
			timer = std::clock();
			mPressedKeysIndicator[keyIndex] = false;
			auto toRemove(std::ranges::remove(mPressedKeys, eutilities::keys[keyIndex]));
			mPressedKeys.erase(toRemove.begin(), toRemove.end());
			updateShortcutText(mPressedKeys);
		}
	}
}

void EQShortcutPicker::enableButton()
{
	mChangeShortcutButton->setEnabled(true);
}

void EQShortcutPicker::changingShortcutLoop(std::stop_token stopToken)
{
	mPressedKeysIndicator.fill(false);
	mPressedKeys.clear();
	std::clock_t timerStart{ std::clock() };
	bool shortcutWasChosen{};

	while (!shortcutWasChosen && !stopToken.stop_requested())
	{
		for (std::size_t i{}; i < eutilities::keys.size(); ++i)
		{
			processKey(timerStart, i);
		}

		shortcutWasChosen = mPressedKeys.size() > 0 && std::clock() - timerStart >= SHORTCUT_HOLD_TIME;
		eutilities::sleepFor(5);
	}

	if (mPressedKeys.size() > 0)
	{
		emit shortcutSelected();
		waitForShortcutRelease(mPressedKeys);
		EShortcutListener::setTargetKeys(mPressedKeys);
		if (wasListening)
		{
			startListening();
		}
		emit stoppedChangingShortcut();
	}
}

void EQShortcutPicker::waitForShortcutRelease(const std::vector<eutilities::Key>& keys)
{
	auto it(keys.cbegin());
	while (eutilities::isPressed(*it))
	{
		++it;
		if (it == keys.cend())
		{
			it = keys.cbegin();
		}

		eutilities::sleepFor(1);
	}
}

void EQShortcutPicker::updateShortcutText(const std::vector<eutilities::Key>& strings)
{
	std::string newText;

	for (auto& i : strings)
	{
		if (!newText.empty())
		{
			newText += " + ";
		}

		newText += eutilities::nameOf(i);
	}

	mShortcutLabel->setText(QString::fromStdString(newText));
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
	auto keys{ EShortcutListener::targetKeys() };
	return QVector<eutilities::Key>(keys.begin(), keys.end());
}

void EQShortcutPicker::setTargetKeys(const QVector<eutilities::Key>& targetKeys)
{
	std::vector<eutilities::Key> keys;
	for (auto i : targetKeys)
	{
		keys.emplace_back(static_cast<eutilities::Key>(i));
	}

	EShortcutListener::setTargetKeys(keys);
	updateShortcutText(keys);
}
