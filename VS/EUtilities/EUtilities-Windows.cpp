module;

#include <Windows.h>
#include <string_view>
#include <optional>

module eutilities:windows;

void eutilities::waitForFullKeyPress(int vKey)
{
	GetAsyncKeyState(vKey); // Reset buffer

	eutilities::waitForKeyPress(vKey);

	eutilities::waitForKeyRelease(vKey);
}

void eutilities::waitForKeyPress(int vKey)
{
	while (!GetAsyncKeyState(vKey))
		Sleep(50);
}

void eutilities::waitForKeyRelease(int vKey)
{
	while (GetAsyncKeyState(vKey))
		Sleep(50);
}

void eutilities::Console::hideCursor()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor{};
	lpCursor.bVisible = false;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

/**************************/
/*     KEYBOARD UTILS     */
/**************************/

void eutilities::pressKey(char key)
{
	short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	eutilities::pressKey(keyCode);
}

void eutilities::pressKey(int keyCode)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;

	eutilities::pressKey(i);
}

void eutilities::pressKey(INPUT& input)
{
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
}

void eutilities::releaseKey(char key)
{
	short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	eutilities::releaseKey(keyCode);
}

void eutilities::releaseKey(int keyCode)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;
	eutilities::releaseKey(i);
}

void eutilities::releaseKey(INPUT& input)
{
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

void eutilities::fullKeyPress(char key, unsigned int pressDuration)
{
	short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	eutilities::fullKeyPress(keyCode, pressDuration);
}

void eutilities::fullKeyPress(int keyCode, unsigned int pressDuration)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;
	eutilities::fullKeyPress(i, pressDuration);
}

void eutilities::fullKeyPress(INPUT& input, unsigned int pressDuration)
{
	eutilities::pressKey(input);
	Sleep(pressDuration);
	eutilities::releaseKey(input);
}

void eutilities::ctrlV()
{
	const short NB_INPUTS = 4;

	INPUT inputs[NB_INPUTS]{};

	for (INPUT& i : inputs)
		i.type = INPUT_KEYBOARD;

	inputs[0].ki.wVk = VK_CONTROL;
	inputs[1].ki.wVk = 0x56;

	inputs[2].ki.wVk = 0x56;
	inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

	inputs[3].ki.wVk = VK_CONTROL;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(NB_INPUTS, inputs, sizeof(INPUT));
}

void eutilities::winR()
{
	const short NB_INPUTS = 4;

	INPUT inputs[NB_INPUTS]{};

	for (INPUT& i : inputs)
		i.type = INPUT_KEYBOARD;

	inputs[0].ki.wVk = VK_LWIN;
	inputs[1].ki.wVk = 0x52;

	inputs[2].ki.wVk = 0x52;
	inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

	inputs[3].ki.wVk = VK_LWIN;
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(NB_INPUTS, inputs, sizeof(INPUT));
}

void eutilities::humanType(const wchar_t* toWrite, int keyPressInterval)
{
	size_t sizeToWrite{ wcslen(toWrite) };
	INPUT ip{};
	ip.type = INPUT_KEYBOARD;

	for (size_t i{}; i <= sizeToWrite; ++i)
	{
		ip.ki.dwFlags = KEYEVENTF_UNICODE;
		ip.ki.wScan = toWrite[i];
		SendInput(1, &ip, sizeof(INPUT));

		Sleep(10);

		ip.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
		Sleep(keyPressInterval);
	}
}

void eutilities::copyToClipBoard(const std::wstring_view data)
{
	if (OpenClipboard(NULL))
	{
		EmptyClipboard();

		const size_t dataSize = (data.size() + 1) * sizeof(wchar_t); // Include null terminator
		HGLOBAL globalAlloc = GlobalAlloc(GMEM_MOVEABLE, dataSize);

		if (globalAlloc)
		{
			wchar_t* dataDestination = static_cast<wchar_t*>(GlobalLock(globalAlloc));
			if (dataDestination)
			{
				std::copy(data.begin(), data.end(), dataDestination);
				dataDestination[data.size()] = L'\0'; // Null terminator
				GlobalUnlock(globalAlloc);
				SetClipboardData(CF_UNICODETEXT, globalAlloc);
			}

			GlobalFree(globalAlloc);
		}

		CloseClipboard();
	}
}

/***********************/
/*     MOUSE UTILS     */
/***********************/

