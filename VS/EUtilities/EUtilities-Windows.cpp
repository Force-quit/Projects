module;

#include <Windows.h>
#include <string_view>
#include <optional>
#include <thread>

module eutilities:windows;

import eutilities;

constexpr bool eutilities::isMouseKey(Key key)
{
	switch (key)
	{
	case eutilities::Key::LEFT_CLICK:
	case eutilities::Key::RIGHT_CLICK:
	case eutilities::Key::MIDDLE_MOUSE:
	case eutilities::Key::MOUSE_BUTTON1:
	case eutilities::Key::MOUSE_BUTTON2:
		return true;
	default:
		return false;
	}
}

void eutilities::setMousePressInput(Key mouseKey, INPUT& mouseInput)
{
	mouseInput.type = INPUT_MOUSE;

	switch (mouseKey)
	{
	case eutilities::Key::LEFT_CLICK:
		mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		break;
	case eutilities::Key::RIGHT_CLICK:
		mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		break;
	case eutilities::Key::MIDDLE_MOUSE:
		mouseInput.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
		break;
	case eutilities::Key::MOUSE_BUTTON1:
		mouseInput.mi.dwFlags = MOUSEEVENTF_XDOWN;
		mouseInput.mi.mouseData = XBUTTON1;
		break;
	case eutilities::Key::MOUSE_BUTTON2:
		mouseInput.mi.dwFlags = MOUSEEVENTF_XDOWN;
		mouseInput.mi.mouseData = XBUTTON2;
		break;
	}
}

void eutilities::setMouseReleaseInput(Key mouseKey, INPUT& mouseInput)
{
	mouseInput.type = INPUT_MOUSE;

	switch (mouseKey)
	{
	case eutilities::Key::LEFT_CLICK:
		mouseInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		break;
	case eutilities::Key::RIGHT_CLICK:
		mouseInput.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		break;
	case eutilities::Key::MIDDLE_MOUSE:
		mouseInput.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
		break;
	case eutilities::Key::MOUSE_BUTTON1:
		mouseInput.mi.dwFlags = MOUSEEVENTF_XUP;
		mouseInput.mi.mouseData = XBUTTON1;
		break;
	case eutilities::Key::MOUSE_BUTTON2:
		mouseInput.mi.dwFlags = MOUSEEVENTF_XUP;
		mouseInput.mi.mouseData = XBUTTON2;
		break;
	}
}

void eutilities::waitForFullKeyPress(Key key)
{
	waitForKeyPress(key);
	waitForKeyRelease(key);
}

void eutilities::waitForKeyPress(Key key)
{
	while (!isPressed(key))
	{
		sleepFor(1);
	}
}

void eutilities::waitForKeyRelease(Key key)
{
	while (isPressed(key))
	{
		sleepFor(1);
	}
}

void eutilities::Console::hideCursor()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor{};
	lpCursor.bVisible = false;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void eutilities::pressKey(Key key)
{
	INPUT input{};
	if (isMouseKey(key))
	{
		setMousePressInput(key, input);
	}
	else
	{
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = key;
	}

	SendInput(1, &input, sizeof(INPUT));
}

void eutilities::releaseKey(Key key)
{
	INPUT input{};
	if (isMouseKey(key))
	{
		setMouseReleaseInput(key, input);
	}
	else
	{
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = key;
		input.ki.dwFlags = KEYEVENTF_KEYUP;
	}
	SendInput(1, &input, sizeof(INPUT));
}

void eutilities::fullKeyPress(Key key)
{
	pressKey(key);
	sleepFor(30);
	releaseKey(key);
}

void eutilities::ctrlV()
{
	pressKey(Key::CONTROL);
	sleepFor(10);
	pressKey(Key::V);
	sleepFor(10);

	releaseKey(Key::CONTROL);
	releaseKey(Key::V);
}

void eutilities::humanType(std::wstring_view string, int keyPressInterval)
{
	INPUT input{};
	input.type = INPUT_KEYBOARD;

	for (auto i : string)
	{
		input.ki.dwFlags = KEYEVENTF_UNICODE;
		input.ki.wScan = i;
		SendInput(1, &input, sizeof(INPUT));

		sleepFor(20);

		input.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(INPUT));

		sleepFor(keyPressInterval);
	}
}

void eutilities::copyToClipBoard(std::span<const char> data)
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


constexpr std::optional<std::string> eutilities::nameOf(Key keyCode)
{
	switch (keyCode)
	{
	case LEFT_CLICK:
		return "Left click";
	case RIGHT_CLICK:
		return "Right click";
	case MIDDLE_MOUSE:
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
	case CONTROL:
		return "CTRL";
	case WINDOWS:
		return "Windows";
	case ALT:
		return "Alt";
	case SPACEBAR:
		return "Spacebar";
	case RIGHT_ALT:
		return "Right alt";
	case RIGHT_WINDOWS:
		return "Right Windows";
	case APPS:
		return "Apps";
	case RIGHT_CONTROL:
		return "Right CTRL";
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
	case UP:
		return "Up";
	case DOWN:
		return "Down";
	case LEFT:
		return "Left";
	case RIGHT:
		return "Right";
	case DEL:
		return "Delete";
	case INSERT:
		return "Insert";
	case HOME:
		return "Home";
	case END:
		return "End";
	case PAGE_UP:
		return "Page up";
	case PAGE_DOWN:
		return "Page down";
	case NUMPAD_0:
		return "Numpad 0";
	case NUMPAD_1:
		return "Numpad 1";
	case NUMPAD_2:
		return "Numpad 2";
	case NUMPAD_3:
		return "Numpad 3";
	case NUMPAD_4:
		return "Numpad 4";
	case NUMPAD_5:
		return "Numpad 5";
	case NUMPAD_6:
		return "Numpad 6";
	case NUMPAD_7:
		return "Numpad 7";
	case NUMPAD_8:
		return "Numpad 8";
	case NUMPAD_9:
		return "Numpad 9";
	case NUMPAD_ADD:
		return "Numpad add";
	case NUMPAD_SUBTRACT:
		return "Numpad subtract";
	case NUMPAD_MULTIPLY:
		return "Numpad multiply";
	case NUMPAD_DIVIDE:
		return "Numpad divide";
	case NUMPAD_CLEAR:
		return "Numpad clear";
	case NUMPAD_LOCK:
		return "Numpad lock";
	case NUMPAD_DECIMAL:
		return "Numpad decimal";
	default:
		return std::nullopt;
	}
}

constexpr std::optional<std::string> eutilities::nameOf(int key)
{
	return nameOf(static_cast<Key>(key));
}

bool eutilities::isPressed(Key key)
{
	return GetKeyState(key) & 0x8000;
}

bool eutilities::isPressed(int key)
{
	return isPressed(static_cast<Key>(key));
}