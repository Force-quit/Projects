#pragma once
#include <string>
#include <Windows.h>
#include <vector>

namespace emile
{
	// Resets std::cin buffer
	void flushTampon();

	
	void consoleBundle();
	void preventConsoleResize();
	void hideCursor();
	void disableQuickEdit();
	void hideScrollingBar();

	/** 
	* Generate a password string 
	* @param alphabet : string containing possible password characters
	* @param passwordLength : Length of the password
	* @return The password string
	*/
	std::string passwordGenerator(const std::string& alphabet, const unsigned short& passwordLength);

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
}