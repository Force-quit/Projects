#pragma once

#pragma warning(disable:5050)
import eutilities;

#include <QWidget>
#include <QString>
#include <QVector>
#include <vector>
#include <thread>
#include <QPushButton>
#include <QLabel>
#include <array>

class EQShortcutPicker : public QWidget
{
	Q_OBJECT

public:
	EQShortcutPicker(QString labelText);

	[[nodiscard]] QVector<eutilities::Key> getTargetKeys() const;
	void setTargetKeys(const QVector<eutilities::Key>& targetKeys);

public slots:
	void startListening();
	void stopListening();

signals:
	void startedChangingShortcut();
	void stoppedChangingShortcut();
	void shortcutPressed();
	
private slots:
	void startChangingShortcut();
	void enableButton();

signals:
	void shortcutSelected();

private:
	static constexpr eutilities::Key DEFAULT_KEY{ eutilities::RIGHT_CONTROL };
	static constexpr clock_t SHORTCUT_HOLD_TIME{ 3000 };

	void updateShortcutText(const std::vector<eutilities::Key>& strings);
	void processKey(std::clock_t& timer, std::size_t keyIndex);
	void changingShortcutLoop(std::stop_token stopToken);
	void waitForShortcutRelease(const std::vector<eutilities::Key>& keys);

	bool wasListening;
	std::jthread mShortcutSetterThread;
	QPushButton* mChangeShortcutButton;
	QLabel* mShortcutLabel;
	std::array<bool, eutilities::keys.size()> mPressedKeysIndicator;
	std::vector<eutilities::Key> mPressedKeys;
};
