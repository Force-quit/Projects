#pragma once
#include <string>
#include <Windows.h>
#include <vector>

// Resets std::cin
void e_flushTampon();

void e_consoleBundle();
void e_preventConsoleResize();
void e_hideCursor();
void e_disableQuickEdit();
void e_hideScrollingBar();

std::string e_passwordGenerator(const std::string& alphabet, const unsigned short& passwordLength);

// Simulate a key press
void e_pressKey(const unsigned char& key);

// Simulate a key release
void e_releaseKey(const unsigned char& key);

// Simulate a key press and release
void e_pressKey(const INPUT& input);

// Simulate the typing of a string
void e_humanType(const std::string& toWrite);

// Copy a string into windows's clipboard
void e_copyToClipBoard(const std::string &dataToCopy);

// Simulate a left mouse button down
void e_leftClickDown();

// Simulate a left mouse button up
void e_leftClickUp();

// Simulate a left click
void e_leftClick(const int& holdTime = 30);
