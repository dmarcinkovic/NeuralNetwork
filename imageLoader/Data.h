//
// Created by david on 14. 03. 2020..
//

#ifndef NEURALNETWORK_DATA_H
#define NEURALNETWORK_DATA_H

#include <filesystem>
#include <vector>
#include <string>
#include <chrono>
#include <random>

#include "stb_image.h"
#include "../math/Vector.h"

class Data
{
private:
    constexpr static const int SIZE = 28 * 28;
    constexpr static const int N = 10;

    Vector<SIZE> data;
    std::string label;

    static Vector<SIZE> loadImage(const char *filename);

    static void shuffleData(std::vector<Data> &data);

public:
    Data(const Vector<SIZE> &data, std::string label);

    static std::vector<Data> loadLabeledData(const char *directoryName);

    [[nodiscard]] const Vector<SIZE> &getData() const;

    [[nodiscard]] const std::string &getLabel() const;

    static Vector<N> getAnswerData(const std::string &label);
};


#endif //NEURALNETWORK_DATA_H
