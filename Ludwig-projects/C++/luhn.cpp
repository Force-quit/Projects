#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//Returns true is the credit card number is valid and false otherwise
bool Luhn(const string CARDNUM)
{
	//Reverse
	const int len = CARDNUM.size();
	string card = CARDNUM;
	int sumodd = 0, sumeven = 0;
	char add;

	for (int i = 0; i < len / 2; ++i)
	{
		swap(card[i], card[len - i - 1]);
	};

	//Odd digits
	for (int i = 0; i <= len; i += 2)
	{
		add = card[i] - '0';
		if (add >= 0)
			sumodd += add;
	};

	//Even digits
	for (int i = 1; i <= len; i += 2)
	{
		add = (card[i] - '0') * 2;
		if (add >= 10)
			add = add / 10 + add % 10;
		if (add >= 0)
			sumeven += add;
	};
	
	//Check
	if ((sumodd + sumeven) % 10 == 0 && len >= 9)
		return true;
	else
		return false;
}

//Luhn algorithm without reversing the string first
bool Luhn2(const string CARDNUM)
{
	const int len = CARDNUM.size();
	int sumodd = 0, sumeven = 0;
	char add;

	//Odd digits
	for (int i = len - 1; i >= 0; i -= 2)
	{
		add = CARDNUM[i] - '0';
		if (add >= 0)
			sumodd += add;
	};

	//Even digits
	for (int i = len - 2; i >= 0; i -= 2)
	{
		add = (CARDNUM[i] - '0') * 2;
		if (add >= 10)
			add = add / 10 + add % 10;
		if (add >= 0)
			sumeven += add;
	};

	//Check
	if ((sumodd + sumeven) % 10 == 0 && len >= 9)
		return true;
	else
		return false;
}

int main()
{
	string carte;
	cout << "Entrez un num\202ro de carte de cr\202dit: ";
	cin >> carte;

	if (Luhn2(carte) == 1)
		cout << "Num\202ro valide.\n";
	else
		cout << "Num\202ro invalide.\n";
	system("pause");
}