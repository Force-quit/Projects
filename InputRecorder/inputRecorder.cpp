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

KeyBoardEvent::KeyBoardEvent(short keyCode, short flags, long timePos)
	: keyCode(keyCode), flags(flags), eventPositionInTime(timePos)
{

}

KeyBoardEvent::KeyBoardEvent() {}

MouseEvent::MouseEvent(long x, long y, long timePos, DWORD mouseData, DWORD flags)
	: x(x), y(y), eventPositionInTime(timePos), mouseData(mouseData), dwFlags(flags)
{

}

MouseEvent::MouseEvent() {}

long record(std::vector<MousePoint>& mousePoints, std::vector<MouseEvent>& mouseEvents, std::vector<KeyBoardEvent>& keyboardEvents)
{
	std::vector<short> mouseVKeys{};
	fillMouseVirtualKeys(mouseVKeys);

	std::vector<short> keyBoardVKeys{};
	fillKeyBoardVirtualKeys(keyBoardVKeys);

	MousePoint* lastMousePoint{};
	mousePoints.push_back(MousePoint());
	lastMousePoint = &mousePoints.front();

	POINT currentMousePoint{};

	std::vector<short> pressedKeyboardKeys{};
	std::vector<short> pressedMouseKeys{};

	std::clock_t start{};
	long currentTime{};

	Sleep(3000);
	start = std::clock();
	GetCursorPos(&lastMousePoint->p);
	std::cout << "Starting" << std::endl;

	for (short i = 0; i < keyBoardVKeys.size(); i++)
	{
		GetAsyncKeyState(keyBoardVKeys[i]);
	}

	for (short i = 0; i < mouseVKeys.size(); i++)
	{
		GetAsyncKeyState(mouseVKeys[i]);
	}

	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		currentTime = std::clock() - start;
		//std::cout << currentTime << std::endl;

		GetCursorPos(&currentMousePoint);
		if (currentMousePoint.x != lastMousePoint->p.x || currentMousePoint.y != lastMousePoint->p.y)
		{
			mousePoints.push_back(MousePoint(currentMousePoint, currentTime));
			lastMousePoint = &mousePoints.back();
		}

		for (short i = 0; i < mouseVKeys.size(); ++i)
		{
			short vKey = mouseVKeys[i];
			if (GetAsyncKeyState(vKey))
			{
				bool wasAlreadyPressing{};
				for (short i = 0; i < pressedMouseKeys.size(); ++i)
				{
					if (vKey == pressedMouseKeys[i])
					{
						wasAlreadyPressing = true;
						break;
					}
				}

				if (wasAlreadyPressing)
					continue;
				else
					pressedMouseKeys.push_back(vKey);

				short mouseData{};
				short flags{};
				switch (vKey)
				{
				case VK_LBUTTON:
					flags = MOUSEEVENTF_LEFTDOWN;
					break;
				case VK_RBUTTON:
					flags = MOUSEEVENTF_RIGHTDOWN;
					break;
				case VK_MBUTTON:
					flags = MOUSEEVENTF_MIDDLEDOWN;
					break;
				case VK_XBUTTON1:
				case VK_XBUTTON2:
					flags = MOUSEEVENTF_XDOWN;
					break;
				}

				if (vKey == VK_XBUTTON1)
					mouseData = XBUTTON1;
				else
					mouseData = XBUTTON2;

				mouseEvents.push_back(MouseEvent(currentMousePoint.x, currentMousePoint.y, currentTime, mouseData, flags));
			}
			else
			{
				for (short i = 0; i < pressedMouseKeys.size(); ++i)
				{
					if (vKey == pressedMouseKeys[i])
					{

						short mouseData{};
						short flags{};
						switch (vKey)
						{
						case VK_LBUTTON:
							flags = MOUSEEVENTF_LEFTUP;
							break;
						case VK_RBUTTON:
							flags = MOUSEEVENTF_RIGHTUP;
							break;
						case VK_MBUTTON:
							flags = MOUSEEVENTF_MIDDLEUP;
							break;
						case VK_XBUTTON1:
						case VK_XBUTTON2:
							flags = MOUSEEVENTF_XUP;
							break;
						}

						if (vKey == VK_XBUTTON1)
							mouseData = XBUTTON1;
						else
							mouseData = XBUTTON2;

						mouseEvents.push_back(MouseEvent(currentMousePoint.x, currentMousePoint.y, currentTime, mouseData, flags));

						pressedMouseKeys.erase(pressedMouseKeys.begin() + i);
						break;
					}
				}
			}
		}

		for (short i = 0; i < keyBoardVKeys.size(); ++i)
		{
			short vKey = keyBoardVKeys[i];

			if (GetAsyncKeyState(vKey))
			{
				bool wasAlreadyPressing{};
				for (short i = 0; i < pressedKeyboardKeys.size(); ++i)
				{
					if (vKey == pressedKeyboardKeys[i])
					{
						wasAlreadyPressing = true;
						break;
					}
				}

				if (wasAlreadyPressing)
					continue;
				else
					pressedKeyboardKeys.push_back(vKey);

				std::cout << std::hex << vKey << " key down" << std::endl;
				keyboardEvents.push_back(KeyBoardEvent(vKey, 0, currentTime));
			}
			else
			{
				for (short i = 0; i < pressedKeyboardKeys.size(); ++i)
				{
					if (vKey == pressedKeyboardKeys[i])
					{
						std::cout << vKey << " key up" << std::endl;
						keyboardEvents.push_back(KeyBoardEvent(vKey, KEYEVENTF_KEYUP, currentTime));
						pressedKeyboardKeys.erase(pressedKeyboardKeys.begin() + i);
						break;
					}
				}
			}
		}

		Sleep(1);
	}
	return std::clock() - start;
}

