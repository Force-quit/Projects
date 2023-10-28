#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "../Utilities/utils.h"
#include "Trouveur-de-mots.h"


std::unordered_map<short, std::string> findWord(const std::vector<std::string>& wordList, const std::string& subString, const unsigned int& NB_WORDS, const unsigned short MAX_FINDS)
{
	unsigned short counter{};
	std::unordered_map<short, std::string> matches{};
	for (unsigned int i = 0; i < NB_WORDS; i++)
	{
		if (wordList[i].find(subString) != std::string::npos)
		{
			++counter;
			std::cout << std::setw(3) << counter << ") " << wordList[i] << "\n";
			std::pair<short, std::string> mapping(counter, wordList[i]);
			matches.insert(mapping);
			if (counter == MAX_FINDS)
				break;
		}
	}
	return matches;
}

void mainLoop(const std::vector<std::string>& wordList, const unsigned short& MAX_FINDS)
{
	std::string subString;
	std::unordered_map<unsigned short, std::string> matchesMap;
	short choice{};

	bool findOtherWords = true;
	while (findOtherWords)
	{
		std::cout << "-------------------------" << '\n';

		do
		{
			emile::flushTampon();
			std::cout << "Échantillon de mot à trouver : ";
			std::cin >> subString;
		} while (std::cin.fail());


		for (auto& c : subString)
			c = std::tolower(c);

		if (subString == "0")
		{
			findOtherWords = false;
			continue;
		}

		matchesMap = findWord(wordList, subString, 1, MAX_FINDS);

		if (matchesMap.size() == 0)
			std::cout << "Aucun mot avec cet échantillon\n";
		else
		{
			do
			{
				emile::flushTampon();
				std::cout << "Numéro du mot à copier : ";
				std::cin >> choice;
			} while (std::cin.fail() || choice > matchesMap.size() || choice < 0);

			if (choice == 0)
				continue;

			emile::copyToClipBoard(matchesMap.at(choice));
			std::cout << "Mot copié dans le clipboard windows\n";
		}
	}

}

void findWords(const std::vector<std::string>& wordList, const std::string& subStr, const unsigned short& MAX_RESULTS, std::unordered_map<unsigned short, std::string>& foundWords)
{

}
