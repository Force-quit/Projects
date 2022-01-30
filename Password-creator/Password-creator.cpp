#include "../Utilities/utils.h"
#include <iostream>
#include <conio.h>

int main() 
{

	SetConsoleTitleA("Password creator");
	std::cout << "Password generator\n";
	std::cout << "Max: 4294967295 caracters" << "\n\n";

	const std::string alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&()?@/";
	unsigned int passwordLength{};
	std::string password{};
	char makeOtherPassword{};

	do 
	{
		do
		{
			emile::flushTampon();
			std::cout << "Password length : ";
			std::cin >> passwordLength;
		} while (std::cin.fail() || passwordLength == 0);
		
		password = emile::passwordGenerator(alphabet, passwordLength);
		emile::copyToClipBoard(password);

		std::cout << "Password has been copied to clipboard\n";
		std::cout << "Password starts with : " << password.front() << " and ends with : " << password.back() << "\n\n";
		
		do
		{
			std::cout << "Press enter to continue or q to quit : ";
			emile::flushTampon();
			makeOtherPassword = toupper(_getche());
			std::cout << std::endl;
		} while (makeOtherPassword != 13 and makeOtherPassword != 81);

		std::cout << std::endl;
	} while (makeOtherPassword != 81);
	return 0;
}