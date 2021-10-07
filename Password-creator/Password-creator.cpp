#include <iostream>
#include "../Utilities/utils.h"
#include "../Console(v1.9)/console(v1.9).h"
#include <conio.h>

void main() 
{
	SetConsoleTitleA("Password creator");
	std::string alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&()?@/";
	std::string password{};
	unsigned short passwordLength{};
	std::cout << "Password generator\n";
	std::cout << "Max: 30 000 caracters\n";
	while (true)
	{
		do
		{
			e_flushTampon();
			std::cout << "password length : ";
			std::cin >> passwordLength;
		} while (std::cin.fail() || passwordLength == 0 || passwordLength > 30000);
		
		password = e_passwordGenerator(alphabet, passwordLength);
		e_copyToClipBoard(password);
		std::cout << "Password has been copied to clipboard\n";
		std::cout << "Password starts with : " << password.front() << " and ends with : " << password.back() << '\n';
		std::cout << "Press any key to continue...";
		e_flushTampon();
		(void)_getch();
		std::cout << "\n\n";
	}
}