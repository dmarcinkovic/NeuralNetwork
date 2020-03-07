//
// Created by david on 07. 03. 2020..
//

#include "Util.h"

double Util::getRandomNumber(double rangeStart, double rangeEnd)
{
    std::random_device device;
    std::mt19937_64 mt(device());
    std::uniform_real_distribution<double> distribution(rangeStart, rangeEnd);

    return distribution(mt);
}

std::function<double(double)> Util::getSigmoid()
{
    return [](double x) {
        return 1.0 / (1.0 + std::exp(-x));
    };
}

std::function<double(double, double)> Util::subtract()
{
    return [](double a, double b) {
        return a - b;
    };
}

std::function<double(double, double)> Util::add()
{
    return [](double a, double b) {
        return a + b;
    };
}

std::function<double(double, double)> Util::multiply()
{
    return [](double a, double b) {
        return a * b;
    };
}
