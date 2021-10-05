#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include "../Console(v1.9)/console(v1.9).h"
#include "../Utilities/usefullshit.h"

double inputValidation();
void getProcessId(DWORD& procId, LPCSTR lpWindowName);
ULONG64 GetModuleBaseAddress(const wchar_t moduleName[], DWORD pID);
ULONG64 getBaseAddress(std::vector<ULONG64>& addressOffsets, HANDLE hprocess, DWORD processId);
void fillAddressesVector(std::vector<ULONG64>& valuesAddresses, HANDLE hprocess, DWORD processId);
short menuSelection();

int main()
{
	DWORD processId{};
	getProcessId(processId, "Leaf Blower Revolution");

	std::cout << std::endl;
	std::vector<ULONG64> valuesAddresses;

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (hProcess != INVALID_HANDLE_VALUE)
	{
		fillAddressesVector(valuesAddresses, hProcess, processId);

		short typeOfResource = menuSelection();
		double valueToWrite = 0;
		bool stayInLoop = true;
		do
		{
			valueToWrite = inputValidation();
			switch ((int)valueToWrite)
			{
			case -1:
				stayInLoop = false;
				break;
			case -2:
				typeOfResource = menuSelection();
				break;
			default:
				if (typeOfResource == -1)
					for (short i = 0; i < valuesAddresses.size(); i++)
						WriteProcessMemory(hProcess, (void*)valuesAddresses.at(i), &valueToWrite, sizeof(double), NULL);
				else
					WriteProcessMemory(hProcess, (void*)valuesAddresses.at(typeOfResource), &valueToWrite, sizeof(double), NULL);
				break;
			}

		} while (stayInLoop);
	}
	else
		std::cout << "OpenProcess failed with code : " << GetLastError();

	CloseHandle(hProcess);
	std::cout << "\n\n Closing...";
	Sleep(1500);
	return 0;
}

short menuSelection()
{
	std::cout << "\n\n" << "-----MENU-----" << "\n\n";
	std::cout << "-- Leafs" << std::endl;
	std::cout << "1 : Normal leaf" << std::endl;
	std::cout << "2 : Gold leaf" << std::endl;
	std::cout << "3 : Platinum leaf" << std::endl;
	std::cout << "4 : Bismuth leaf" << std::endl;
	std::cout << "5 : Cosmic leaf" << std::endl;
	std::cout << "6 : Void leaf" << std::endl;
	std::cout << "7 : Exotic leaf" << std::endl;
	std::cout << "8 : Celestial leaf" << std::endl;
	std::cout << "9 : Mythical leaf" << std::endl;
	std::cout << "A : Lava leaf" << std::endl;
	std::cout << "B : Ice leaf" << std::endl;
	std::cout << "C : Obsidian leaf" << std::endl;
	std::cout << "D : Silicon leaf" << std::endl;
	std::cout << "E : Benitoite leaf" << std::endl;
	std::cout << "\n" << "-- Science" << std::endl;
	std::cout << "F : Red science" << std::endl;
	std::cout << "G : Green science" << std::endl;
	std::cout << "H : Blue science" << std::endl;
	std::cout << "I : Magenta science" << std::endl;
	std::cout << "J : Orange science" << std::endl;
	std::cout << "K : Black science" << std::endl;
	std::cout << "L : Strange science" << std::endl;
	std::cout << "\n" << "-- Others" << std::endl;
	std::cout << "M : Gems" << std::endl;
	std::cout << "N : Gold token" << std::endl;
	std::cout << "O : Silver token" << std::endl;
	std::cout << "P : BLC" << std::endl;
	std::cout << "Q : Coins" << std::endl;
	std::cout << "R : Borb" << std::endl;
	std::cout << "S : Cheese" << std::endl;
	std::cout << "Z : EVERYTHING AT ONCE!" << std::endl;

	std::cout << std::endl << "Type your choice...";
	char answer{};
	std::string currentSelection = "";
	short returnValue;
	do
	{
		flushTampons();
		answer = toupper(_getch());
		switch (answer)
		{
		case '1':
			currentSelection = "Normal leaf";
			returnValue = 0;
			break;
		case '2':
			currentSelection = "Gold leaf";
			returnValue = 1;
			break;
		case '3':
			currentSelection = "Platinum leaf";
			returnValue = 2;
			break;
		case '4':
			currentSelection = "Bismuth leaf";
			returnValue = 3;
			break;
		case '5':
			currentSelection = "Cosmic leaf";
			returnValue = 4;
			break;
		case '6':
			currentSelection = "Void leaf";
			returnValue = 5;
			break;
		case '7':
			currentSelection = "Exotic leaf";
			returnValue = 6;
			break;
		case '8':
			currentSelection = "Celestial leaf";
			returnValue = 7;
			break;
		case '9':
			currentSelection = "Mythical leaf";
			returnValue = 8;
			break;
		case 'A':
			currentSelection = "Lava leaf";
			returnValue = 9;
			break;
		case 'B':
			currentSelection = "Ice leaf";
			returnValue = 10;
			break;
		case 'C':
			currentSelection = "Obsidian leaf";
			returnValue = 11;
			break;
		case 'D':
			currentSelection = "Silicon leaf";
			returnValue = 12;
			break;
		case 'E':
			currentSelection = "Benitoite leaf";
			returnValue = 13;
			break;
		case 'F':
			currentSelection = "Red science";
			returnValue = 14;
			break;
		case 'G':
			currentSelection = "Green science";
			returnValue = 15;
			break;
		case 'H':
			currentSelection = "Blue science";
			returnValue = 16;
			break;
		case 'I':
			currentSelection = "Magenta science";
			returnValue = 17;
			break;
		case 'J':
			currentSelection = "Orange science";
			returnValue = 18;
			break;
		case 'K':
			currentSelection = "Black science";
			returnValue = 19;
			break;
		case 'L':
			currentSelection = "Stange science";
			returnValue = 20;
			break;
		case 'M':
			currentSelection = "Gems";
			returnValue = 21;
			break;
		case 'N':
			currentSelection = "Gold token";
			returnValue = 22;
			break;
		case 'O':
			currentSelection = "Silver token";
			returnValue = 23;
			break;
		case 'P':
			currentSelection = "BLC";
			returnValue = 24;
			break;
		case 'Q':
			currentSelection = "Coins";
			returnValue = 25;
			break;
		case 'R':
			currentSelection = "Borb";
			returnValue = 26;
			break;
		case 'S':
			currentSelection = "Cheese";
			returnValue = 27;
			break;
		case 'Z':
			currentSelection = "EVERYTHING AT ONCE!";
			returnValue = -1;
			break;
		}
	} while (currentSelection == "");

	std::cout << "\n\n\n";
	std::cout << "Current selection : " << currentSelection << std::endl;
	return returnValue;
}


