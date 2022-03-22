#include "inputRecorder.h"
#include <vector>
#include <Windows.h>
#include <iostream>
#include <limits>

MousePoint::MousePoint(POINT& currentPoint, long timePos)
	: p(currentPoint), eventPositionInTime(timePos)
{

}

MousePoint::MousePoint() {}

KeyBoardEvent::KeyBoardEvent(bool type, short keyCode, short flags, long timePos)
	: type(type), keyCode(keyCode), flags(flags), eventPositionInTime(timePos)
{

}

KeyBoardEvent::KeyBoardEvent() {}

long record(std::vector<MousePoint>& mousePoints, std::vector<KeyBoardEvent>& keyboardEvents, std::vector<short>& vKeys)
{
	MousePoint* lastMousePoint{};
	mousePoints.push_back(MousePoint());
	lastMousePoint = &mousePoints.front();
	POINT currentMousePoint{};

	std::vector<short> pressedKeys{};

	std::clock_t start{};
	long currentTime{};

	Sleep(3000);
	start = std::clock();
	GetCursorPos(&lastMousePoint->p);
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		currentTime = std::clock() - start;
		std::cout << currentTime << std::endl;

		GetCursorPos(&currentMousePoint);
		if (currentMousePoint.x != lastMousePoint->p.x || currentMousePoint.y != lastMousePoint->p.y)
		{
			mousePoints.push_back(MousePoint(currentMousePoint, currentTime));
			lastMousePoint = &mousePoints.back();
		}

		for (short i = 0; i < vKeys.size(); i++)
		{
			short vKey = vKeys[i];

			if (GetAsyncKeyState(vKey))
			{
				short wasAlreadyPressing{};
				for (short i = 0; i < pressedKeys.size(); ++i)
				{
					if (vKey == pressedKeys[i])
					{
						wasAlreadyPressing = true;
						break;
					}
				}

				if (wasAlreadyPressing)
					continue;
				else
					pressedKeys.push_back(vKey);

				bool type = true;
				switch (vKey)
				{
				case VK_LBUTTON:
				case VK_RBUTTON:
				case VK_MBUTTON:
				case VK_XBUTTON1:
				case VK_XBUTTON2:
					type = false;
					break;
				}

				keyboardEvents.push_back(KeyBoardEvent(type, vKey, 0, currentTime));
			}
			else
			{
				for (short i = 0; i < pressedKeys.size(); ++i)
				{
					if (vKey == pressedKeys[i])
					{
						bool type = true;
						switch (vKey)
						{
						case VK_LBUTTON:
						case VK_RBUTTON:
						case VK_MBUTTON:
						case VK_XBUTTON1:
						case VK_XBUTTON2:
							type = false;
							break;
						}

						keyboardEvents.push_back(KeyBoardEvent(type, vKey, KEYEVENTF_KEYUP, currentTime));
						pressedKeys.erase(pressedKeys.begin() + i);
						break;
					}
				}
			}
		}

		Sleep(1);
	}
	return std::clock() - start;
}

void play(std::vector<MousePoint>& mousePoints, std::vector<KeyBoardEvent>& keyboardEvents, long totalTime)
{
	POINT mousePos{};

	if (mousePoints.size() == 0)
		mousePoints.push_back(MousePoint(mousePos, LONG_MAX));
	
	MousePoint* nextMousePoint{ &mousePoints.front() };

	if (keyboardEvents.size() == 0)
		keyboardEvents.push_back(KeyBoardEvent(0, 0, 0, LONG_MAX));

	KeyBoardEvent nextKeyboardEvent{ keyboardEvents.front() };


	int mousePointIndex = 0;
	int keyboardEventIndex = 0;

	INPUT input{};
	clock_t start{};
	long currentTime{};

	for (start = std::clock(); currentTime <= totalTime; currentTime = std::clock() - start)
	{
		std::cout << currentTime << std::endl;
		if (currentTime >= nextMousePoint->eventPositionInTime)
		{
			SetCursorPos(nextMousePoint->p.x, nextMousePoint->p.y);
			++mousePointIndex;
			mousePointIndex %= mousePoints.size();
			nextMousePoint = &mousePoints[mousePointIndex];
		}

		if (currentTime >= nextKeyboardEvent.eventPositionInTime)
		{
			input.type = nextKeyboardEvent.type;
			if (nextKeyboardEvent.type)
			{
				input.ki.dwFlags = nextKeyboardEvent.flags;
				input.ki.wVk = nextKeyboardEvent.keyCode;
			}
			else
			{
				GetCursorPos(&mousePos);
				input.mi.dwFlags = nextKeyboardEvent.flags;
				input.mi.dx = mousePos.x;
				input.mi.dy = mousePos.y;
			}
			SendInput(1, &input, sizeof(INPUT));
			++keyboardEventIndex;
			keyboardEventIndex %= keyboardEvents.size();
			nextKeyboardEvent = keyboardEvents[keyboardEventIndex];
		}

		Sleep(1);
	}
}

