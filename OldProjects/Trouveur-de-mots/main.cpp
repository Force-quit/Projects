#include "Trouveur-de-mots.h"
#include <Windows.h>
#include <fstream>
#include <iostream>

int main()
{
	std::ifstream wordListFile("francais.txt");
	if (wordListFile.good())
	{
		SetConsoleCP(1252);
		SetConsoleOutputCP(1252);
		SetConsoleTitleA("Trouveur de mots par �chantillon");
		std::cout << "Trouveur de mots par �chantillon\n";


		std::vector<std::string> wordList;
		std::string word;
		while (std::getline(wordListFile, word))
			wordList.push_back(word);

		const unsigned short MAX_FINDS = 25;
		mainLoop(wordList, MAX_FINDS);
	}
	else
	{
		std::cout << "List de mots pas trouv�e.";
		std::cout << "Assurez-vous d'avoir le fichier �Francais.txt� dans le m�me r�pertoire que ce programme.";
		std::cin.get();
	}
	
	return 0;
}