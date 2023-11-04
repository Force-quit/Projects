#include "inputRecorder.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <random>
#include <fstream>
#include <string>

MousePoint::MousePoint(POINT& currentPoint, long timePos)
	: p(currentPoint), eventPositionInTime(timePos)
{

}

MousePoint::MousePoint() {}

KeyboardEvent::KeyboardEvent(short keyCode, short flags, long timePos)
	: keyCode(keyCode), flags(flags), eventPositionInTime(timePos)
{

}

KeyboardEvent::KeyboardEvent() {}

MouseEvent::MouseEvent(long x, long y, long timePos, DWORD mouseData, DWORD flags)
	: x(x), y(y), eventPositionInTime(timePos), mouseData(mouseData), dwFlags(flags)
{

}

MouseEvent::MouseEvent() {}

void recordMouseMovement(std::vector<MousePoint>& mousePoints, const clock_t& recordingTime, const bool& keepRecording)
{
	MousePoint* lastMousePoint{};
	mousePoints.push_back(MousePoint());
	lastMousePoint = &mousePoints.front();
	POINT currentMousePoint{};
	GetCursorPos(&lastMousePoint->p);
	while (keepRecording)
	{
		GetCursorPos(&currentMousePoint);
		if (currentMousePoint.x != lastMousePoint->p.x || currentMousePoint.y != lastMousePoint->p.y)
		{
			mousePoints.push_back(MousePoint(currentMousePoint, recordingTime));
			lastMousePoint = &mousePoints.back();
		}
		Sleep(1);
	}

	if (mousePoints.size() == 1)
		mousePoints.clear();
}

void recordMouseEvents(std::vector<MouseEvent>& mouseEvents, const clock_t& recordingTime, const bool& keepRecording)
{
	std::vector<short> mouseVKeys{};
	fillMouseVirtualKeys(mouseVKeys);
	std::vector<short> pressedMouseKeys{};
	for (short i = 0; i < mouseVKeys.size(); i++)
		GetAsyncKeyState(mouseVKeys[i]);

	while (keepRecording)
	{
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

				POINT p{};
				GetCursorPos(&p);
				mouseEvents.push_back(MouseEvent(p.x, p.y, recordingTime, mouseData, flags));
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

						POINT p{};
						GetCursorPos(&p);
						mouseEvents.push_back(MouseEvent(p.x, p.y, recordingTime, mouseData, flags));

						pressedMouseKeys.erase(pressedMouseKeys.begin() + i);
						break;
					}
				}
			}
		}

		Sleep(1);
	}
}

void recordKeyBoardEvents(std::vector<KeyboardEvent>& keyboardEvents, std::mutex& vectorMutex, const std::vector<short>& vKeys, const clock_t& recordingTime, const bool& keepRecording)
{
	std::vector<short> pressedKeyboardKeys{};
	for (auto vKey : vKeys)
		GetAsyncKeyState(vKey);

	while (keepRecording)
	{
		for (auto vKey : vKeys)
		{
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

				vectorMutex.lock();
				keyboardEvents.push_back(KeyboardEvent(vKey, 0, recordingTime));
				vectorMutex.unlock();
			}
			else
			{
				for (short i = 0; i < pressedKeyboardKeys.size(); ++i)
				{
					if (vKey == pressedKeyboardKeys[i])
					{
						vectorMutex.lock();
						keyboardEvents.push_back(KeyboardEvent(vKey, KEYEVENTF_KEYUP, recordingTime));
						vectorMutex.unlock();

						pressedKeyboardKeys.erase(pressedKeyboardKeys.begin() + i);
						break;
					}
				}
			}
		}

		Sleep(1);
	}
}

