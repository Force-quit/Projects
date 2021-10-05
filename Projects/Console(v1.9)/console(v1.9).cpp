#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include "console(v1.9).h"

using namespace std;

#undef clrscr

static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
static CONSOLE_SCREEN_BUFFER_INFO csbi;

void clreol()
{
	DWORD length, dummy;	
	GetConsoleScreenBufferInfo(h, &csbi);
	length = csbi.srWindow.Right - csbi.dwCursorPosition.X;
	FillConsoleOutputCharacter(h, ' ', length, csbi.dwCursorPosition, &dummy);
}

void clreoscr()
{
	DWORD length = 0xFFFFFFFF, dummy;
	GetConsoleScreenBufferInfo(h, &csbi);
	FillConsoleOutputCharacter(h, ' ', length, csbi.dwCursorPosition, &dummy);
}

void clrscr()
{
	COORD home = {0,0};
	DWORD length = 0xFFFFFFFF, dummy;
	FillConsoleOutputCharacter(h, ' ', length, home, &dummy);
	SetConsoleCursorPosition(h, home);
}

int wherex() { GetConsoleScreenBufferInfo(h, &csbi); return csbi.dwCursorPosition.X; }
int wherey() { GetConsoleScreenBufferInfo(h, &csbi); return csbi.dwCursorPosition.Y; }

void gotoxy(int x, int y)
{	
	COORD dwCursorPosition = { short(x), short(y) };
	SetConsoleCursorPosition(h, dwCursorPosition);
}

/**************************************************************************************/

Console::Console()
{
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
}

void Console::get_csbi() { GetConsoleScreenBufferInfoEx(h, &csbi); }
bool Console::set_csbi() { return SetConsoleScreenBufferInfoEx(h, &csbi); }

void Console::set_wRect(SMALL_RECT rect) { SetConsoleWindowInfo(h, TRUE, &rect); };


unsigned short Console::get_bLines()  { get_csbi(); return csbi.dwSize.Y; }
unsigned short Console::get_bColumn() { get_csbi(); return csbi.dwSize.X; }

unsigned short Console::get_wLines()  { get_csbi(); return csbi.srWindow.Bottom - csbi.srWindow.Top + 1; }
unsigned short Console::get_wColumn() { get_csbi(); return csbi.srWindow.Right - csbi.srWindow.Left + 1; }

unsigned short Console::get_wMaxLines()  { COORD largestSize = GetLargestConsoleWindowSize(h); return largestSize.Y; }
unsigned short Console::get_wMaxColumn() { COORD largestSize = GetLargestConsoleWindowSize(h); return largestSize.X; }

int Console::get_wPosX() { RECT rect; GetWindowRect(GetConsoleWindow(), &rect); return rect.left; }
int Console::get_wPosY() { RECT rect; GetWindowRect(GetConsoleWindow(), &rect); return rect.top; }


bool Console::set_bLines(unsigned short lines)
{
	get_csbi();
	if (lines < get_wLines()) return false; // redimensionner la fenêtre avant
	csbi.dwSize.Y = lines;
	csbi.srWindow.Bottom += 1; // bug the windows ???  
	return set_csbi();
}

bool Console::set_bColumn(unsigned short column)
{
	get_csbi();
	if (column < get_wColumn())	return false; // redimensionner la fenêtre avant
	csbi.dwSize.X = column;
	csbi.srWindow.Bottom += 1; // bug the windows ???  
	return set_csbi();
}

bool Console::set_wSize(unsigned short column, unsigned short lines)
{
	if ((column == 0) || (lines == 0)) return false; // Deuhh ...

	COORD largestSize = GetLargestConsoleWindowSize(h);
	if ((column > largestSize.X) || (lines > largestSize.Y)) return false; // Rentre pas dans l'écran...

	get_csbi();

	if (lines > csbi.dwSize.Y) set_bLines(lines);
	if (column > csbi.dwSize.X) set_bColumn(column);

	set_wRect({ 0, 0, column - 1, lines - 1 });
	set_bColumn(column);
	return true;
}

bool Console::set_wPos(int x, int y)
{
	HWND consoleWindow = GetConsoleWindow();
	return SetWindowPos(consoleWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}


bool Console::set_wFullscreen()
{
	set_wSize(get_wMaxColumn(), get_wMaxLines());
	return set_wPos(-8 , 0);
}

/**************************************************************************************/

void cvmSetColor(cvmColor c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(c));
}

void cvmResetColor() { cvmSetColor(cvmColor::BLANC); }


// Le deuxième argument est le temps de défilement des lettres en milliseconde.
// Mettre 0 pour aucun défilement ralenti.

void cvmCenterTxt(string texte, unsigned int Temps, cvmColor couleur)
{
	unsigned int scrWidth = 120; // get_wColumn();
	
	cvmSetColor(couleur);
	
	if ( texte.size() <= scrWidth )
		cout << setw ( (scrWidth - texte.size() ) / 2 ) << left << "";

	for ( unsigned int i = 0 ; i < texte.size() ; i++ )	//Défiler
	{
		cout << texte[i];
		Sleep(Temps);
	}
}

// Le deuxième argument est le temps de défilement des lettres en milliseconde.

void cvmDefilTxt(string texte, unsigned int Temps, cvmColor couleur)
{
	cvmSetColor(couleur);
	for (unsigned int i(0); i<texte.size(); i++) //Défiler
	{
		cout << texte[i];
		Sleep(Temps);
	}
}