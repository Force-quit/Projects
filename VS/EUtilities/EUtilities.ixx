module;

#include <string_view>

export module eutilities;

#ifdef _WIN32
export import :windows;
#endif

export namespace eutilities
{
	void flushTampon();

	// Create folder if it doesn't exist. Returns false if folder did not exist
	bool ensureFolderExists(const std::string_view dirName);

	bool folderExists(const std::string_view dirName);
}