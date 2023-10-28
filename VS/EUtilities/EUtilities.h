#pragma once

#include <string_view>

#ifdef EUTILITIES_EXPORTS
#define EUTILITIES_API __declspec(dllexport)
#else
#define EUTILITIES_API __declspec(dllimport)
#endif

namespace EUtilities 
{
	EUTILITIES_API void flushTampon();

	class EUTILITIES_API Console
	{
		static void consoleBundle();
		static void preventConsoleResize();
		static void hideCursor();
		static void disableQuickEdit();
		static void hideScrollingBar();
	};

	//////////////////////////////
	// KEYBOARD AND MOUSE INPUT //
	//////////////////////////////

	EUTILITIES_API void pressKey(const char key);
	EUTILITIES_API void pressKey(const int keyCode);
	EUTILITIES_API void pressKey(INPUT& input);
	EUTILITIES_API void releaseKey(const char key);
	EUTILITIES_API void releaseKey(const int keyCode);
	EUTILITIES_API void releaseKey(INPUT& input);
	EUTILITIES_API void fullKeyPress(const char key, unsigned int pressDuration = 20);
	EUTILITIES_API void fullKeyPress(const int keyCode, unsigned int pressDuration = 20);
	EUTILITIES_API void fullKeyPress(INPUT& input, unsigned int pressDuration = 20);

	EUTILITIES_API void ctrlV();

	EUTILITIES_API void winR();

	// Simulate the typing of a string
	EUTILITIES_API void humanType(const wchar_t* toWrite, int keyPressInterval = 50);

	// Copy a string into windows's clipboard
	EUTILITIES_API void copyToClipBoard(const std::string_view dataToCopy);

	// Simulate a left mouse button down
	EUTILITIES_API void leftClickDown();

	// Simulate a left mouse button up
	EUTILITIES_API void leftClickUp();

	// Simulate a left click
	EUTILITIES_API void leftClick(const int& holdTime = 30);

	// Simulate a right mouse button down
	EUTILITIES_API void rightClickDown();

	// Simulate a right mouse button up
	EUTILITIES_API void rightClickUp();

	// Simulate a right click
	EUTILITIES_API void rightClick(const int& holdTime = 30);

	// Wait until user presses and release the specified virutal key
	EUTILITIES_API void waitForKeyPress(short vKey);

	// Create folder if it doesn't exist. Returns false if folder did not exist
	EUTILITIES_API bool ensureFolderExists(const std::string_view dirName);

	EUTILITIES_API bool folderExists(const std::string_view dirName);
}