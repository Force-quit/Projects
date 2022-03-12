#include "../../Utilities/utils.h"
#include <Windows.h>
#include <fstream>

int main()
{
	FreeConsole();
	std::clock_t start;
	start = std::clock();
	while (!GetAsyncKeyState(VK_RCONTROL))
	{
		if (std::clock() - start >= 30000)
		{
			if (GetKeyState(VK_CAPITAL) == 0)
				emile::fullKeyPress(VK_CAPITAL);
			start = std::clock();
		}

		Sleep(5);
	}

	std::ofstream myfile;
	myfile.open("jtaieu.txt");
	myfile << "AHAHAHA! Tu t'es fait avoir par l'équipe de jt'ai eu!";
	myfile.close();

	system("jtaieu.txt");
	remove("jtaieu.txt");
	return 0;
}
