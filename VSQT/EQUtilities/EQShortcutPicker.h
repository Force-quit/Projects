#pragma once

import eutilities;
import EShortcutListener;

#include <QWidget>
#include <QString>
#include <thread>
#include <QVector>
#include <QPushButton>
#include <QLabel>
#include <string_view>
#include <span>
#include <string>
#include <set>

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
	void disableButton();
	void enableButton();

signals:
	void startedChangingShortcut();
	void stoppedChangingShortcut();
	void shortcutPressed();
	
private slots:
	void startChangingShortcut();
	void changeShortcut();

signals:
	void finishedChangingShortcut();

private:
	static constexpr eutilities::Key DEFAULT_KEY{ eutilities::RIGHT_CONTROL };
	static constexpr clock_t SHORTCUT_HOLD_TIME{ 3000 };

	void shortcutTextChanged(const std::set<eutilities::Key>& strings);
	void changingShortcutLoop(std::stop_token stopToken);
	void waitForShortcutRelease(const std::vector<eutilities::Key>& keys);

	bool wasListening;
	std::jthread mShortcutSetterThread;
	QPushButton* changeShortcutButton;
	QLabel* mShortcutLabel;
};
