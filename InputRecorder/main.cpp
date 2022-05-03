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
	std::cout << "Record a session : 1" << std::endl;
	std::cout << "Playback last session : 2" << std::endl;

	char choice{};
	do
	{
		emile::flushTampon();
		std::cout << "Select : ";
		std::cin >> choice;
	} while (std::cin.fail() || choice != '1' and choice != '2');


	emile::consoleBundle();
	if (choice == '1')
		record();
	else
		loadAndPlay();

	return 0;
}