double inputValidation()
{
	std::string answer;
	short x, y;
	double value;
	while (true)
	{
		std::cout << "Value to write (not negative): ";
		flushTampons();
		x = wherex();
		y = wherey();
		std::cin >> answer;
		if (answer == "quit")
			return -1;
		if (answer == "menu")
			return -2;
		gotoxy(x, y);
		clreoscr();
		try
		{
			value = std::stod(answer, nullptr);
			std::cout << value << std::endl;
			if (value < 0)
			{
				std::cout << "Please enter a positive number." << std::endl;
			}
			else
				break;
		}
		catch (const std::exception&)
		{
			std::cout << answer << std::endl;
			std::cout << "Invalid value of double." << std::endl;
		}
	}
	return value;
}

void getProcessId(DWORD& procId, LPCSTR lpWindowName)
{
	do
	{
		HWND hwnd = FindWindowA(NULL, "Leaf Blower Revolution");
		GetWindowThreadProcessId(hwnd, &procId);

		std::cout << "Process id ";
		if (procId == 0)
			std::cout << "not found; try opening the program." << std::endl;

		else
			std::cout << "found : " << procId << std::endl;

		std::cout << "Press any key to continue...";
		(void)_getch();
		std::cout << std::endl;
	} while (!procId);
	std::cout << "Type \"quit\" to quit, \"menu\" to get to main menu.";
}

ULONG64 GetModuleBaseAddress(const wchar_t moduleName[], DWORD pID) {
	ULONG64 dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
	MODULEENTRY32 ModuleEntry32{};
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &ModuleEntry32))
	{
		do {
			if (wcscmp(ModuleEntry32.szModule, moduleName) == 0)
			{
				dwModuleBaseAddress = (ULONG64)ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32));


	}
	CloseHandle(hSnapshot);
	return dwModuleBaseAddress;
}

ULONG64 getBaseAddress(std::vector<ULONG64>& addressOffsets, HANDLE hprocess, DWORD processId)
{
	ULONG64 targetAddress = GetModuleBaseAddress(L"game.exe", processId);
	for (USHORT i = 0; i < addressOffsets.size() - 1; i++)
		ReadProcessMemory(hprocess, (void*)(targetAddress + addressOffsets.at(i)), &targetAddress, sizeof(targetAddress), NULL);
	targetAddress += addressOffsets.back();
	return targetAddress;
}

void fillAddressesVector(std::vector<ULONG64>& valuesAddresses, HANDLE hprocess, DWORD processId)
{
	std::vector<std::vector<ULONG64>> addressOffsets;
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xB0, 0xDD0 });				// NORMAL LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xB0, 0x10, 0x130, 0x540 });	// GOLD LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xD0, 0xC20 });				// PLATINUM LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xB0, 0xD60 });				// BISMUTH LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xD0, 0xBB0 });				// COSMIC LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x300, 0xCE0 });				// VOID LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x280, 0x8A0 });				// EXOTIC LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xF0, 0xE70 });				// CELESTIAL LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xD0, 0xD00 });				// MYTHICAL LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x370, 0x870 });				// LAVA LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x230, 0x990 });				// ICE LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xB0, 0xB0 });				// OBSIDIAN LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xD0, 0xC90 });				// SILICON LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x110, 0x860 });				// BENITOITE LEAF
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x100, 0xE80 });				// RED SCIENCE
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xD0, 0x20, 0x140, 0xA20 });	// GREEN SCIENCE
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xF0, 0xE00 });				// BLUE SCIENCE
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x3F0, 0xC40 });				// MAGENTA SCIENCE
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x370, 0xF70 });				// ORANGE SCIENCE
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x260, 0xFE0 });				// BLACK SCIENCE
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xB0, 0x7B0 });				// STRANGE SCIENCE
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xD0, 0xB40 });				// GEMS
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x370, 0xA30 });				// GOLD TOKEN
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x230, 0xF40 });				// SILVER TOKEN
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x100, 0xA20 });				// BLC
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0xB0, 0x580 });				// COINS
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x300, 0xEA0 });				// BORB
	addressOffsets.push_back({ 0x7FEEF0, 0x258, 0x10, 0x300, 0xB90 });				// CHEESE

	for (auto& i : addressOffsets)
		valuesAddresses.push_back(getBaseAddress(i, hprocess, processId));
}