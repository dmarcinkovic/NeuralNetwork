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

    /**
     * Returns random number in given range using uniform distribution.
     *
     * @param rangeStart Start of desired range.
     * @param rangeEnd  End of desired range.
     * @return  Random number in desired range.
     */
    static double getRandomUniformDistribution(double rangeStart, double rangeEnd);

    /**
     * Returns random number using normal distribution.
     *
     * @param mean Mean value of normal distribution.
     * @param deviation Standard value of normal distribution.
     * @return Random number using normal distribution.
     */
    static double getRandomNormalDistribution(double mean, double deviation);

    /**
     * Return normal Xavier deviation for given input and output number of nodes.
     *
     * @param inputs Number of incoming connections to given layer of neural network.
     * @param outputs Number of links coming out of given layer of neural network.
     * @return Normal Xavier deviation.
     */
    static double getNormalXavierDeviation(int inputs, int outputs);

    /**
     * Returns sigmoid function.
     *
     * @return Sigmoid function.
     */
    static std::function<double(double)> getSigmoid();

    /**
     * Returns derivation of sigmoid function.
     *
     * @return Sigmoid derivation.
     */
    static std::function<double(double)> getSigmoidDerivation();
};


#endif //NEURALNETWORK_UTIL_H
