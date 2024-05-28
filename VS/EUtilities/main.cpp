import eutilities;

#include <string>

int main()
{
	eutilities::sleepFor(300);
	eutilities::fullKeyPress(eutilities::Key::WINDOWS);
	std::wstring messageToType = L"Salut! Je suis Émile Laforce @ École de technologie supérieure !! 🤷‍👌👌";
	eutilities::sleepFor(300);
	eutilities::humanType(messageToType, 40);
}
