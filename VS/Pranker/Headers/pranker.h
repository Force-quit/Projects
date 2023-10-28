#pragma once
#include <vector>

void startPranking(const bool& continuePranking);
bool passwordIsTyped(const std::vector<int>& passwordKeys);
bool passwordIsTyped(const std::vector<int>& password, const size_t i);
void waitForKeyRelease(const int key);
void resetInputBuffer();