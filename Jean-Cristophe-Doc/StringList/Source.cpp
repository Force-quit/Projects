#include "StringList.h"
#include <iostream>



void show(std::string& str) { std::cout << str << " "; }

int main()
{
	StringList myList;

	myList.append("Allo");
	myList.append("Toi");
	myList.append("Monde");

	myList.traverse([](StringList::value_type& str){ str += " yo yo"; });
	myList.traverse(show);

	std::string cool(myList.front());
	std::cout << myList.front();
	myList.front() = "Yo";
	std::cout << myList.front();

	myList.clear();

	return 0;
}