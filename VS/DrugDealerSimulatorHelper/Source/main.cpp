import eutilities;

#include "../Headers/drugDealer.h"
#include <iostream>
#include <string>
#include <map>
#include <Windows.h>
#include <vector>

int main()
{
	auto title = R"(
 ______     ______     __    __      _____       ______      _____     ____     _____        _____   ______    
(_  __ \   (   __ \    ) )  ( (     / ___ \     (_  __ \    / ___/    (    )   (_   _)      / ___/  (   __ \   
  ) ) \ \   ) (__) )  ( (    ) )   / /   \_)      ) ) \ \  ( (__      / /\ \     | |       ( (__     ) (__) )  
 ( (   ) ) (    __/    ) )  ( (   ( (  ____      ( (   ) )  ) __)    ( (__) )    | |        ) __)   (    __/   
  ) )  ) )  ) \ \  _  ( (    ) )  ( ( (__  )      ) )  ) ) ( (        )    (     | |   __  ( (       ) \ \  _  
 / /__/ /  ( ( \ \_))  ) \__/ (    \ \__/ /      / /__/ /   \ \___   /  /\  \  __| |___) )  \ \___  ( ( \ \_)) 
(______/    )_) \__/   \______/     \____/      (______/     \____\ /__(  )__\ \________/    \____\  )_) \__/  
                                                                                                               
)";
	std::map<short, std::string> drugTypes;
	drugTypes.insert({ 1, "MJ" });
	drugTypes.insert({ 2, "Amp" });
	drugTypes.insert({ 3, "Ecstasy" });
	drugTypes.insert({ 4, "Crystal meth" });
	drugTypes.insert({ 5, "Cocaine" });
	drugTypes.insert({ 6, "Heroin" });
	drugTypes.insert({ 7, "Fentanyl" });

	
	std::cout << title << std::endl;
	
	char continueTakingOrders;
	do
	{
		std::map<short, std::vector<short>> drugsNeeded;
		takeOrders(drugTypes, drugsNeeded);
		printTotals(drugTypes, drugsNeeded);
		if (drugsNeeded.size() != 0)
		{
			std::cout << "\n" << "Pack your drugs, dealer." << "\n\n";
			printTotalBags(drugTypes, drugsNeeded);
		}
		std::cout << "\n\n";
		do
		{
			eutilities::resetConsoleInput();
			std::cout << "Take other orders? (Y/N) : ";
			std::cin >> continueTakingOrders;
			continueTakingOrders = toupper(continueTakingOrders);
		} while (std::cin.fail() || continueTakingOrders != 'Y' and continueTakingOrders != 'N');
		std::cout << std::endl;
	} while (continueTakingOrders == 'Y');
	return 0;
}