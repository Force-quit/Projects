#pragma once
#include <Windows.h>
#include <vector>

double numberInputValidation();
void getProcessId(DWORD& procId, LPCSTR lpWindowName);
ULONG64 GetModuleBaseAddress(const wchar_t moduleName[], DWORD pID);
ULONG64 getBaseAddress(std::vector<ULONG64>& addressOffsets, HANDLE hprocess, DWORD processId);
void fillAddressesVector(std::vector<ULONG64>& valuesAddresses, HANDLE hprocess, DWORD processId);
short menuSelection();
void startHacking(DWORD& processId, HANDLE& hProcess);