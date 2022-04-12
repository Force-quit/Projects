#include "motherfucker.h"
#include "../Utilities/utils.h"
#include <Windows.h>
#include <TlHelp32.h>

bool multipleInstances(const wchar_t processName[])
{
	HANDLE hProcessSnap{};
	PROCESSENTRY32 pe32{};
	bool processExists{};
	bool multipleInstances{};

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap != INVALID_HANDLE_VALUE)
	{
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hProcessSnap, &pe32))
		{
			do
			{
				if (wcscmp(pe32.szExeFile, processName) == 0)
				{
					if (processExists)
					{
						multipleInstances = true;
						break;
					}
					processExists = true;
				}

			} while (Process32Next(hProcessSnap, &pe32));
		}
	}
	CloseHandle(hProcessSnap);
	return multipleInstances;
}

bool checkMultipleInstances()
{
	TCHAR szPath[MAX_PATH];
	auto nameLength = GetModuleFileName(NULL, szPath, MAX_PATH);

	std::string processName{};
	for (int i = 0; i < nameLength; i++)
	{
		if (szPath[i] == 92)
			processName = "";
		else
			processName += szPath[i];
	}

	std::wstring wideProcessName{};
	for (int i = 0; i < processName.length(); ++i)
		wideProcessName += wchar_t(processName[i]);

	return multipleInstances(wideProcessName.c_str());
}

void createPrankMessage()
{
	Sleep(50);
	emile::copyToClipBoard("notepad.exe");
	Sleep(50);
	emile::winR();
	Sleep(50);
	emile::ctrlV();
	Sleep(50);
	emile::fullKeyPress(VK_RETURN);
	Sleep(50);
	emile::copyToClipBoard("LOLOLOLOLOLOLOL XD XD ahahahh HIHII");
	Sleep(50);
	emile::ctrlV();
}

int rangedRandom(int min, int max)
{
	return min + rand() % ((max + 1) - min);
}

void prank_CAPSLOCK()
{
	if (GetKeyState(VK_CAPITAL) == 0)
		emile::fullKeyPress(VK_CAPITAL);
}

void prank_WINDOWS()
{
	emile::fullKeyPress(VK_LWIN);
}

void prank_SPACE()
{
	emile::fullKeyPress(VK_SPACE);
}

void prank_RETURN()
{
	emile::fullKeyPress(VK_RETURN);
}

void prank_BACKSPACE()
{
	emile::fullKeyPress(VK_BACK);
}

void prank_CTRLV()
{
	emile::ctrlV();
}

void prank_ESCAPE()
{
	emile::fullKeyPress(VK_ESCAPE);
}
