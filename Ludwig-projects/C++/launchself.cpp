#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

static string utf16ToUTF8(const wstring& s)
{
	const int size = ::WideCharToMultiByte(CP_UTF8, 0, s.c_str(), -1, NULL, 0, 0, NULL);

	vector<char> buf(size);
	::WideCharToMultiByte(CP_UTF8, 0, s.c_str(), -1, &buf[0], size, 0, NULL);

	return string(&buf[0]);
}

int main()
{
	WCHAR path0[1020];
	DWORD size = GetModuleFileNameW(NULL, path0, 1020);

	wcout << "this is the name of the path " << path0 << '\n';

	Sleep(2500);

	string utf8String = utf16ToUTF8(path0);
	LPCSTR path = utf8String.c_str();

	ShellExecuteA(NULL, "open", path, NULL, NULL, SW_MINIMIZE);

	Sleep(2500);

	return 0;
}