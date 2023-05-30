#include <Windows.h>
#include <algorithm>
#include <utility>
#include <iostream>

std::pair<int, int> getWindowSize()
{
	RECT windowSize;
	GetWindowRect(GetDesktopWindow(), &windowSize);
	return { windowSize.right - 2, windowSize.bottom - 2 };
}

int main()
{
	const std::pair<int, int> WINDOW_SIZE(getWindowSize());
	POINT previousMousePos, mousePos;
	
	GetCursorPos(&mousePos);
	previousMousePos = mousePos;

	std::cout << "Right shift to stop";

	while (!GetAsyncKeyState(VK_RSHIFT))
	{
		GetCursorPos(&mousePos);

		if (previousMousePos.x != mousePos.x || previousMousePos.y != mousePos.y)
		{
			previousMousePos.x -= mousePos.x;
			previousMousePos.y -= mousePos.y;

			mousePos.x += 2 * previousMousePos.x;
			mousePos.y += 2 * previousMousePos.y;

			mousePos.x = std::clamp(static_cast<int>(mousePos.x), 2, WINDOW_SIZE.first);
			mousePos.y = std::clamp(static_cast<int>(mousePos.y), 2, WINDOW_SIZE.second);

			SetCursorPos(mousePos.x, mousePos.y);
			previousMousePos = mousePos;
		}
	}
	return 0;

}