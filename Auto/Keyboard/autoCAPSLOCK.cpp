#include "../../Utilities/utils.h"
#include <Windows.h>
#include <iostream>


int main()
{
	FreeConsole();
	while (true)
	{
		Sleep(30000);
		if (GetKeyState(VK_CAPITAL) == 0)
		{
			emile::fullKeyPress(VK_CAPITAL);
		}

		if (GetAsyncKeyState(VK_RCONTROL))
			break;
	}

	emile::copyToClipBoard("notepad.exe");
	Sleep(10);
	emile::pressKey(VK_LWIN);
	Sleep(10);

	emile::pressKey(0x52);
	Sleep(10);

	emile::releaseKey(VK_LWIN);
	Sleep(10);

	emile::releaseKey(0x52);

	emile::pressKey(VK_CONTROL);
	Sleep(10);

	emile::pressKey(0x56);
	Sleep(10);

	emile::releaseKey(VK_CONTROL);
	Sleep(10);

	emile::releaseKey(0x56);
	Sleep(10);

	emile::fullKeyPress(VK_RETURN);
	Sleep(10);

	emile::copyToClipBoard("AHAHAHA Tu t'es fait avoir par l'equipe de chteu");

	Sleep(10);
	emile::pressKey(VK_CONTROL);
	Sleep(10);

	emile::pressKey(0x56);
	Sleep(10);

	emile::releaseKey(VK_CONTROL);
	Sleep(10);

	emile::releaseKey(0x56);
	Sleep(10);

	return 0;
}