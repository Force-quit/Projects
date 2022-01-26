#include "../Utilities/utils.h"
#include <Windows.h>
#include <iostream>


int main()
{
	emile::consoleBundle();
	std::cout << "Left click holder" << std::endl;

	std::cout << "Q : quit program" << std::endl;
	std::cout << "X : enable/disable" << std::endl;


	bool leftMouseButtonDown = false;
	bool keyDown = false;

	GetAsyncKeyState('X');
	GetAsyncKeyState('Q');

	while (!GetAsyncKeyState('Q'))
	{
		if (GetAsyncKeyState('X'))
		{
			if (!keyDown)
			{
				leftMouseButtonDown = !leftMouseButtonDown;
				if (leftMouseButtonDown)
					emile::leftClickDown();
				else
					emile::leftClickUp();
				
				std::cout << "Left mouse button : " << (leftMouseButtonDown ? "pressed" : "released") << std::endl;
				keyDown = true;
			}
		}
		else
			keyDown = false;

		Sleep(5);
	}
	return 0;
}