#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

struct Position {
	double X;
	double Y;
	double Yaw;
	double Pitch;
};

class Player {
	public:
		std::string name;
		int health;
		Position position;
		friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

std::ostream& operator<<(std::ostream& os, const Player& player) {
	os << "Player("
		<< "Name: \"" << player.name << '\"'
		<< ", Health: " << player.health
		<< ", Position: Position("
			<< "X: " << player.position.X
			<< ", Y: " << player.position.Y
			<< ", Yaw: " << player.position.Yaw
			<< ", Pitch: " << player.position.Pitch
		<< ")"
	<< ")";
	return os;
}

int main() {
	Position pos = { 27.01, 25, 91.98, 25.7 };
	Player player = { "John", 100, pos };

	std::cout << player;

	std::cin.ignore();
	return 0;
}


//https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading#4421719