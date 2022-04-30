#include <Windows.h>
#include "../Utilities/utils.h"
#include "motherfucker.h"
#include <ctime> 
#include <random>


int main()
{	
	using prank_function_type = void (*)();
	
	FreeConsole();
	srand(time(0));

	if (checkMultipleInstances())
		return 0;

	std::vector<prank_function_type> prankFunctions;
	prankFunctions.push_back(prank_CAPSLOCK);
	prankFunctions.push_back(prank_WINDOWS);
	prankFunctions.push_back(prank_BACKSPACE);
	prankFunctions.push_back(prank_CTRLV);
	prankFunctions.push_back(prank_RETURN);
	prankFunctions.push_back(prank_SPACE);
	prankFunctions.push_back(prank_ESCAPE);



	std::clock_t start;
	start = std::clock();
	GetAsyncKeyState(VK_RCONTROL);
	while (!GetAsyncKeyState(VK_RCONTROL))
	{
		if (std::clock() - start >= rangedRandom(30000, 120000))
		{
			prankFunctions[rangedRandom(0, prankFunctions.size() - 1)]();
			start = std::clock();
		}
		Sleep(5);
	}

	while (GetAsyncKeyState(VK_RCONTROL))
		Sleep(5);

	createPrankMessage();

	return 0;
}