void play(std::vector<MousePoint>& mousePoints, std::vector<MouseEvent>& mouseEvents, std::vector<KeyBoardEvent>& keyboardEvents, long totalTime)
{
	MousePoint* nextMousePoint{};
	MouseEvent* nextMouseEvent{};
	KeyBoardEvent* nextKeyboardEvent{};
	std::vector<short> keysBeingPressed{};

	if (mousePoints.size() != 0)
		nextMousePoint = &mousePoints.front();

	if (mouseEvents.size() != 0)
		nextMouseEvent = &mouseEvents.front();

	if (keyboardEvents.size() != 0)
		nextKeyboardEvent = &keyboardEvents.front();

	int mousePointIndex = 0;
	int mouseEventIndex = 0;
	int keyboardEventIndex = 0;

	INPUT keyboardInput{};
	keyboardInput.type = INPUT_KEYBOARD;

	INPUT mouseInput{};
	mouseInput.type = INPUT_MOUSE;

	clock_t start{};
	long currentTime{};

	std::cout << "Starting" << std::endl;
	for (start = std::clock(); currentTime <= totalTime; currentTime = std::clock() - start)
	{
		//std::cout << currentTime << std::endl;
		if (nextMousePoint != nullptr && currentTime >= nextMousePoint->eventPositionInTime)
		{
			//std::cout << "Mouse move" << std::endl;

			SetCursorPos(nextMousePoint->p.x, nextMousePoint->p.y);
			++mousePointIndex;
			if (mousePointIndex < mousePoints.size())
				nextMousePoint = &mousePoints[mousePointIndex];
			else
				nextMousePoint = nullptr;
		}

		if (nextMouseEvent != nullptr && currentTime >= nextMouseEvent->eventPositionInTime)
		{
			std::cout << "Mouse event" << std::endl;

			mouseInput.mi.dwFlags = nextMouseEvent->dwFlags;
			mouseInput.mi.dx = nextMouseEvent->x;
			mouseInput.mi.dy = nextMouseEvent->y;
			mouseInput.mi.mouseData = nextMouseEvent->mouseData;

			SendInput(1, &mouseInput, sizeof(INPUT));

			++mouseEventIndex;
			if (mouseEventIndex < mouseEvents.size())
				nextMouseEvent = &mouseEvents[mouseEventIndex];
			else
				nextMouseEvent = nullptr;
		}

		if (nextKeyboardEvent != nullptr && currentTime >= nextKeyboardEvent->eventPositionInTime)
		{
			std::cout << "Keyboard event" << std::endl;
			keyboardInput.ki.wVk = nextKeyboardEvent->keyCode;
			keyboardInput.ki.dwFlags = nextKeyboardEvent->flags;
			/*if (nextKeyboardEvent->flags == 0)
				keysBeingPressed.push_back(nextKeyboardEvent->keyCode);
			else
				for (short i = 0; i < keysBeingPressed.size(); i++)
					if (keysBeingPressed[i] == nextKeyboardEvent->keyCode)
						keysBeingPressed.erase(keysBeingPressed.begin() + i);*/

			SendInput(1, &keyboardInput, sizeof(INPUT));

			++keyboardEventIndex;
			if (keyboardEventIndex < keyboardEvents.size())
				nextKeyboardEvent = &keyboardEvents[keyboardEventIndex];
			else
				nextKeyboardEvent = nullptr;
		}

		/*for (short i = 0; i < keysBeingPressed.size(); i++)
		{
			keyboardInput.ki.wVk = keysBeingPressed[i];
			keyboardInput.ki.dwFlags = 0;
			SendInput(1, &keyboardInput, sizeof(INPUT));
		}*/

		Sleep(1);
	}
}

void fillKeyBoardVirtualKeys(std::vector<short>& vector)
{
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

void fillMouseVirtualKeys(std::vector<short>& vector)
{
	// Mouse
	vector.push_back(VK_LBUTTON);
	vector.push_back(VK_RBUTTON);
	vector.push_back(VK_MBUTTON);
	vector.push_back(VK_XBUTTON1); // Back
	vector.push_back(VK_XBUTTON2); // Next
}
