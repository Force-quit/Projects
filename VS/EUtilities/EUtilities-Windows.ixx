export module eUtilities:windows;

export namespace eUtilities
{
	namespace windows
	{
		namespace Console
		{
			void consoleBundle();
			void preventConsoleResize();
			void hideCursor();
			void disableQuickEdit();
			void hideScrollingBar();
		};

		// Wait until user presses and release the specified virutal key
		void waitForFullKeyPress(short vKey);
		void waitForKeyPress(short vKey);
		void waitForKeyRelease(short vKey);
	}
}