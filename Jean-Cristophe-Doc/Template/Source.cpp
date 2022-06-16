#include "StringList.h"
#include <iostream>

#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

void show(std::string& str) { std::cout << str << " "; }
void showi(int i) { std::cout << i << " "; }

void test_vect()
{
	std::vector<int> v(10);
	for (int i{}; i < v.size(); ++i) {
		v[i] = 0;
	}
	for (auto i : v) {
		showi(i);

	}
	std::vector<int>::iterator it(v.begin());
	std::vector<int>::iterator end(v.end());
	while (it != end) {
		std::cout << *it;
		++it;
	}
	for (auto it(v.begin()); it != v.end(); ++it) {
		std::cout << *it;
	}

	std::for_each(std::next(v.begin(), 3), v.end(), showi);
	std::iota(v.begin(), v.end(), 0);
}

using StringList = List<std::string>;

int main()
{
	StringList myList;

	for (auto i : myList) {
		std::cout << i;
	}


	myList.append("Allo");
	myList.append("Toi");
	myList.append("Monde");

	size_t size{ 10 };
	myList.traverse([size](StringList::value_type & str){ str += std::string(size, ' '); });
	std::cout << "\n";
	myList.traverse(show);

	std::string cool(myList.front());
	std::cout << myList.front();
	myList.front() = "Yo";
	std::cout << myList.front();

	myList.clear();

	return 0;
}