//
// Created by david on 07. 03. 2020..
//

#ifndef NEURALNETWORK_UTIL_H
#define NEURALNETWORK_UTIL_H

#include <functional>
#include <random>

class Util
{
public:
    static double getRandomUniformDistribution(double rangeStart, double rangeEnd);

    static double getRandomNormalDistribution(double mean, double deviation);

    static double getNormalXavierDeviation(int inputs, int outputs);

    static std::function<double(double)> getSigmoid();

    static std::function<double(double)> getSigmoidDerivation();

    static std::function<double(double, double)> subtract();

    static std::function<double(double, double)> add();

    static std::function<double(double, double)> multiply();
};


#endif //NEURALNETWORK_UTIL_H
