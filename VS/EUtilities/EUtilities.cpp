module;

#include <iostream>
#include <Windows.h>
#include <filesystem>

module eutilities;

void eutilities::flushTampon()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}

bool eutilities::ensureFolderExists(const std::string_view dirName)
{
	bool folderExists = eutilities::folderExists(dirName);
	if (!folderExists)
		std::filesystem::create_directory(dirName);
	return folderExists;
}

bool eutilities::folderExists(const std::string_view dirName)
{
	return std::filesystem::is_directory(dirName);
}