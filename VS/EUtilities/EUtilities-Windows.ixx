module;

#include <Windows.h>
#include <string_view>
#include <string>
#include <optional>

export module eutilities:windows;

export namespace eutilities
{
	// Usefull Windows console utilities
	namespace Console
	{
		// Make the console's cursor invisible.
		void hideCursor();
	};

	/**
	* Represents physical buttons you can press.
	*
	* @see [Windows virtual key codes](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)
	*/
	enum Key
	{
		MOUSE_LEFT = VK_LBUTTON,
		MOUSE_RIGHT = VK_RBUTTON,
		MOUSE_MIDDLE = VK_MBUTTON,
		MOUSE_BUTTON1 = VK_XBUTTON1,
		MOUSE_BUTTON2 = VK_XBUTTON2,

		ESCAPE = VK_ESCAPE,
		F1 = VK_F1,
		F2 = VK_F2,
		F3 = VK_F3,
		F4 = VK_F4,
		F5 = VK_F5,
		F6 = VK_F6,
		F7 = VK_F7,
		F8 = VK_F8,
		F9 = VK_F9,
		F10 = VK_F10,
		F11 = VK_F11,
		F12 = VK_F12,
		PRINT = VK_SNAPSHOT,
		SCROLL_LOCK = VK_SCROLL,
		PAUSE = VK_PAUSE,

		KEY_0 = 0x30,
		KEY_1 = 0x31,
		KEY_2 = 0x32,
		KEY_3 = 0x33,
		KEY_4 = 0x34,
		KEY_5 = 0x35,
		KEY_6 = 0x36,
		KEY_7 = 0x37,
		KEY_8 = 0x38,
		KEY_9 = 0x39,


		SHIFT = VK_LSHIFT,
		RIGHT_SHIFT = VK_RSHIFT,
		CONTROL = VK_LCONTROL,
		RIGHT_CONTROL = VK_RCONTROL,
		ALT = VK_LMENU,
		RIGHT_ALT = VK_RMENU,
		WINDOWS = VK_LWIN,
		RIGHT_WINDOWS = VK_RWIN,
		TAB = VK_TAB,
		CAPSLOCK = VK_CAPITAL,
		APPS = VK_APPS,
		ENTER = VK_RETURN,
		BACKSPACE = VK_BACK,
		SPACEBAR = VK_SPACE,

		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C,
		M = 0x4D,
		N = 0x4E,
		O = 0x4F,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5A,

		OEM1 = 0xBA,
		OEM2 = 0xBF,
		OEM3 = 0xC0,
		OEM4 = 0xDB,
		OEM5 = 0xDC,
		OEM6 = 0xDD,
		OEM7 = 0xDE,
		OEM8 = 0xDF,

		OEM_PLUS = VK_OEM_PLUS,
		OEM_MINUS = VK_OEM_MINUS,
		OEM_PERIOD = VK_OEM_PERIOD,
		OEM_COMMA = VK_OEM_COMMA,
		OEM102 = VK_OEM_102,
	};

	/**
	* Get the display name of the specified key.
	*
	* @param key An enum value of eutilities::Key.
	* @return The name of the key if it's known. If not, an empty std::optional.
	*/
	[[nodiscard]] constexpr std::optional<std::string> nameOf(Key key);

	/**
	* Check if the specified key is being pressed.
	*
	* @param key The key you want to check.
	* @return True if the key is being pressed.
	*/
	[[nodiscard]] bool keyIsPressed(Key key);

	/**
	* Returns execution only when the specified
	* key was pressed and then released.
	*
	* @param key The key you want to wait for.
	*/
	void waitForFullKeyPress(Key key);

	/**
	* Returns execution only when the specified
	* key was pressed.
	*
	* @param key The key you want to wait for.
	*/
	void waitForKeyPress(Key key);

	/**
	* Returns execution only when the specified
	* key was released.
	*
	* @param key The key you want to wait for.
	*/
	void waitForKeyRelease(Key key);

	/**
	* Simulates a key press with the specified key.
	* @param key The key to press.
	*/
	void pressKeyboardKey(Key key);

	/**
	* Simulates a key release with the specified key.
	* @param key The key to release.
	*/
	void releaseKeyboardKey(Key key);

	void fullKeyboardKeyPress(Key key);

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

	void sleepFor(int msDuration);
}