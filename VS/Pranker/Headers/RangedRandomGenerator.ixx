module;

#include <random>
#include <concepts>

export module Pranker:RangedRandomGenerator;

export template <typename T> requires std::is_arithmetic_v<T>
class RangedRandomGenerator
{
private:
    inline static std::random_device rd;
    inline static std::mt19937 sGen;

    std::uniform_int_distribution<T> mDistribution;

public:
    RangedRandomGenerator(T iMin, T iInclusiveMax)
        : mDistribution(iMin, iInclusiveMax)
    {
    }

    T random()
    {
        return mDistribution(sGen);
    }
};