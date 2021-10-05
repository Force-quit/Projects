#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>


void findWord(const std::string wordList[], const std::string &subString)
{
    short counter{};
    for (uint32_t i = 0; i < 208913; i++)
    {
        if (wordList[i].find(subString) != std::string::npos)
        {
            std::cout << wordList[i] << "\n";
            ++counter;
            if (counter == 25)
                break;
        }
    }
}

int main()
{
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);
    SetConsoleTitleA("Trouveur de mots avec échantillon");

    const unsigned int NB_FILE_LINES = 208913;

    std::ifstream file("francais.txt");
    if (!file.good())
    {
        std::cout << "Ey! Yé où mon fichier texte?";
        Sleep(5000);
        return 0;
    }

    std::string* wordList = new std::string[NB_FILE_LINES]{};

    for (unsigned int i = 0; i < NB_FILE_LINES; i++)
        std::getline(file, wordList[i]);

    file.close();

    std::string subString{};
    while (true)
    {
        std::cout << "-------------------------" << '\n';
        std::cout << "Échantillon de mot à trouver : ";
        std::cin >> subString;
        findWord(wordList, subString);
    }

    return 0;
}