#include "IdleSpiral.h"
#include <iostream>
#include "../Utilities/utils.h"
#include <TlHelp32.h>

short menuSelection()
{
	std::cout << std::endl << "-----MENU-----" << "\n";
	std::cout << "1 : r" << std::endl;

	std::cout << std::endl;
	char answer{};
	char currentSelection{};
	short returnValue{};
	do
	{
		do
		{
			emile::flushTampon();
			std::cout << "Select a resource : ";
			std::cin >> answer;
		} while (std::cin.fail());

		switch (answer)
		{
		case '1':
			currentSelection = 'r';
			returnValue = 0;
			break;
		}
	} while (!currentSelection);

	std::cout << std::endl << "Current selection : " << currentSelection << std::endl;
	return returnValue;
}

void startHacking(DWORD& processId, HANDLE& hProcess)
{
	std::vector<ULONG64> valuesAddresses;
	fillAddressesVector(valuesAddresses, hProcess, processId);

	bool keepChangingValues{ true };
	while (keepChangingValues)
	{
		short typeOfResource = menuSelection();
		std::cout << "Type -1 to quit, or -2 to change resource" << std::endl;
		double valueToWrite{};
		bool updateSameResource{ true };
		while (updateSameResource)
		{
			valueToWrite = numberInputValidation();

			if (valueToWrite < 0)
				updateSameResource = false;
			else
			{
				WriteProcessMemory(hProcess, (void*)valuesAddresses.at(typeOfResource), &valueToWrite, sizeof(double), NULL);
				std::cout << "Value successfully written." << std::endl;
			}
		}

		if (valueToWrite == -1)
			keepChangingValues = false;
	}
}


double numberInputValidation()
{
	double value{};
	bool badInput{ true };
	while (badInput)
	{
		do
		{
			emile::flushTampon();
			std::cout << "New value : ";
			std::cin >> value;
		} while (std::cin.fail());

		if (value >= -2)
			badInput = false;
	}
	return value;
}

void getProcessId(DWORD& procId, LPCSTR lpWindowName)
{
	do
	{
		HWND hwnd = FindWindowA(NULL, lpWindowName);
		GetWindowThreadProcessId(hwnd, &procId);

		std::cout << "Process id ";
		if (procId == 0)
			std::cout << "not found; try opening the program." << std::endl;
		else
			std::cout << "found : " << procId << std::endl;

		std::cout << "Press enter to continue...";
		std::cin.get();
	} while (!procId);
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
	ULONG64 targetAddress = GetModuleBaseAddress(L"UnityPlayer.dll", processId);
	for (USHORT i = 0; i < addressOffsets.size() - 1; i++)
		ReadProcessMemory(hprocess, (void*)(targetAddress + addressOffsets.at(i)), &targetAddress, sizeof(targetAddress), NULL);
	targetAddress += addressOffsets.back();
	return targetAddress;
}

void fillAddressesVector(std::vector<ULONG64>& valuesAddresses, HANDLE hprocess, DWORD processId)
{
	std::vector<std::vector<ULONG64>> addressOffsets;
	addressOffsets.push_back({ 0x1A4ED98, 0x20, 0xB0, 0x60, 0x18, 0xB0, 0x40, 0xE0 }); // R

	for (auto& i : addressOffsets)
		valuesAddresses.push_back(getBaseAddress(i, hprocess, processId));
}