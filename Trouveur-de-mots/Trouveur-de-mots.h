#pragma once
#include <vector>
#include <string>
#include <unordered_map>

void mainLoop(const std::vector<std::string>& wordList, const unsigned short& MAX_FINDS);
void findWords(const std::vector<std::string>& wordList, const std::string& subStr, const unsigned short& MAX_RESULTS, std::unordered_map<unsigned short, std::string>& foundWords);