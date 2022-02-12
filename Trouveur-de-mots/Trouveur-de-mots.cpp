#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <unordered_map>
#include <memory>
#include "../Utilities/utils.h"


const unsigned int NB_FILE_LINES = 208913;

std::unordered_map<short, std::string> findWord(const std::unique_ptr<std::string[]>& wordList, const std::string& subString)
{
	short counter{};
	std::unordered_map<short, std::string> matches{};
	for (unsigned int i = 0; i < NB_FILE_LINES; i++)
	{
		if (wordList[i].find(subString) != std::string::npos)
		{
			++counter;
			std::cout << std::setw(3) << counter << ") " << wordList[i] << "\n";
			std::pair<short, std::string> mapping(counter, wordList[i]);
			matches.insert(mapping);
			if (counter == 25)
				break;
		}
	}
	return matches;
}

int main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	SetConsoleTitleA("Trouveur de mots avec échantillon");


	std::ifstream file("francais.txt");
	if (!file.good())
	{
		std::cout << "Ey! Yé où mon fichier texte?";
		Sleep(5000);
	}
	else
	{
		auto wordList = std::make_unique<std::string[]>(NB_FILE_LINES);

		for (unsigned int i = 0; i < NB_FILE_LINES; i++)
			std::getline(file, wordList[i]);

		file.close();

		std::string subString{};
		std::unordered_map<short, std::string> map;
		short choice{};
		std::cout << "Trouveur de mots avec échantillon\n";
		while (true)
		{
			std::cout << "-------------------------" << '\n';
			std::cout << "Échantillon de mot à trouver : ";
			std::cin >> subString;

			
			for (auto& c : subString)
				c = std::tolower(c);
			
			map = findWord(wordList, subString);
			if (map.size() > 0)
			{
				do
				{
					emile::flushTampon();
					std::cout << "Numéro du mot à copier : ";
					std::cin >> choice;
				} while (std::cin.fail() || choice > map.size() || choice < 0);

				if (choice == 0)
					continue;

				emile::copyToClipBoard(map.at(choice));
				std::cout << "Mot copié dans le clipboard windows\n";
			}
			else
				std::cout << "Aucun mot avec cet échantillon\n";
		}
	}

	return 0;
}