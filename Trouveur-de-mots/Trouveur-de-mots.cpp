#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>
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
			std::cout << counter << ") " << wordList[i] << "\n";
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
		return 0;
	}

	std::unique_ptr<std::string[]> wordList = std::make_unique<std::string[]>(NB_FILE_LINES);

	for (unsigned int i = 0; i < NB_FILE_LINES; i++)
		std::getline(file, wordList[i]);

	file.close();

	std::string subString{};
	std::unordered_map<short, std::string> map;
	short choice{};
	while (true)
	{
		std::cout << "-------------------------" << '\n';
		std::cout << "Échantillon de mot à trouver : ";
		std::cin >> subString;
		map = findWord(wordList, subString);
		std::cin >> choice;
		if (choice <= map.size() && choice >= 1)
			e_copyToClipBoard(map.at(choice));
	}

	return 0;
}