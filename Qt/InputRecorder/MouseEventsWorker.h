#pragma once

#include <QObject>
#include <QVector>
#include <QSet>
#include <QHash>

#include "EQMouseClickEvent.h"
#include "EQMouseMoveEvent.h"

class MouseEventsWorker : public QObject
{
	Q_OBJECT

public:
	MouseEventsWorker(clock_t& currentRecTime);
	void stopListening();
	bool isReadyToShare() const;
	QVector<EQMouseClickEvent> getMouseClickEvents() const;
	QVector<EQMouseMoveEvent> getMouseMoveEvents() const;

public slots:
	void startListening();

private:
	const clock_t& currentRecTime;
	bool continueListening;
	bool readyToShare;

	const QHash<uint8_t, DWORD> keyUpFlags;
	const QHash<uint8_t, DWORD> keyDownFlags;
	const QHash<uint8_t, DWORD> mouseData;

	POINT lastMousePos;
	POINT tempMousePos; 

	QVector<EQMouseClickEvent> mouseClickEvents;
	QSet<uint8_t> mousePressedKeys;
	QVector<uint8_t> mouseKeysToRemove;
	void checkMouseClickEvents();

	QVector<EQMouseMoveEvent> mouseMoveEvents;
	void checkMouseMoveEvents();

	void reset();
	

	const QVector<uint8_t> MOUSE_CLICK_VK;
};