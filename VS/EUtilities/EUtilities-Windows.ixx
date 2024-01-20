export module eutilities:Windows;

export namespace eutilities
{
	namespace windows
	{
		// Wait until user presses and release the specified virutal key
		void waitForFullKeyPress(short vKey);
		void waitForKeyPress(short vKey);
		void waitForKeyRelease(short vKey);
	}
}