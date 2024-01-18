#pragma once
#include <random>

class RangedRandomGenerator
{
private:
    static std::random_device rd;
    static std::mt19937 gen;

    std::uniform_int_distribution<size_t> distribution;

public:
    RangedRandomGenerator(size_t min, size_t inclusiveMax);
    size_t random();
};

