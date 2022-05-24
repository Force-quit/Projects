#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <Windows.h>
#include <WinUser.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/utils/logger.hpp>

using namespace cv;
using namespace std;
using namespace std::chrono;

/*
Searches for an open Notepad.exe instance and creates one if
none is found, then change its title to the parameter given
and returns the handle to the edit window.
*/
HWND GetNotePad(const string);

/*
Builds a string that can be sent to other functions with the
ascii character that most closely matches the brightness for
each pixel in a given matrix. The first parameter is a matrix
of colors that represents an image; the second parameter is a
boolean that controls whether to use 70 different characters
in the string for more possible colors instead of 10 for
sharper outputs.
*/
string GetText(Mat, const bool);

/*
Sends a string to the edit window of a Notepad.exe instance.
The first parameter is a handle to the edit window; the
second parameter is the string to be sent.
*/
void SendToNotePad (HWND, const string);


int main (int argc, char* argv[])
{	
	utils::logging::setLogLevel(utils::logging::LogLevel::LOG_LEVEL_SILENT);	//Remove logs from console
	SetWindowTextA(GetConsoleWindow(), "Notepad player by Grainus");

	string inputPath;
	bool HD, lowFPS;
	double ratio;
	const HANDLE consHndl = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dummy;

	bool first = true;
	bool openVideo = false;
	do
	{
		//Check if an argument was passed directly to the application
		//by dropping a file onto it
		if (argc > 1 && first)
		{
			VideoCapture video(argv[1]);
			if (video.isOpened())
			{
				inputPath = argv[1];
				break;
			}

			first = false;
		}
		else
		{
			cout << "Directory: ";
			cin >> inputPath;
		}

		VideoCapture video(inputPath);
		if (video.isOpened())
			openVideo = true;
		else
		{
			FillConsoleOutputCharacter(consHndl, 32, 0xFFFF, {}, &dummy);
			SetConsoleCursorPosition(consHndl, {});
			cout << "Could not open the file.\n";
		}
	} while (!openVideo);

	string title = "Playing - " + inputPath.substr(inputPath.find_last_of("/\\") + 1);

	cout << "(Y/N) Use more ascii (might be more blurry): ";
	{
		string temp;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(consHndl, &csbi);
		COORD coords = { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };
		do
		{
			FillConsoleOutputCharacter(consHndl, 32, 0xFFFF, coords, &dummy);
			SetConsoleCursorPosition(consHndl, coords);

			cin >> temp;
			if (temp.size() > 1)
				continue;

			temp = toupper(temp[0]);
		} while (temp != "Y" && temp != "N");

		if (temp == "Y") HD = 1;
			else HD = 0;
	}
	

	cout << "(Y/N) Use half FPS to make the screen flicker less?: ";
	{
		string temp;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(consHndl, &csbi);
		COORD coords = { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };
		do
		{
			FillConsoleOutputCharacter(consHndl, 32, 0xFFFF, coords, &dummy);
			SetConsoleCursorPosition(consHndl, coords);

			cin >> temp;
			if (temp.size() > 1)
				continue;

			temp = toupper(temp[0]);
		} while (temp != "Y" && temp != "N");

		if (temp == "Y") lowFPS = 1;
			else lowFPS = 0;
	}


	cout << "Ratio of the resolution in characters over the original resolution: ";
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(consHndl, &csbi);
		COORD coords = { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };
		bool first = true;
		do
		{
			if (!first)
			{
				cin.clear();
				cin.ignore('\n');
			}
			else first = false;
		
			FillConsoleOutputCharacter(consHndl, 32, 0xFFFF, coords, &dummy);
			SetConsoleCursorPosition(consHndl, coords);

			cin >> ratio;
		} while (cin.fail());
	}
	if (ratio > 1)
		ratio /= 100;

	//Clear the screen
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), 32, 0xFFFF, {}, &dummy);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });

	HWND hwnd = GetNotePad(title);


	for (int i = 2; i > 0; --i)
	{
		SendToNotePad(hwnd, to_string(i));
		Sleep(1000);
	}
	
	VideoCapture video(inputPath, CAP_FFMPEG);
	Mat frame;

	int iter = 0;

	auto begin = high_resolution_clock::now();

	while (video.read(frame))
	{
		auto beginframe = high_resolution_clock::now();
		if (!lowFPS || iter % 2 == 0)
		{
			cvtColor(frame, frame, COLOR_BGR2GRAY);		//convert image to grayscale

			resize(frame, frame, Size(), ratio, ratio / 2, INTER_AREA);	//Resize the image

			string text = GetText(frame, HD);
			SendToNotePad(hwnd, text);
		}
		cout << iter++ << ' ';

		//Adjusts the video framerate, speeds up to catch up on lag
		{
			auto endframe = high_resolution_clock::now();
			double framerate = 1.0 / video.get(CAP_PROP_FPS) - (endframe - begin).count() / 1e9 / iter;
			auto spinStart = high_resolution_clock::now();
			while ((high_resolution_clock::now() - spinStart).count() / 1e9 / iter < framerate);
		}
	}
	return 0;
}