void fillVirtualKeys(std::vector<short>& vector)
{
	// Mouse
	vector.push_back(VK_LBUTTON);
	vector.push_back(VK_RBUTTON);
	vector.push_back(VK_MBUTTON);
	vector.push_back(VK_XBUTTON1); // Back
	vector.push_back(VK_XBUTTON2); // Next

	// Keyboard
	vector.push_back(VK_BACK);
	vector.push_back(VK_TAB);
	vector.push_back(VK_CLEAR);
	vector.push_back(VK_RETURN);
	vector.push_back(VK_SHIFT);
	vector.push_back(VK_CONTROL);
	vector.push_back(VK_LWIN);
	vector.push_back(VK_MENU);
	vector.push_back(VK_PAUSE);
	vector.push_back(VK_CAPITAL);
	vector.push_back(VK_ESCAPE);
	vector.push_back(VK_SPACE);
	vector.push_back(VK_PRIOR);
	vector.push_back(VK_NEXT);
	vector.push_back(VK_END);
	vector.push_back(VK_HOME);
	vector.push_back(VK_SELECT);
	vector.push_back(VK_PRINT);
	vector.push_back(VK_EXECUTE);
	vector.push_back(VK_SNAPSHOT);
	vector.push_back(VK_INSERT);
	vector.push_back(VK_DELETE);
	vector.push_back(VK_HELP);
	vector.push_back(VK_LEFT);
	vector.push_back(VK_UP);
	vector.push_back(VK_RIGHT);
	vector.push_back(VK_DOWN);

	vector.push_back(0x30); // 0 key
	vector.push_back(0x31); // 1 key
	vector.push_back(0x32); // 2 key
	vector.push_back(0x33); // 3 key
	vector.push_back(0x34); // 4 key
	vector.push_back(0x35); // 5 key
	vector.push_back(0x36); // 6 key
	vector.push_back(0x37); // 7 key
	vector.push_back(0x38); // 8 key
	vector.push_back(0x39); // 9 key

	vector.push_back(0x41);	// A key
	vector.push_back(0x42);	// B key
	vector.push_back(0x43);	// C key
	vector.push_back(0x44);	// D key
	vector.push_back(0x45);	// E key
	vector.push_back(0x46);	// F key
	vector.push_back(0x47);	// G key
	vector.push_back(0x48);	// H key
	vector.push_back(0x49);	// I key
	vector.push_back(0x4A);	// J key
	vector.push_back(0x4B);	// K key
	vector.push_back(0x4C);	// L key
	vector.push_back(0x4D);	// M key
	vector.push_back(0x4E);	// N key
	vector.push_back(0x4F);	// O key
	vector.push_back(0x50);	// P key
	vector.push_back(0x51);	// Q key
	vector.push_back(0x52);	// R key
	vector.push_back(0x53);	// S key
	vector.push_back(0x54);	// T key
	vector.push_back(0x55);	// U key
	vector.push_back(0x56);	// V key
	vector.push_back(0x57);	// W key
	vector.push_back(0x58);	// X key
	vector.push_back(0x59);	// Y key
	vector.push_back(0x5A);	// Z key

	vector.push_back(VK_NUMPAD0); // Numeric keypad 0 key
	vector.push_back(VK_NUMPAD1); // Numeric keypad 1 key
	vector.push_back(VK_NUMPAD2); // Numeric keypad 2 key
	vector.push_back(VK_NUMPAD3); // Numeric keypad 3 key
	vector.push_back(VK_NUMPAD4); // Numeric keypad 4 key
	vector.push_back(VK_NUMPAD5); // Numeric keypad 5 key
	vector.push_back(VK_NUMPAD6); // Numeric keypad 6 key
	vector.push_back(VK_NUMPAD7); // Numeric keypad 7 key
	vector.push_back(VK_NUMPAD8); // Numeric keypad 8 key
	vector.push_back(VK_NUMPAD9); // Numeric keypad 9 key

	vector.push_back(VK_MULTIPLY);	// Multiply key
	vector.push_back(VK_ADD);		// Add key
	vector.push_back(VK_SEPARATOR);	// Separator key
	vector.push_back(VK_SUBTRACT);	// Subtract key
	vector.push_back(VK_DECIMAL);	// Decimal key
	vector.push_back(VK_DIVIDE);		// Divide key

	vector.push_back(VK_F1);	 // F1 key
	vector.push_back(VK_F2);	 // F2 key
	vector.push_back(VK_F3);	 // F3 key
	vector.push_back(VK_F4);	 // F4 key
	vector.push_back(VK_F5);	 // F5 key
	vector.push_back(VK_F6);	 // F6 key
	vector.push_back(VK_F7);	 // F7 key
	vector.push_back(VK_F8);	 // F8 key
	vector.push_back(VK_F9);	 // F9 key
	vector.push_back(VK_F10); // F10 key
	vector.push_back(VK_F11); // F11 key
	vector.push_back(VK_F12); // F12 key
}