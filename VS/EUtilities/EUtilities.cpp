module;

#include <iostream>
#include <Windows.h>
#include <filesystem>

module eUtilities;

void eUtilities::flushTampon()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}

/**************************/
/*     KEYBOARD UTILS     */
/**************************/

void eUtilities::pressKey(char key)
{
	short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	eUtilities::pressKey(keyCode);
}

void eUtilities::pressKey(int keyCode)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;

	eUtilities::pressKey(i);
}

void eUtilities::pressKey(INPUT& input)
{
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));
}

void eUtilities::releaseKey(char key)
{
	short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	eUtilities::releaseKey(keyCode);
}

void eUtilities::releaseKey(int keyCode)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;
	eUtilities::releaseKey(i);
}

void eUtilities::releaseKey(INPUT& input)
{
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
}

void eUtilities::fullKeyPress(char key, unsigned int pressDuration)
{
	short keyCode = VkKeyScanExA(key, GetKeyboardLayout(0));
	eUtilities::fullKeyPress(keyCode, pressDuration);
}

void eUtilities::fullKeyPress(int keyCode, unsigned int pressDuration)
{
	INPUT i{};
	i.type = INPUT_KEYBOARD;
	i.ki.wVk = keyCode;
	eUtilities::fullKeyPress(i, pressDuration);
}

void eUtilities::fullKeyPress(INPUT& input, unsigned int pressDuration)
{
	eUtilities::pressKey(input);
	Sleep(pressDuration);
	eUtilities::releaseKey(input);
}

void eUtilities::ctrlV()
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

void eUtilities::winR()
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

void eUtilities::humanType(const wchar_t* toWrite, int keyPressInterval)
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

void eUtilities::copyToClipBoard(const std::wstring_view data)
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

void eUtilities::leftClickDown()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void eUtilities::leftClickUp()
{
	INPUT mouseUp{};
	mouseUp.type = INPUT_MOUSE;
	mouseUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &mouseUp, sizeof(INPUT));
}

void eUtilities::leftClick(const int& holdTime)
{
	eUtilities::leftClickDown();
	Sleep(holdTime);
	eUtilities::leftClickUp();
}

// RIGHT CLICK

void eUtilities::rightClickDown()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void eUtilities::rightClickUp()
{
	INPUT mouseDown{};
	mouseDown.type = INPUT_MOUSE;
	mouseDown.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &mouseDown, sizeof(INPUT));
}

void eUtilities::rightClick(const int& holdTime)
{
	eUtilities::rightClickDown();
	Sleep(holdTime);
	eUtilities::rightClickUp();
}

bool eUtilities::ensureFolderExists(const std::string_view dirName)
{
	bool folderExists = eUtilities::folderExists(dirName);
	if (!folderExists)
		std::filesystem::create_directory(dirName);
	return folderExists;
}

bool eUtilities::folderExists(const std::string_view dirName)
{
	return std::filesystem::is_directory(dirName);
}