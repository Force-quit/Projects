#include "IdleSpiral.h"
#include <Windows.h>
#include <iostream>
#include "../Utilities/utils.h"

int main()
{
	emile::Console::disableQuickEdit();
	DWORD processId{};
	getProcessId(processId, "IdleSpiral");
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (hProcess != INVALID_HANDLE_VALUE)
		startHacking(processId, hProcess);
	else
		std::cout << "OpenProcess failed with code : " << GetLastError();

	CloseHandle(hProcess);
	std::cout << "\n\n" << "Closing...";
	Sleep(1500);
	return 0;
}