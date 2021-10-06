#pragma once
#include <string>
#include <Windows.h>

void e_consoleBundle();
void e_preventConsoleResize();
void e_hideCursor();
void e_disableQuickEdit();
void e_hideScrollingBar();

void e_pressKey(INPUT& input);
void e_humanType(const std::string& toWrite);
void e_copyToClipBoard(const std::string &dataToCopy);

void e_leftClickDown();
void e_leftClickUp();
void e_click(const int& holdTime = 30);