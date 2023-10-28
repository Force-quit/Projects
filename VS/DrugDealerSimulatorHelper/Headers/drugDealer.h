#pragma once
#include <map>
#include <string>
#include <vector>

void listDrugs(const std::map<short, std::string>& drugTypes);
unsigned short getDrugType(const std::map<short, std::string>& drugTypes);
short getTotalFromList(std::string& list, std::vector<short>& typeOfDrugNeeded);
void takeOrders(const std::map<short, std::string>& drugTypes, std::map<short, std::vector<short>>& drugsNeeded);
void printTotals(const std::map<short, std::string>& drugTypes, const std::map<short, std::vector<short>>& drugsNeeded);
void printTotalBags(const std::map<short, std::string>& drugTypes, std::map<short, std::vector<short>>& drugsNeeded);
