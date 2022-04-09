#include "drugDealer.h"
#include <iomanip>
#include <iostream>
#include "../Utilities/utils.h"
#include <vector>

void listDrugs(const std::map<short, std::string>& drugTypes)
{
	std::cout << "Drug types --->" << std::endl;
	for (const auto& it : drugTypes)
		std::cout << std::left << std::setw(20) << it.second << ": " << it.first << std::endl;

	std::cout << std::endl;
}

unsigned short getDrugType(const std::map<short, std::string>& drugTypes)
{
	unsigned short drugType{};
	do
	{
		emile::flushTampon();
		std::cout << "Select a drug type (or 0 to stop taking orders) : ";
		std::cin >> drugType;
	} while (std::cin.fail() || !drugTypes.count(drugType) and drugType != 0);
	std::cout << std::endl;
	return drugType;
}

short getTotalFromList(std::string& list, std::vector<short>& typeOfDrugNeeded)
{
	if (!isdigit(list[0]))
		return -1;

	std::string currentNumber = "";
	std::vector<short> addition;
	for (char& character : list)
	{
		if (!isdigit(character) and character != ',' or character == ',' and currentNumber == "")
			return -1;
		else if (character == ',')
		{
			try
			{
				addition.push_back(std::stoi(currentNumber));
			}
			catch (const std::out_of_range& e)
			{
				(void)e.what();
				std::cout << "Fuck off that's too big\n";
				return -1;
			}
			currentNumber = "";
		}
		else
			currentNumber += character;
	}

	if (!currentNumber.empty())
	{
		try
		{
			addition.push_back(std::stoi(currentNumber));

		}
		catch (const std::out_of_range& e)
		{
			(void)e.what();
			std::cout << "Fuck off that's too big\n";
			return -1;
		}
	}

	short totalAdded{ 0 };
	for (auto& i : addition)
	{
		totalAdded += i;
		typeOfDrugNeeded.push_back(i);
	}
	return totalAdded;
}

void takeOrders(const std::map<short, std::string>& drugTypes, std::map<short, std::vector<short>>& drugsNeeded)
{
	drugsNeeded.clear();
	std::cout << "--- Taking new orders ---" << std::endl;
	listDrugs(drugTypes);

	unsigned short drugType{};
	while (true)
	{
		drugType = getDrugType(drugTypes);
		if (drugType == 0)
			break;
		std::cout << "Selected " << drugTypes.at(drugType) << "\n\n";

		std::string gramsToAdd{};
		std::cout << "Write a list like : 13,45,65,12,3 . . ." << std::endl;
		short totalGrams{};
		do
		{
			do
			{
				emile::flushTampon();
				std::cout << "Amount to add : ";
				std::cin >> gramsToAdd;
			} while (std::cin.fail());

			totalGrams = getTotalFromList(gramsToAdd, drugsNeeded[drugType]);

			if (totalGrams == -1)
				std::cout << "Bro wtf? Your list is not correct" << std::endl;
			else if (totalGrams != 0)
				std::cout << "Added " << totalGrams << " grams of " << drugTypes.at(drugType) << std::endl;

		} while (totalGrams == -1);
		std::cout << std::endl;
	}
}

void printTotals(const std::map<short, std::string>& drugTypes, const std::map<short, std::vector<short>>& drugsNeeded)
{
	std::string string = "These orders require a total of : ";
	if (drugsNeeded.size() == 0)
		string += "0 nothing you dumbass..";
	else
	{
		for (auto& it : drugsNeeded)
		{
			short total{ 0 };
			for (auto& i : it.second)
				total += i;

			string += drugTypes.at(it.first) + "(" + std::to_string(total) + ") ";
		}
	}

	std::cout << string << "\n\n";
}

void printTotalBags(const std::map<short, std::string>& drugTypes, std::map<short, std::vector<short>>& drugsNeeded)
{
	const std::vector<short> packageSizes = { 1000, 500, 100, 50, 20, 10, 5, 3, 2, 1 };
	for (auto& drugNeeded : drugsNeeded)
	{
		std::cout << drugTypes.at(drugNeeded.first) << std::endl;
		std::cout << "----------" << std::endl;
		for (const auto& packageSize : packageSizes)
		{
			short nbPackagesOfThisSize{ 0 };
			for (auto& order : drugNeeded.second)
			{
				if (order == 0)
					continue;
				short thisOrdersTake{ 0 };
				thisOrdersTake += order / packageSize;
				nbPackagesOfThisSize += thisOrdersTake;
				order -= packageSize * thisOrdersTake;


			}
			if (nbPackagesOfThisSize != 0)
				std::cout << std::to_string(packageSize) << "g x " << std::to_string(nbPackagesOfThisSize) << std::endl;
		}
		std::cout << std::endl;
	}
}

void prepareConsole()
{
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 1200, 550, FALSE);
}
