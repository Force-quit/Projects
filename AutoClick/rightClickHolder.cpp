#include "../Utilities/utils.h"
#include <Windows.h>
#include <iostream>


int main()
{
	emile::consoleBundle();
	std::cout << "Right click holder" << std::endl;

	std::cout << "Q : quit program" << std::endl;
	std::cout << "X : enable/disable" << std::endl;


	bool rightMouseButtonDown = false;
	bool keyDown = false;

	GetAsyncKeyState('X');
	GetAsyncKeyState('Q');

	while (!GetAsyncKeyState('Q'))
	{
		if (GetAsyncKeyState('X'))
		{
			if (!keyDown)
			{
				rightMouseButtonDown = !rightMouseButtonDown;
				if (rightMouseButtonDown)
					emile::rightClickDown();
				else
					emile::rightClickUp();

				std::cout << "Right mouse button : " << (rightMouseButtonDown ? "pressed" : "released") << std::endl;
				keyDown = true;
			}
		}
		else
			keyDown = false;

		Sleep(5);
	}
	return 0;
}