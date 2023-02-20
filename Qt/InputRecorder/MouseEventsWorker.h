#pragma once

#include <QObject>
#include <vector>
#include <set>
#include <QVector>

#include "MouseClickEvent.h"
#include "MouseMoveEvent.h"

class MouseEventsWorker : public QObject
{
	Q_OBJECT

public:
	MouseEventsWorker(clock_t& currentRecTime);
	void stopListening();

public slots:
	void startListening();

signals:
	void mouseClickEventsReady(QVector<MouseClickEvent>& mouseClickEvents);
	void mouseMoveEventsReady(QVector<MouseMoveEvent>& mouseMoveEvents);

private:
	const clock_t& currentRecTime;
	bool continueListening;

	QVector<MouseClickEvent> mouseClickEvents;
	std::set<uint8_t> mousePressedKeys;
	std::vector<uint8_t> mouseKeysToRemove;
	void checkMouseClickEvents();

	QVector<MouseMoveEvent> mouseMoveEvents;
	void checkMouseMoveEvents();

	const std::vector<uint8_t> MOUSE_CLICK_VK;
};