HWND GetNotePad(const string title)
{
	HWND editHwnd = 0;
	HWND mainHwnd;
	//ShellExecuteA(0, "open", "notepad.exe", NULL, NULL, 0);	//creates hidden window for testing
	while (1) {
		mainHwnd = FindWindowA("Notepad", NULL);
		if (mainHwnd != NULL)
		{
			cout << "Found open notepad window...\n";
			if (IsWindowVisible(mainHwnd))
			{
				cout << "Checking if the window is valid...\n";
				char* title = new char[11];
				GetWindowTextA(mainHwnd, title, 11);
				editHwnd = FindWindowEx(mainHwnd, NULL, L"Edit", NULL);
				if (string(title) == "Playing - ")
				{
					delete[] title;
					cout << "Window was created by this program, reusing it...\n";
					break;
				}
				else if (GetWindowTextLength(editHwnd) == 0)
				{
					delete[] title;
					cout << "Window is empty, using it...\n";
					break;
				}
				else
				{
					delete[] title;
					cout << "Window is invalid, opening a new notepad window...\n";
					break;
				}
			}
			else
			{
				cout << "Hidden window found, terminating it...\n";
				SendMessage(mainHwnd, WM_CLOSE, NULL, NULL);
				continue;
			}
		}
		else
		{
			cout << "No valid window found, creating a new one...\n";
			break;
		}
	}

	if (editHwnd == 0)
	{

		STARTUPINFOW startupInfo;
		PROCESS_INFORMATION procInfo;

		ZeroMemory(&startupInfo, sizeof(startupInfo));
		ZeroMemory(&procInfo, sizeof(procInfo));

		wchar_t NOTEPATH[] = L"C:/Windows/System32/Notepad.exe";

		CreateProcess(NOTEPATH,
			NULL,
			NULL,
			NULL,
			FALSE,
			NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
			NULL,
			NULL,
			&startupInfo,
			&procInfo
		);

		WaitForInputIdle(procInfo.hProcess, 20000);

		mainHwnd = FindWindowW(L"Notepad", NULL);				//The newly created window should be top level
		editHwnd = FindWindowEx(mainHwnd, NULL, L"Edit", NULL);

		CloseHandle(procInfo.hProcess);
		CloseHandle(procInfo.hThread);
	}

	SetWindowTextA(mainHwnd, title.c_str());
	return editHwnd;
}


void SendToNotePad (HWND hwnd, const string msg)
{
	int wchars_num = MultiByteToWideChar(CP_UTF8, 0, msg.c_str(), -1, NULL, 0);
	wchar_t* wstr = new wchar_t[wchars_num];
	MultiByteToWideChar(CP_UTF8, 0, msg.c_str(), -1, wstr, wchars_num);

	SendMessage(hwnd, WM_SETTEXT, NULL, (LPARAM)wstr);

	delete[] wstr;
	return;
}


string GetText(Mat image, const bool FULL)
{
	string text = "";
	const int valuesFull = 71;
	const char asciiFull[valuesFull] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B$@";
	const int valuesSmall = 11;
	char asciiSmall[valuesSmall] = " .:-=+*#%@";
	int a;

	for (int y = 0; y < image.rows; ++y)
	{
		for (int x = 0; x < image.cols; ++x)
		{
			//Mat.at() uses uchar here because it's always grayscale
			a = (255 - image.at<uchar>(y, x)) * ((FULL == 1 ? valuesFull : valuesSmall) - 1) / 256;
			text += (FULL == 1 ? asciiFull : asciiSmall)[a];
		}
		text += '\n';
	}
	return text;
}