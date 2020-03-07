//
// Created by david on 07. 03. 2020..
//

#include "Random.h"

#include <random>

double Random::getRandomNumber(double rangeStart, double rangeEnd)
{
    std::random_device device;
    std::mt19937_64 mt(device());
    std::uniform_real_distribution<double> distribution(rangeStart, rangeEnd);

    return distribution(mt);
}
