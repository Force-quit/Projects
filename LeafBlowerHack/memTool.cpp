#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>
#include <string>
#include <Psapi.h>
#include <conio.h>
#include <tchar.h>
#include "Utilities/usefullshit.h"

// Prototypes
DWORD getProcessId(const wchar_t processName[]);
USHORT writeToMemory(HANDLE hProcess, void* memoryAdress);
ULONG64 GetModuleBaseAddress(const wchar_t moduleName[], DWORD pID);
std::vector<ULONG64> threadList(DWORD& pid);
//ULONG64 GetThreadStartAddress(HANDLE hProcess, HANDLE hThread);

// Fonction definitions
DWORD getProcessId(const wchar_t processName[])
{
	HANDLE hProcessSnap{};
	PROCESSENTRY32 pe32{};
	DWORD processId{};

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
					processId = pe32.th32ProcessID;
					break;
				}
			} while (Process32Next(hProcessSnap, &pe32));
		}
	}
	CloseHandle(hProcessSnap);
	return processId;
}

USHORT writeToMemory(HANDLE hProcess, void* memoryAdress)
{
	DWORD valueToWrite{};
	std::cout << "Input new value : ";
	std::cin >> valueToWrite;
	if (valueToWrite == 0)
		return 0;
	if (WriteProcessMemory(hProcess, memoryAdress, &valueToWrite, sizeof valueToWrite, NULL) != 0)
		std::cout << "Value written to adress." << std::endl;
	else
		std::cout << "Error writing to that adress." << std::endl;
	return 1;
}

ULONG64 GetModuleBaseAddress(const wchar_t moduleName[], DWORD pID) {
	ULONG64 dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID); // make snapshot of all modules within process
	MODULEENTRY32 ModuleEntry32{};
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &ModuleEntry32)) //store first Module in ModuleEntry32
	{
		do {
			if (wcscmp(ModuleEntry32.szModule, moduleName) == 0) // if Found Module matches Module we look for -> done!
			{
				dwModuleBaseAddress = (ULONG64)ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32)); // go through Module entries in Snapshot and store in ModuleEntry32


	}
	CloseHandle(hSnapshot);
	return dwModuleBaseAddress;
}

int main()
{
	DWORD processId{};
	do
	{
		//processId = getProcessId(L"chien.exe");	  // Get a litteral process id
		HWND hwnd = FindWindowA(NULL, "Game"); // Get a named window process id
		GetWindowThreadProcessId(hwnd, &processId);

		std::cout << "Process id ";
		if (processId == 0)
			std::cout << "not found; try opening the program." << std::endl;

		else
			std::cout << "found : " << processId << std::endl;

		system("pause");
	} while (!processId);

	std::cout << std::endl;

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (hProcess != INVALID_HANDLE_VALUE)
	{
		//std::vector<ULONG64> threadsId = threadList(processId);
		ULONG64 baseAddress = GetModuleBaseAddress(L"aswhook.dll", processId);
		//HANDLE hThread = OpenThread(THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION, FALSE, threadsId.at(0));
		//ULONG64 threadStartAddress = GetThreadStartAddress(hProcess, hThread);
		std::cout << "Base adress         : " << std::hex << std::uppercase << baseAddress << std::endl;
		std::vector<ULONG64> addressOffsets{ 0xAEA0, 0x30, 0x1C8, 0x78, 0x28, 0x8D0 };
		ULONG64 targetAddress = baseAddress;
		std::cout << "Target adress       : " << std::hex << targetAddress << std::endl;
		for (USHORT i = 0; i < addressOffsets.size() - 1; i++)
		{
			ReadProcessMemory(hProcess, (void*)(targetAddress + addressOffsets.at(i)), &targetAddress, sizeof(targetAddress), NULL);
			std::cout << "Target adress       : " << std::hex << targetAddress << std::endl;
		}

		targetAddress += addressOffsets.back(); // Weird shit voodoo doesn't work in for loop
		std::cout << "Final target adress : " << std::hex << targetAddress << "\n\n";

		do
		{
			flushTampons();
			if (!writeToMemory(hProcess, (void*)targetAddress))
				break;
		} while (true);
	}
	else
		std::cout << "OpenProcess failed with code : " << GetLastError();

	CloseHandle(hProcess);

	system("pause");
	return 0;
}

std::vector<ULONG64> threadList(DWORD &pid) 
{
	std::vector<ULONG64> vect = std::vector<ULONG64>();
	HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (h != INVALID_HANDLE_VALUE)
	{
		THREADENTRY32 te{};
		te.dwSize = sizeof(te);
		if (Thread32First(h, &te))
		{
			do
			{
				if (te.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof(te.th32OwnerProcessID))
					if (te.th32OwnerProcessID == pid)
						vect.push_back(te.th32ThreadID);
				
				te.dwSize = sizeof(te);
			} while (Thread32Next(h, &te));
		}
	}

	return vect;
}

//ULONG64 GetThreadStartAddress(HANDLE hProcess, HANDLE hThread)
//{
//	DWORD used = 0, ret = 0;
//	DWORD stacktop = 0, result = 0;
//
//	MODULEINFO mi;
//
//	GetModuleInformation(hProcess, GetModuleHandleA("KERNEL32.dll"), &mi, sizeof(mi));
//	//stacktop = (DWORD)GetThreadStackTopAddress_x86(processHandle, hThread);
//
//	/* The stub below has the same result as calling GetThreadStackTopAddress_x86()
//	change line 54 in ntinfo.cpp to return tbi.TebBaseAddress
//	Then use this stub
//	*/
//	//LPCVOID tebBaseAddress = GetThreadStackTopAddress_x86(processHandle, hThread);
//	//if (tebBaseAddress)
//	//	ReadProcessMemory(processHandle, (LPCVOID)((DWORD)tebBaseAddress + 4), &stacktop, 4, NULL);
//
//	CloseHandle(hThread);
//
//	if (stacktop) {
//		//find the stack entry pointing to the function that calls "ExitXXXXXThread"
//		//Fun thing to note: It's the first entry that points to a address in kernel32
//
//		DWORD* buf32 = new DWORD[4096];
//
//		if (ReadProcessMemory(processHandle, (LPCVOID)(stacktop - 4096), buf32, 4096, NULL)) {
//			for (int i = 4096 / 4 - 1; i >= 0; --i) {
//				if (buf32[i] >= (DWORD)mi.lpBaseOfDll && buf32[i] <= (DWORD)mi.lpBaseOfDll + mi.SizeOfImage) {
//					result = stacktop - 4096 + i * 4;
//					break;
//				}
//
//			}
//		}
//
//		delete buf32;
//	}
//
//	return result;
//}