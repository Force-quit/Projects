#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "../Utilities/utils.h"


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

unsigned int fillWordsList(std::vector<std::string>& wordList)
{
	std::ifstream file("francais.txt");
	unsigned int nbLines{ 0 };
	if (!file.good())
	{
		std::cout << "La liste de mots n'est pas à la bonne place...";
	}
	else
	{
		std::string s;
		std::cout << "Lecture du fichier de mots...\n";
		while (std::getline(file, s))
			++nbLines;

		file.clear();
		file.seekg(0);

		wordList.resize(nbLines);

		for (unsigned int i = 0; i < nbLines; i++)
			std::getline(file, wordList[i]);

		file.close();
		std::cout << "Lecture terminée.\n\n";
	}


	return nbLines;
}

void mainLoop(std::vector<std::string>& wordList, const unsigned int WORDS_LIST_LENGTH, const unsigned short MAX_FINDS)
{
	std::string subString{};
	std::unordered_map<short, std::string> matchesMap;
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

		matchesMap = findWord(wordList, subString, WORDS_LIST_LENGTH, MAX_FINDS);

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

int main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	SetConsoleTitleA("Trouveur de mots avec échantillon");


	std::vector<std::string> wordList;
	const unsigned int WORDS_LIST_LENGTH = fillWordsList(wordList);

	if (WORDS_LIST_LENGTH == 0)
	{
		emile::flushTampon();
		std::cin.get();
	}
	else
	{
		const unsigned short MAX_FINDS = 25;

		std::cout << "Trouveur de mots avec échantillon\n";
		mainLoop(wordList, WORDS_LIST_LENGTH, MAX_FINDS);
	}

	return 0;
}