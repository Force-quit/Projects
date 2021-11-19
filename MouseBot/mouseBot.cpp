#include <iostream>
#include <Windows.h>
#include "../Projects/Utilities/utils.h"
#include "../Projects/Console(v1.9)/console(v1.9).h"

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

void playLoop(MyPoint*& firstPoint, MyPoint*& endPoint, short speed = 1, short waitTime = 5)
{
	bool stayInLoop = true;
	bool moving = true;
	bool pressedPause = false;
	bool pressedEscape = false;

	// Reset state??
	GetAsyncKeyState(VK_ESCAPE);
	GetAsyncKeyState(VK_SPACE);
	endPoint = firstPoint;
	while (stayInLoop)
	{
		if (moving)
		{
			SetCursorPos(endPoint->p.x, endPoint->p.y);
			for (int i = 0; i < speed; ++i)
			{
				endPoint = endPoint->nextPoint;
				if (endPoint == NULL)
					endPoint = firstPoint;
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

		std::cout << std::endl << "Press left shift and move your mouse; release shift when done.";

		MyPoint* firstPoint = new MyPoint{};
		MyPoint* lastPoint = firstPoint;
		MyPoint* endPoint = firstPoint;

		drawAndLoadLoop(firstPoint, lastPoint, endPoint);

		std::cout << std::endl << "Press space to pause the loop and escape to end it.";

		playLoop(firstPoint, endPoint, speed, waitTime);

		lastPoint = firstPoint;
		while (lastPoint != NULL)
		{
			firstPoint = lastPoint->nextPoint;
			delete lastPoint;
			lastPoint = firstPoint;
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