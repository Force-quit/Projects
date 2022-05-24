#include <iostream>
#include <string>
#include <Windows.h>
#include <random>
#include <conio.h>

enum Direction {up = 80, down = 72, left = 75, right = 77};

class Player {
	private:
		int x_, y_;
		void ChangePos(int, int);

	public:
		Player(int x, int y) { x_ = x; y_ = y; };
		int x() const { return x_; };
		int y() const { return y_; };
		void Move(Direction, int);

};

class Map {
	public:
		const int height = 25;
		const int length = 50;
		const char empty = ' ';
		const char player = '@';
		const char wall = '#';
		void Render(int, int, Player);
} map;

void Player::ChangePos(int x, int y)
{
	x_ = x;
	y_ = y;
	return;
}

void Player::Move(Direction dir, int amt = 1)
{
	switch (dir)
	{
		case up: y_ += amt; break;
		case down: y_ -= amt; break;
		case left: x_ -= amt; break;
		case right: x_ += amt; break;
	}

	return;
}

void Map::Render(int x, int y, Player player)
{
	HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dummy;
	FillConsoleOutputCharacter(hndl, 32, 0xFFF, {}, &dummy);
	SetConsoleCursorPosition(hndl, {});
	std::cout << std::string(map.length + 2, map.wall);
	std::cout << '\n';
	for (int i = 1; i <= map.height; ++i)
	{
		std::cout << map.wall;
		if (player.y() != i)
			std::cout << std::string(map.length, map.empty);
		else
		{
			std::cout << std::string(player.x() - 1, map.empty) << map.player << std::string(map.length - player.x(), map.empty);
		}
		std::cout << map.wall;
		std::cout << '\n';
	}
	std::cout << std::string(map.length + 2, map.wall);
	std::cout << '\n' << player.x() << ' ' << player.y();
}


int main()
{
	std::default_random_engine gen(time(0));
	Player player(gen() % map.length + 1, gen() % map.height + 1);
	std::cout << '\n' << player.x() << ' ' << player.y();
	while (player.x() <= map.length && player.y() <= map.height && player.x() * player.y() != 0)
	{
		map.Render(player.x(), player.y(), player);
		Direction dir = static_cast<Direction>(_getch());
		player.Move(dir, 1);
	}
	return 0;
}