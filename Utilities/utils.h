#pragma once
#include <string>
#include <Windows.h>

void consoleBundle();
void preventConsoleResize();
void hideCursor();
void disableQuickEdit();
void hideScrollingBar();

void pressKey(INPUT& input);
void humanType(const std::string& toWrite);
void copyToClipBoard(const std::string &dataToCopy);

void leftClickDown();
void leftClickUp();
void e_click(const int& holdTime = 30);