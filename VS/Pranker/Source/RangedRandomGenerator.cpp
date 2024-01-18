#include "../Headers/RangedRandomGenerator.h"

std::random_device RangedRandomGenerator::rd;
std::mt19937 RangedRandomGenerator::gen(RangedRandomGenerator::rd());

RangedRandomGenerator::RangedRandomGenerator(size_t min, size_t inclusiveMax)
	: distribution(min, inclusiveMax)
{
}

size_t RangedRandomGenerator::random()
{
	return distribution(gen);
}
