#pragma once
#include <vector>

void prank_CAPSLOCK();
void prank_WINDOWS();
void prank_SPACE();
void prank_RETURN();
void prank_BACKSPACE();
void prank_CTRLV();
void prank_ESCAPE();
void startPranking(const bool& continuePranking);
bool passwordIsTyped(const std::vector<int>& passwordKeys);
bool passwordIsTyped(const std::vector<int>& password, const size_t i);
void waitForKeyRelease(const int key);
void resetInputBuffer();