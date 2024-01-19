export module EUtilities:Windows;

export namespace EUtilities
{
	// Wait until user presses and release the specified virutal key
	void waitForFullKeyPress(short vKey);
	void waitForKeyPress(short vKey);
	void waitForKeyRelease(short vKey);
}