void play(std::vector<MousePoint>& mousePoints, std::vector<MouseEvent>& mouseEvents, std::vector<KeyboardEvent>& keyboardEvents, long totalTime)
{
	MousePoint* nextMousePoint{};
	MouseEvent* nextMouseEvent{};
	KeyboardEvent* nextKeyboardEvent{};
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

	std::vector<INPUT> inputsToSend{};

	INPUT keyboardInput{};
	keyboardInput.type = INPUT_KEYBOARD;

	INPUT mouseInput{};
	mouseInput.type = INPUT_MOUSE;

	clock_t start{};
	long currentTime{};

	for (start = std::clock(); currentTime <= totalTime; currentTime = std::clock() - start)
	{
		if (nextMousePoint != nullptr && currentTime >= nextMousePoint->eventPositionInTime)
		{
			SetCursorPos(nextMousePoint->p.x, nextMousePoint->p.y);
			++mousePointIndex;
			if (mousePointIndex < mousePoints.size())
				nextMousePoint = &mousePoints[mousePointIndex];
			else
				nextMousePoint = nullptr;
		}

		if (nextMouseEvent != nullptr && currentTime >= nextMouseEvent->eventPositionInTime)
		{
			mouseInput.mi.dwFlags = nextMouseEvent->dwFlags;
			mouseInput.mi.dx = nextMouseEvent->x;
			mouseInput.mi.dy = nextMouseEvent->y;
			mouseInput.mi.mouseData = nextMouseEvent->mouseData;

			inputsToSend.push_back(mouseInput);

			++mouseEventIndex;
			if (mouseEventIndex < mouseEvents.size())
				nextMouseEvent = &mouseEvents[mouseEventIndex];
			else
				nextMouseEvent = nullptr;
		}

		if (nextKeyboardEvent != nullptr && currentTime >= nextKeyboardEvent->eventPositionInTime)
		{
			keyboardInput.ki.wVk = nextKeyboardEvent->keyCode;
			keyboardInput.ki.dwFlags = nextKeyboardEvent->flags;

			inputsToSend.push_back(keyboardInput);

			++keyboardEventIndex;
			if (keyboardEventIndex < keyboardEvents.size())
				nextKeyboardEvent = &keyboardEvents[keyboardEventIndex];
			else
				nextKeyboardEvent = nullptr;
		}

		if (inputsToSend.size() > 0)
		{
			INPUT* inputs = &inputsToSend[0];
			SendInput(inputsToSend.size(), inputs, sizeof(INPUT));
			inputsToSend.clear();
		}

		Sleep(1);
	}
}

void fillKeyBoardVirtualKeys(std::vector<std::vector<short>>& vector)
{
	const short NB_KEYS_PER_THREAD = 6;
	std::vector<short> KEYBOARD_VKEYS = {
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
		VK_OEM_2, // �� ��
		VK_OEM_3, // `` { 
		VK_OEM_4, // ^[
		VK_OEM_5, // <> }
		VK_OEM_6, // � � � ]
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
		VK_F12
	};

	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(KEYBOARD_VKEYS), std::end(KEYBOARD_VKEYS), rng);

	vector.push_back(std::vector<short>());
	for (short i = 0; i < KEYBOARD_VKEYS.size(); ++i)
	{
		vector.back().push_back(KEYBOARD_VKEYS[i]);
		if (i % NB_KEYS_PER_THREAD == 0)
			vector.push_back(std::vector<short>());
	}
}

void record()
{
	std::vector<std::thread> keyboardThreads{};
	std::vector<std::vector<short>> keyboardThreadsVKeys{};
	fillKeyBoardVirtualKeys(keyboardThreadsVKeys);

	std::vector<MousePoint> mousePoints{};
	std::vector<MouseEvent> mouseEvents{};
	std::vector<KeyboardEvent> keyboardEvents{};
	std::mutex keyboardEventsMutex{};

	bool keepRecording = true;

	std::cout << "Starting in 3..." << std::endl;
	Sleep(1000);
	std::cout << "Starting in 2..." << std::endl;
	Sleep(1000);
	std::cout << "Starting in 1..." << std::endl;
	Sleep(1000);
	std::cout << "Started" << std::endl;

	clock_t start = std::clock();
	clock_t recordingTime = start - std::clock();
	std::thread mouseMovementRecording(recordMouseMovement, std::ref(mousePoints), std::ref(recordingTime), std::ref(keepRecording));
	std::thread mouseInputRecording(recordMouseEvents, std::ref(mouseEvents), std::ref(recordingTime), std::ref(keepRecording));
	for (auto& vKeysSection : keyboardThreadsVKeys)
		keyboardThreads.push_back(std::thread(recordKeyBoardEvents, std::ref(keyboardEvents), std::ref(keyboardEventsMutex),
			std::ref(vKeysSection), std::ref(recordingTime), std::ref(keepRecording)));


	GetAsyncKeyState(VK_ESCAPE);
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		recordingTime = std::clock() - start;
		Sleep(1);
	}

	keepRecording = false;

	mouseMovementRecording.join();
	mouseInputRecording.join();
	for (auto& thread : keyboardThreads)
		thread.join();


	long totalRecordingTime = std::clock() - start;
	std::cout << "Ended recording" << "\n\n";

	if (keyboardEvents.size() > 0)
		if (keyboardEvents.back().keyCode == VK_ESCAPE)
			keyboardEvents.pop_back();

	CreateDirectoryA("SavedSessions", NULL);
	saveTotalRecordingTime(totalRecordingTime);
	saveMouseMovements(mousePoints);
	saveMouseEvents(mouseEvents);
	saveKeyBoardEvents(keyboardEvents);
}

