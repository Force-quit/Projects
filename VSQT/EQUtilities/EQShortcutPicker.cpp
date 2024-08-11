#include "EQShortcutPicker.h"

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

EQShortcutPicker::EQShortcutPicker(QString iShortcutTriggerText)
	: mShortcutLabel{ new QLabel(eutilities::nameOf(DEFAULT_KEY).c_str()) }
{
	QHBoxLayout* centralLayout{ new QHBoxLayout };
	QLabel* widgetName{ new QLabel(iShortcutTriggerText) };

	centralLayout->addWidget(widgetName);
	centralLayout->addWidget(mShortcutLabel);

	mChangeShortcutButton->setFocusPolicy(Qt::NoFocus);
	centralLayout->addWidget(mChangeShortcutButton);

	setLayout(centralLayout);

	mShortcutListener.setTargetKeys(DEFAULT_KEY);

	connect(mChangeShortcutButton, &QPushButton::clicked, this, &EQShortcutPicker::startChangingShortcut);
	connect(mChangeShortcutButton, &QPushButton::clicked, mChangeShortcutButton, &QWidget::setEnabled);
	connect(this, &EQShortcutPicker::shortcutSelected, this, &EQShortcutPicker::enableButton);
}

void EQShortcutPicker::startChangingShortcut()
{
	emit startedChangingShortcut();
	mWasListening = mShortcutListener.isListening();
	mShortcutListener.stopListening();
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
			mPressedKeys.push_back(eutilities::keys[keyIndex]);
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

	while (!stopToken.stop_requested())
	{
		for (std::size_t i{}; i < eutilities::keys.size(); ++i)
		{
			processKey(timerStart, i);
		}
		
		if (mPressedKeys.size() > 0 && std::clock() - timerStart >= SHORTCUT_HOLD_TIME)
		{
			break;
		}

		eutilities::sleepFor(5);
	}

	if (!stopToken.stop_requested())
	{
		emit shortcutSelected();
		waitForShortcutRelease(mPressedKeys);
		mShortcutListener.setTargetKeys(mPressedKeys);
		if (mWasListening)
		{
			startListening();
		}
		emit stoppedChangingShortcut();
	}
}

void EQShortcutPicker::waitForShortcutRelease(std::span<const eutilities::Key> keys)
{
	auto it(keys.cbegin());
	while (eutilities::isPressed(*it))
	{
		++it;
		
		if (it == keys.cend())
		{
			it = keys.cbegin();
		}

		eutilities::sleepFor(5);
	}
}

void EQShortcutPicker::updateShortcutText(std::span<const eutilities::Key> strings)
{
	std::string newText;

	for (auto i : strings)
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
	mShortcutListener.startListening([this] {emit shortcutPressed(); });
}

void EQShortcutPicker::stopListening()
{
	mShortcutListener.stopListening();
}

void EQShortcutPicker::disableButton()
{
	mChangeShortcutButton->setEnabled(false);
}

std::vector<eutilities::Key> EQShortcutPicker::targetKeys() const
{
	return mShortcutListener.targetKeys();
}

void EQShortcutPicker::setTargetKeys(std::span<const eutilities::Key> targetKeys)
{
	mShortcutListener.setTargetKeys(targetKeys);
	updateShortcutText(targetKeys);
}
