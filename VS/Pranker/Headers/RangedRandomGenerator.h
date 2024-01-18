#pragma once
#include <random>

template <typename T>
class RangedRandomGenerator
{
private:
    inline static std::random_device rd;
    inline static std::mt19937 gen;

    std::uniform_int_distribution<T> distribution;

public:
    RangedRandomGenerator(T min, T inclusiveMax)
        : distribution(min, inclusiveMax)
    {
    }

    T random()
    {
        return distribution(gen);
    }
};

