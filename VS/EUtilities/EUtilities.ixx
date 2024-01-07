module;

#include <Windows.h>
#include <string_view>

export module EUtilities;

export namespace EUtilities
{
	void flushTampon();

	namespace Console
	{
		void consoleBundle();
		void preventConsoleResize();
		void hideCursor();
		void disableQuickEdit();
		void hideScrollingBar();
	};

	//////////////////////////////
	// KEYBOARD AND MOUSE INPUT //
	//////////////////////////////

	void pressKey(const char key);
	void pressKey(const int keyCode);
	void pressKey(INPUT& input);
	void releaseKey(const char key);
	void releaseKey(const int keyCode);
	void releaseKey(INPUT& input);
	void fullKeyPress(const char key, unsigned int pressDuration = 20);
	void fullKeyPress(const int keyCode, unsigned int pressDuration = 20);
	void fullKeyPress(INPUT& input, unsigned int pressDuration = 20);

	void ctrlV();

	void winR();

	// Simulate the typing of a string
	void humanType(const wchar_t* toWrite, int keyPressInterval = 50);

	// Copy a string into windows's clipboard
	void copyToClipBoard(const std::wstring_view dataToCopy);

	// Simulate a left mouse button down
	void leftClickDown();

	// Simulate a left mouse button up
	void leftClickUp();

	// Simulate a left click
	void leftClick(const int& holdTime = 30);

	// Simulate a right mouse button down
	void rightClickDown();

	// Simulate a right mouse button up
	void rightClickUp();

	// Simulate a right click
	void rightClick(const int& holdTime = 30);

	// Wait until user presses and release the specified virutal key
	void waitForKeyPress(short vKey);

	// Create folder if it doesn't exist. Returns false if folder did not exist
	bool ensureFolderExists(const std::string_view dirName);

	bool folderExists(const std::string_view dirName);
}