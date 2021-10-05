#pragma once
#include <Windows.h>
#include <vector>
#include <string>

void consoleBundle();
void preventConsoleResize();
void hideCursor();
void disableQuickEdit();
void hideScrollingBar();
void pressKey(INPUT& input);
void humanType(std::vector<UINT16> keys);
void copyToClipBoard(const std::string &dataToCopy);