#pragma once
#include <string>
#include <Windows.h>
#include <vector>

namespace emile
{
	// Resets std::cin buffer
	void flushTampon();

	struct Console
	{
		static void consoleBundle();
		static void preventConsoleResize();
		static void hideCursor();
		static void disableQuickEdit();
		static void hideScrollingBar();
	};

	struct PasswordGenerator
	{
		
		static const std::string DEFAULT_ALPHABET;
		/**
		* Generate a password string
		* @param alphabet : string containing possible password characters
		* @param passwordLength : Length of the password
		* @return The password string
		*/
		static std::string generate(const std::string& alphabet = DEFAULT_ALPHABET, const unsigned short& passwordLength = 100);
	};


	//////////////////////////////
	// KEYBOARD AND MOUSE INPUT //
	//////////////////////////////

	void pressKey(const char& key);
	void pressKey(const int& keyCode);
	void pressKey(INPUT& input);
	void releaseKey(const char& key);
	void releaseKey(const int& keyCode);
	void releaseKey(INPUT& input);
	void fullKeyPress(const char& key);
	void fullKeyPress(const int& keyCode);
	void fullKeyPress(INPUT& input);

	void ctrlV();

	void winR();

	// Simulate the typing of a string
	void humanType(const std::string& toWrite);

	// Copy a string into windows's clipboard
	void copyToClipBoard(const std::string& dataToCopy);

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

	// Create folder is not existant. Returns false if folder did not exist
	bool verifyFolderExists(const std::string& dirName);

	bool folderExists(const std::string& dirName);
}