void loadAndPlay()
{
	std::vector<MousePoint> mousePoints;
	std::vector<MouseEvent> mouseEvents;
	std::vector<KeyboardEvent> keyboardEvents;
	long totalRecordingTime{};

	loadTotalRecordingTime(totalRecordingTime);
	if (totalRecordingTime == 0)
	{
		std::cout << "Nothing to play";
		return;
	}

	loadMouseMovements(mousePoints);
	loadMouseEvents(mouseEvents);
	loadKeyboardEvents(keyboardEvents);

	std::cout << "Starting in 3..." << std::endl;
	Sleep(1000);
	std::cout << "Starting in 2..." << std::endl;
	Sleep(1000);
	std::cout << "Starting in 1..." << std::endl;
	Sleep(1000);
	std::cout << "Started playing back" << std::endl;
	play(mousePoints, mouseEvents, keyboardEvents, totalRecordingTime);
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

void saveTotalRecordingTime(const long& totalRecordingtime)
{
	std::ofstream saveFile("SavedSessions\\totalRecordingTime.txt");
	if (saveFile.good())
		saveFile << totalRecordingtime;
	saveFile.close();
}

void loadTotalRecordingTime(long& totalRecordingTime)
{
	std::ifstream saveFile("SavedSessions\\totalRecordingTime.txt");
	if (saveFile.good())
		saveFile >> totalRecordingTime;
	saveFile.close();
}

void saveMouseEvents(std::vector<MouseEvent>& mouseEvents)
{
	std::ofstream saveFile("SavedSessions\\mouseEvents.txt");
	if (saveFile.good())
		for (MouseEvent& e : mouseEvents)
			saveFile << e.x << ',' << e.y << ',' << e.eventPositionInTime << ',' << e.mouseData << ',' << e.dwFlags << ',';
	saveFile.close();
}

void loadMouseEvents(std::vector<MouseEvent>& mouseEvents)
{
	std::ifstream saveFile("SavedSessions\\mouseEvents.txt");
	if (saveFile.good())
	{
		long x{};
		long y{};
		long timePos{};
		DWORD mouseData{};
		DWORD flags{};
		char separator{};
		while (saveFile.peek() != EOF)
		{
			saveFile >> x;
			saveFile >> separator;
			saveFile >> y;
			saveFile >> separator;
			saveFile >> timePos;
			saveFile >> separator;
			saveFile >> mouseData;
			saveFile >> separator;
			saveFile >> flags;
			saveFile >> separator;
			mouseEvents.push_back(MouseEvent(x, y, timePos, mouseData, flags));
		}
	}
	saveFile.close();
}

void saveMouseMovements(std::vector<MousePoint>& mousePoints)
{
	std::ofstream saveFile("SavedSessions\\mousePoints.txt");
	if (saveFile.good())
		for (MousePoint& p : mousePoints)
			saveFile << p.p.x << ',' << p.p.y << ',' << p.eventPositionInTime << ',';
	saveFile.close();
}

void loadMouseMovements(std::vector<MousePoint>& mousePoints)
{
	std::ifstream saveFile("SavedSessions\\mousePoints.txt");
	if (saveFile.good())
	{
		POINT p{};
		long timePos{};
		char separator{};
		while (saveFile.peek() != EOF)
		{
			saveFile >> p.x;
			saveFile >> separator;
			saveFile >> p.y;
			saveFile >> separator;
			saveFile >> timePos;
			saveFile >> separator;
			mousePoints.push_back(MousePoint(p, timePos));
		}
	}
	saveFile.close();
}

void saveKeyBoardEvents(const std::vector<KeyboardEvent>& keyboardEvents)
{
	std::ofstream saveFile("SavedSessions\\keyboardEvents.txt");
	if (saveFile.good())
		for (auto& k : keyboardEvents)
			saveFile << k.keyCode << ',' << k.flags << ',' << k.eventPositionInTime << ',';
	saveFile.close();
}

void loadKeyboardEvents(std::vector<KeyboardEvent>& keyBoardEvents)
{
	std::ifstream saveFile("SavedSessions\\keyboardEvents.txt");
	if (saveFile.good())
	{
		short keyCode{};
		short flags{};
		long timePos{};
		char separator{};
		while (saveFile.peek() != EOF)
		{
			saveFile >> keyCode;
			saveFile >> separator;
			saveFile >> flags;
			saveFile >> separator;
			saveFile >> timePos;
			saveFile >> separator;
			keyBoardEvents.push_back(KeyboardEvent(keyCode, flags, timePos));
		}
	}
	saveFile.close();
}