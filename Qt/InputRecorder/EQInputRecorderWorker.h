#pragma once

#include <QObject>
#include <QString>
#include <vector>
#include "Event.h"
#include <set>
#include <Windows.h>
#include "MouseEventsHandler.h"
#include <QThread>

class EQInputRecorderWorker  : public QObject
{
	Q_OBJECT

public:
	EQInputRecorderWorker();
	~EQInputRecorderWorker();

public slots:
	void startRecording();
	void startPlayback();

signals:
	void textChanged(const QString& newText);

private:

signals:
	void startListening();

private:
	const uint8_t COUNTDOWN{ 3 };
	void setupTimers(const bool recording);

	void startRealRecording();
	void startRealPlayBack();

	std::vector<Event> allEvents;

	QThread mouseEventsThread;
	MouseEventsHandler* mouseEventsWorker;
	bool continueListening;
	clock_t currentRecordingTime;

	const std::vector<uint8_t> KEYBOARD_VK
	{ 
		VK_BACK,
		VK_TAB,
		VK_CLEAR,
		VK_RETURN,
		VK_SHIFT,
		VK_CONTROL,
		VK_LWIN,
		VK_MENU,
		VK_PAUSE,
		VK_CAPITAL,
		VK_ESCAPE,
		VK_SPACE,
		VK_PRIOR,
		VK_NEXT,
		VK_END,
		VK_HOME,
		VK_SELECT,
		VK_PRINT,
		VK_EXECUTE,
		VK_SNAPSHOT,
		VK_INSERT,
		VK_DELETE,
		VK_HELP,
		VK_LEFT,
		VK_UP,
		VK_RIGHT,
		VK_DOWN,
		0x31, // 1 key
		0x32, // 2 key
		0x33, // 3 key
		0x34, // 4 key
		0x35, // 5 key
		0x36, // 6 key
		0x37, // 7 key
		0x38, // 8 key
		0x39, // 9 key
		0x30, // 0 key
		VK_OEM_MINUS,
		VK_OEM_PLUS,
		0x41,	// A key
		0x42,	// B key
		0x43,	// C key
		0x44,	// D key
		0x45,	// E key
		0x46,	// F key
		0x47,	// G key
		0x48,	// H key
		0x49,	// I key
		0x4A,	// J key
		0x4B,	// K key
		0x4C,	// L key
		0x4D,	// M key
		0x4E,	// N key
		0x4F,	// O key
		0x50,	// P key
		0x51,	// Q key
		0x52,	// R key
		0x53,	// S key
		0x54,	// T key
		0x55,	// U key
		0x56,	// V key
		0x57,	// W key
		0x58,	// X key
		0x59,	// Y key
		0x5A,	// Z key
		VK_OEM_COMMA,
		VK_OEM_PERIOD,
		VK_OEM_1, // ;:~
		VK_OEM_2, // È… ¥¥
		VK_OEM_3, // `` { 
		VK_OEM_4, // ^[
		VK_OEM_5, // <> }
		VK_OEM_6, // ∏ Á ® ]
		VK_OEM_7, // #| 
		VK_OEM_8,
		VK_OEM_102,
		VK_NUMPAD0, // Numeric keypad 0 key
		VK_NUMPAD1, // Numeric keypad 1 key
		VK_NUMPAD2, // Numeric keypad 2 key
		VK_NUMPAD3, // Numeric keypad 3 key
		VK_NUMPAD4, // Numeric keypad 4 key
		VK_NUMPAD5, // Numeric keypad 5 key
		VK_NUMPAD6, // Numeric keypad 6 key
		VK_NUMPAD7, // Numeric keypad 7 key
		VK_NUMPAD8, // Numeric keypad 8 key
		VK_NUMPAD9, // Numeric keypad 9 key
		VK_MULTIPLY,	// Multiply key
		VK_ADD,		// Add key
		VK_SEPARATOR,	// Separator key
		VK_SUBTRACT,  // Subtract key
		VK_DECIMAL,	// Decimal key
		VK_DIVIDE,		// Divide key
		VK_F1,
		VK_F2,
		VK_F3,
		VK_F4,
		VK_F5,
		VK_F6,
		VK_F7,
		VK_F8,
		VK_F9,
		VK_F10,
		VK_F11,
		VK_F12 };
};