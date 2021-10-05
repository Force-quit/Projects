#pragma once

#include <Windows.h>
#include <string>

// POUR LE NETTOYAGE DE LA FENÊTRE CONSOLE

void clreol();   // efface la ligne courante à partir du curseur sans le déplacer
void clreoscr(); // efface la fenêtre à partir du curseur sans le déplacer
void clrscr();   // efface toute la fenêtre et remet le curseur au début

// POUR LE POSITIONNEMENT DU CURSEUR DE LA FENÊTRE CONSOLE

int wherex();				// retourne la colonne courante du curseur
int wherey();				// retourne la ligne courante du curseur
void gotoxy(int x,int y);	// place le curseur à la colonne x et à la ligne y  ( l'origine = gotoxy(0,0); )


// POUR GERER LES PROPRIÉTÉS DE LA FENÊTRE CONSOLE

class Console
{
	public:
		// Window
		unsigned short get_wLines();
		unsigned short get_wColumn();
		unsigned short get_wMaxLines();
		unsigned short get_wMaxColumn();

		bool set_wSize(unsigned short column, unsigned short lines);
		bool set_wFullscreen();

		// Buffer
		unsigned short get_bLines();
		unsigned short get_bColumn();
		bool set_bLines(unsigned short lines);
		bool set_bColumn(unsigned short column);

		// Windows position
		int get_wPosX();
		int get_wPosY();
		bool set_wPos(int x, int y);

		Console();

	private:
		HANDLE h;
		CONSOLE_SCREEN_BUFFER_INFOEX csbi;

		void get_csbi();
		bool set_csbi();
		void set_wRect(SMALL_RECT rect);
};

// POUR LA COLORATION DES CARACTÈRES DE LA FENÊTRE CONSOLE

enum class cvmColor // énumération des couleurs possibles
{
	NOIR  = 0x00,
	BLANC = 0x07,
	BLEU  = 0x09,
	VERT  = 0x0a,
	CYAN  = 0x0b,	
	ROUGE = 0x0c,
	ROSE  = 0x0d,
	JAUNE = 0x0e
};

void cvmSetColor(cvmColor c); // change la couleur courante
void cvmResetColor(); // change la couleur courante en BLANC


// POUR AFFICHER DU TEXTE DE LA FENÊTRE CONSOLE

void cvmCenterTxt(std::string texte, unsigned int Temps = 0, cvmColor couleur = cvmColor::BLANC);
void cvmDefilTxt(std::string texte, unsigned int Temps = 0, cvmColor couleur = cvmColor::BLANC);

//#include "tp_redirect.h"