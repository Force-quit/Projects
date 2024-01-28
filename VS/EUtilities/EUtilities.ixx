export module eutilities;

#ifdef _WIN32
export import :windows;
#endif

export namespace eutilities
{
	//Reset the std::cin buffer.
	void resetConsoleInput();

	/**
	* Sleep for a certain time.
	*
	* @param msDuration The duration in milliseconds.
	*/
	void sleepFor(int msDuration);
}