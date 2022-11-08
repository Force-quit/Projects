#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include "../Utilities/utils.h"

std::string generatePassword(const std::string& alphabet, const unsigned short passwordLength)
{
	std::string password(passwordLength, '0');
	auto alphabetSize{ alphabet.size() };
	for (auto& character : password)
		character = alphabet[rand() % alphabetSize];
	return password;
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	SetConsoleTitleA("Password creator");
	std::cout << "Password generator\n";
	std::cout << "Max: " << UINT_MAX << " caracters" << "\n\n";

	const std::string DEFAULT_ALPHABET = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&()?@/";

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

		password = generatePassword(DEFAULT_ALPHABET, passwordLength);
		emile::copyToClipBoard(password);

		std::cout << "Password has been copied to clipboard\n";
		std::cout << "Password starts with : " << password.front() << " and ends with : " << password.back() << "\n\n";

		do
		{
			std::cout << "Press enter to continue or q to quit : ";
			emile::flushTampon();
			makeOtherPassword = toupper(_getche());
			std::cout << std::endl;
		} while (makeOtherPassword != '\r' and makeOtherPassword != 'Q');

		std::cout << std::endl;
	} while (makeOtherPassword != 'Q');
	return 0;
}