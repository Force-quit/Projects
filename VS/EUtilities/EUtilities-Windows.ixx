module;

#include <Windows.h>
#include <string_view>
#include <string>
#include <optional>
#include <span>
#include <array>

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
	enum Key : std::uint16_t
	{
		LEFT_CLICK = VK_LBUTTON,
		RIGHT_CLICK = VK_RBUTTON,
		MIDDLE_MOUSE = VK_MBUTTON,
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

		UP = VK_UP,
		DOWN = VK_DOWN,
		LEFT = VK_LEFT,
		RIGHT = VK_RIGHT,
		DEL = VK_DELETE,
		INSERT = VK_INSERT,
		HOME = VK_HOME,
		END = VK_END,
		PAGE_UP = VK_PRIOR,
		PAGE_DOWN = VK_NEXT,

		NUMPAD_0 = VK_NUMPAD0,
		NUMPAD_1 = VK_NUMPAD1,
		NUMPAD_2 = VK_NUMPAD2,
		NUMPAD_3 = VK_NUMPAD3,
		NUMPAD_4 = VK_NUMPAD4,
		NUMPAD_5 = VK_NUMPAD5,
		NUMPAD_6 = VK_NUMPAD6,
		NUMPAD_7 = VK_NUMPAD7,
		NUMPAD_8 = VK_NUMPAD8,
		NUMPAD_9 = VK_NUMPAD9,
		NUMPAD_ADD = VK_ADD,
		NUMPAD_SUBTRACT = VK_SUBTRACT,
		NUMPAD_MULTIPLY = VK_MULTIPLY,
		NUMPAD_DIVIDE = VK_DIVIDE,
		NUMPAD_CLEAR = VK_CLEAR,
		NUMPAD_LOCK = VK_NUMLOCK,
		NUMPAD_DECIMAL = VK_DECIMAL,
	};

	// Array to iterate over all the values of the Key enum.
	constexpr auto keys	= std::array{
		LEFT_CLICK,
		RIGHT_CLICK,
		MIDDLE_MOUSE,
		MOUSE_BUTTON1,
		MOUSE_BUTTON2,
		ESCAPE,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		PRINT,
		SCROLL_LOCK,
		PAUSE,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		SHIFT,
		RIGHT_SHIFT,
		CONTROL,
		RIGHT_CONTROL,
		ALT,
		RIGHT_ALT,
		WINDOWS,
		RIGHT_WINDOWS,
		TAB,
		CAPSLOCK,
		APPS,
		ENTER,
		BACKSPACE,
		SPACEBAR,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		OEM1,
		OEM2,
		OEM3,
		OEM4,
		OEM5,
		OEM6,
		OEM7,
		OEM8,
		OEM_PLUS,
		OEM_MINUS,
		OEM_PERIOD,
		OEM_COMMA,
		OEM102,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		DEL,
		INSERT,
		HOME,
		END,
		PAGE_UP,
		PAGE_DOWN,
		NUMPAD_0,
		NUMPAD_1,
		NUMPAD_2,
		NUMPAD_3,
		NUMPAD_4,
		NUMPAD_5,
		NUMPAD_6,
		NUMPAD_7,
		NUMPAD_8,
		NUMPAD_9,
		NUMPAD_ADD,
		NUMPAD_SUBTRACT,
		NUMPAD_MULTIPLY,
		NUMPAD_DIVIDE,
		NUMPAD_CLEAR,
		NUMPAD_LOCK,
		NUMPAD_DECIMAL,
	};

	// Array to iterate over the keyboard keys of the Key enum.
	constexpr auto keyboardKeys = std::array{
		ESCAPE,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		PRINT,
		SCROLL_LOCK,
		PAUSE,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		SHIFT,
		RIGHT_SHIFT,
		CONTROL,
		RIGHT_CONTROL,
		ALT,
		RIGHT_ALT,
		WINDOWS,
		RIGHT_WINDOWS,
		TAB,
		CAPSLOCK,
		APPS,
		ENTER,
		BACKSPACE,
		SPACEBAR,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		OEM1,
		OEM2,
		OEM3,
		OEM4,
		OEM5,
		OEM6,
		OEM7,
		OEM8,
		OEM_PLUS,
		OEM_MINUS,
		OEM_PERIOD,
		OEM_COMMA,
		OEM102,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		DEL,
		INSERT,
		HOME,
		END,
		PAGE_UP,
		PAGE_DOWN,
		NUMPAD_0,
		NUMPAD_1,
		NUMPAD_2,
		NUMPAD_3,
		NUMPAD_4,
		NUMPAD_5,
		NUMPAD_6,
		NUMPAD_7,
		NUMPAD_8,
		NUMPAD_9,
		NUMPAD_ADD,
		NUMPAD_SUBTRACT,
		NUMPAD_MULTIPLY,
		NUMPAD_DIVIDE,
		NUMPAD_CLEAR,
		NUMPAD_LOCK,
		NUMPAD_DECIMAL,
	};

	// Array to iterate over the mouse keys of the Key enum.
	constexpr auto mouseKeys = std::array{
		LEFT_CLICK,
		RIGHT_CLICK,
		MIDDLE_MOUSE,
		MOUSE_BUTTON1,
		MOUSE_BUTTON2
	};

	/**
	* Get the display name of the specified key.
	*
	* @param key An enum value of eutilities::Key.
	* @return The name of the key if it's known. If not, an empty std::optional.
	*/
	[[nodiscard]] constexpr std::optional<std::string> nameOf(Key key);

	/**
	* Get the display name of the specified key.
	*
	* @param key An enum value of eutilities::Key.
	* @return The name of the key if it's known. If not, an empty std::optional.
	* @overload
	*/
	[[nodiscard]] constexpr std::optional<std::string> nameOf(int key);


	/**
	* Check if the specified key is being pressed.
	*
	* @param key The key you want to check.
	* @return True if the key is being pressed.
	*/
	[[nodiscard]] bool isPressed(Key key);

	/**
	* Check if the specified key is being pressed.
	*
	* @param key The key you want to check.
	* @return True if the key is being pressed.
	* @overload
	*/
	[[nodiscard]] bool isPressed(int key);

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
	void pressKey(Key key);

	/**
	* Simulates a key release with the specified key.
	* @param key The key to release.
	*/
	void releaseKey(Key key);

	/**
	* Simulates a full key press (press and release)
	* with the specified key.
	* @param key The key to press and release.
	*/
	void fullKeyPress(Key key);

	// Simulates the CTRL + V keyboard shortcut
	void ctrlV();

	/**
	* Simulates the typing of a string.
	*
	* @param string A sequence of unicode characters.
	* @param keyPressInterval The interval between key presses.
	*/
	void humanType(std::wstring_view string, int keyPressInterval = 120);

	/**
	* Copy a sequence of characters into the Windows clipboard.
	*
	* @param dataToCopy A sequence of unicode characters.
	*/
	void copyToClipBoard(std::span<const char> dataToCopy);
}

namespace eutilities
{
	void setMouseReleaseInput(Key mouseKey, INPUT& mouseInput);
	void setMousePressInput(Key mouseKey, INPUT& mouseInput);
	constexpr bool isMouseKey(Key key);
}