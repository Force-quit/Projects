export module eutilities;

#ifdef _WIN32
export import :windows;
#endif

export namespace eutilities
{
	//Reset the std::cin buffer.
	void resetConsoleInput();
}