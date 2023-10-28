#include "../Utilities/utils.h"
#include "inputRecorder.h"
#include <iostream>

int main()
{
	auto title = R"( (                                                                        
 )\ )                        )                            (               
(()/(                 (   ( /(   (      (           (     )\ )   (   (    
 /(_)) (     `  )    ))\  )\())  )(    ))\  (   (   )(   (()/(  ))\  )(   
(_))   )\ )  /(/(   /((_)(_))/  (()\  /((_) )\  )\ (()\   ((_))/((_)(()\  
|_ _| _(_/( ((_)_\ (_))( | |_    ((_)(_))  ((_)((_) ((_)  _| |(_))   ((_) 
 | | | ' \))| '_ \)| || ||  _|  | '_|/ -_)/ _|/ _ \| '_|/ _` |/ -_) | '_| 
|___||_||_| | .__/  \_,_| \__|  |_|  \___|\__|\___/|_|  \__,_|\___| |_|   
            |_|                                                           
)";

	std::cout << title << std::endl;
	
	char choice{};
	emile::Console::disableQuickEdit();
	do
	{
		std::cout << "Record a session : 1" << std::endl;
		std::cout << "Playback last session : 2" << std::endl;

		do
		{
			emile::flushTampon();
			std::cout << "Select : ";
			std::cin >> choice;
		} while (std::cin.fail() || choice != '1' and choice != '2');

		std::cout << std::endl;
		
		if (choice == '1')
			record();
		else
			loadAndPlay();

		std::cout << std::endl;

		do
		{
			emile::flushTampon();
			std::cout << "Do you want to perform another action? (Y/N) : ";
			std::cin >> choice;
			choice = toupper(choice);
		} while (std::cin.fail() || choice != 'Y' and choice != 'N');
		std::cout << std::endl;
	} while (choice == 'Y');
	return 0;
}