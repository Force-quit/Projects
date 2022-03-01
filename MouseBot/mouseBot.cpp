#include "../Utilities/utils.h"
#include "../Console(v1.9)/console(v1.9).h"
#include <iostream>
#include <Windows.h>

struct MyPoint
{
	POINT p;
	MyPoint* nextPoint;
};

void drawAndLoadLoop(MyPoint* &firstPoint, MyPoint*& lastPoint, MyPoint*& endPoint)
{
	POINT p;
	bool startedLoop = false;
	GetAsyncKeyState(VK_LSHIFT);
	while (true)
	{
		if (GetAsyncKeyState(VK_LSHIFT))
		{
			if (!startedLoop)
			{
				startedLoop = true;

				GetCursorPos(&(firstPoint->p));
			}
			else
			{
				GetCursorPos(&p);
				if (p.x != lastPoint->p.x || p.y != lastPoint->p.y)
				{
					endPoint->nextPoint = new MyPoint{};
					lastPoint = endPoint;
					endPoint = endPoint->nextPoint;
					endPoint->p = p;
				}
			}
		}
		else if (startedLoop)
			break;
		Sleep(5);
	}
}

void playLoop(const MyPoint * const firstPoint, const MyPoint* currentPoint, short speed = 1, short waitTime = 5)
{
	bool stayInLoop = true;
	bool moving = true;
	bool pressedPause = false;
	bool pressedEscape = false;

	GetAsyncKeyState(VK_ESCAPE);
	GetAsyncKeyState(VK_SPACE);
	currentPoint = firstPoint;
	while (stayInLoop)
	{
		if (moving)
		{
			SetCursorPos(currentPoint->p.x, currentPoint->p.y);
			for (int i = 0; i < speed; ++i)
			{
				currentPoint = currentPoint->nextPoint;
				if (currentPoint == NULL)
					currentPoint = firstPoint;
			}
		}

		if (GetAsyncKeyState(VK_SPACE))
		{
			if (!pressedPause)
			{
				pressedPause = true;
				moving = !moving;
			}
		}
		else
			pressedPause = false;

		if (GetAsyncKeyState(VK_ESCAPE))
			pressedEscape = true;
		else if (pressedEscape)
			stayInLoop = false;


		Sleep(waitTime);
	}
}

int main()
{
	SetConsoleTitleA("Mouse bot");
	cvmCenterTxt("!AWESOME MOUSE BOT!");
	std::cout << std::endl;
	char redo;
	do
	{
		std::cout << std::endl << "Press left shift and move your mouse; release shift when done.\n";

		MyPoint* firstPoint = new MyPoint{};
		MyPoint* currentPoint = firstPoint;
		MyPoint* lastPoint = firstPoint;

		drawAndLoadLoop(firstPoint, currentPoint, lastPoint);

		short speed;
		do
		{
			std::cout << "Speed of cursor: ";
			emile::flushTampon();
			std::cin >> speed;
		} while (std::cin.fail() || speed < 1);

		short waitTime;
		do
		{
			std::cout << "Wait time (ms) between cursor move: ";
			emile::flushTampon();
			std::cin >> waitTime;
		} while (std::cin.fail() || waitTime < 1);

		std::cout << std::endl << "Press space to pause the loop and escape to end it.";

		playLoop(firstPoint, currentPoint, speed, waitTime);

		currentPoint = firstPoint;
		while (currentPoint != NULL)
		{
			firstPoint = currentPoint->nextPoint;
			delete currentPoint;
			currentPoint = firstPoint;
		}

		std::cout << "\n\n";
		do
		{
			std::cout << "Do you want to do another loop? Y/N: ";
			emile::flushTampon();
			std::cin >> redo;
			redo = toupper(redo);
		} while (redo != 'N' && redo != 'Y');
	} while (redo == 'Y');
	
	return 0;
}