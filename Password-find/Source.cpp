#include <iostream>

int main()
{
	const short ALPHABET_LENGHT = 27;
	const char alphabet[ALPHABET_LENGHT] = "abcdefghijklmnop0123456789"; //"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&()?@/"
	
	const short ANSWER_LENGHT = 5;
	char answer[ANSWER_LENGHT];

	for (short i = 0; i < ANSWER_LENGHT; i++)
		answer[i] = alphabet[0];
	

	/*for (int i = 0; i < ALPHABET_LENGHT; i++)
	{

	}*/

	std::cout << "Alphabet : " << alphabet << std::endl;
	std::cout << "Answer : " << answer;
	std::cin.get();
	return 0;
}