// LEFT CLICK

void eutilities::leftClickDown()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void eutilities::leftClickUp()
{
	INPUT mouseUp{};
	mouseUp.type = INPUT_MOUSE;
	mouseUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &mouseUp, sizeof(INPUT));
}

void eutilities::leftClick(const int& holdTime)
{
	eutilities::leftClickDown();
	Sleep(holdTime);
	eutilities::leftClickUp();
}

// RIGHT CLICK

void eutilities::rightClickDown()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void eutilities::rightClickUp()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void eutilities::rightClick(const int& holdTime)
{
	eutilities::rightClickDown();
	Sleep(holdTime);
	eutilities::rightClickUp();
}

constexpr std::optional<std::string> eutilities::nameOf(VirtualKey keyCode)
{
	switch (keyCode)
	{
	case MOUSE_LEFT:
		return "Left click";
	case MOUSE_RIGHT:
		return "Right click";
	case MOUSE_MIDDLE:
		return "Middle mouse";
	case MOUSE_BUTTON1:
		return "Mouse 1";
	case MOUSE_BUTTON2:
		return "Mouse 2";
	case ESCAPE:
		return "Escape";
	case F1:
		return "F1";
	case F2:
		return "F2";
	case F3:
		return "F3";
	case F4:
		return "F4";
	case F5:
		return "F5";
	case F6:
		return "F6";
	case F7:
		return "F7";
	case F8:
		return "F8";
	case F9:
		return "F9";
	case F10:
		return "F10";
	case F11:
		return "F11";
	case F12:
		return "F12";
	case PRINT:
		return "Print";
	case SCROLL_LOCK:
		return "Scroll lock";
	case PAUSE:
		return "Pause";
	case KEY_0:
		return "0";
	case KEY_1:
		return "1";
	case KEY_2:
		return "2";
	case KEY_3:
		return "3";
	case KEY_4:
		return "4";
	case KEY_5:
		return "5";
	case KEY_6:
		return "6";
	case KEY_7:
		return "7";
	case KEY_8:
		return "8";
	case KEY_9:
		return "9";
	case TAB:
		return "Tab";
	case CAPSLOCK:
		return "Capslock";
	case SHIFT:
		return "Shift";
	case LEFT_SHIFT:
		return "Left shift";
	case CTRL:
		return "CTRL";
	case LEFT_CONTROL:
		return "Left control";
	case LEFT_WINDOWS:
		return "Left Windows";
	case ALT:
		return "Alt";
	case LEFT_ALT:
		return "Left alt";
	case SPACEBAR:
		return "Spacebar";
	case RIGHT_ALT:
		return "Right alt";
	case RIGHT_WINDOWS:
		return "Right Windows";
	case APPS:
		return "Apps";
	case RIGHT_CONTROL:
		return "Right control";
	case RIGHT_SHIFT:
		return "Right shift";
	case ENTER:
		return "Enter";
	case BACKSPACE:
		return "Backspace";
	case A:
		return "A";
	case B:
		return "B";
	case C:
		return "C";
	case D:
		return "D";
	case E:
		return "E";
	case F:
		return "F";
	case G:
		return "G";
	case H:
		return "H";
	case I:
		return "I";
	case J:
		return "J";
	case K:
		return "K";
	case L:
		return "L";
	case M:
		return "M";
	case N:
		return "N";
	case O:
		return "O";
	case P:
		return "P";
	case Q:
		return "Q";
	case R:
		return "R";
	case S:
		return "S";
	case T:
		return "T";
	case U:
		return "U";
	case V:
		return "V";
	case W:
		return "W";
	case X:
		return "X";
	case Y:
		return "Y";
	case Z:
		return "Z";
	case OEM1:
		return "OEM1";
	case OEM2:
		return "OEM2";
	case OEM3:
		return "OEM3";
	case OEM4:
		return "OEM4";
	case OEM5:
		return "OEM5";
	case OEM6:
		return "OEM6";
	case OEM7:
		return "OEM7";
	case OEM8:
		return "OEM8";
	case OEM_PLUS:
		return "OEM plus";
	case OEM_MINUS:
		return "OEM minus";
	case OEM_PERIOD:
		return "OEM period";
	case OEM_COMMA:
		return "OEM comma";
	case OEM102:
		return "OEM102";
	default:
		return std::nullopt;
	}
}