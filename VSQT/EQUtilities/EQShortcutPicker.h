#pragma once

#pragma warning(disable:5050)
import eutilities;
import EShortcutListener;

#include <array>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <span>
#include <thread>
#include <vector>

class EQShortcutPicker : public QWidget
{
	Q_OBJECT

public:
	EQShortcutPicker(QString iShortcutTriggerText);

	[[nodiscard]] std::vector<eutilities::Key> targetKeys() const;

	void setTargetKeys(std::span<const eutilities::Key> targetKeys);

public slots:
	void startListening();
	void stopListening();
	void disableButton();
	void enableButton();

signals:
	void startedChangingShortcut();
	void stoppedChangingShortcut();
	void shortcutPressed();

private slots:
	void startChangingShortcut();

signals:
	void shortcutSelected();

private:
	static constexpr eutilities::Key DEFAULT_KEY{ eutilities::RIGHT_CONTROL };
	static constexpr std::clock_t SHORTCUT_HOLD_TIME{ 1500 };

	void updateShortcutText(std::span<const eutilities::Key> keys);
	void processKey(std::clock_t& timer, std::size_t keyIndex);
	void changingShortcutLoop(std::stop_token stopToken);
	void waitForShortcutRelease(std::span<const eutilities::Key> keys);

	std::jthread mShortcutSetterThread;
	std::array<bool, eutilities::keys.size()> mPressedKeysIndicator{};
	std::vector<eutilities::Key> mPressedKeys{};
	QPushButton* mChangeShortcutButton{ new QPushButton("Change") };
	QLabel* mShortcutLabel;
	bool mWasListening{};
	EShortcutListener mShortcutListener;
};