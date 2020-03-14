//
// Created by david on 14. 03. 2020..
//

#ifndef NEURALNETWORK_DATA_H
#define NEURALNETWORK_DATA_H

#include <filesystem>
#include <vector>
#include <ostream>
#include <string>

#include "stb_image.h"
#include "../math/Vector.h"

class Data
{
private:
    constexpr static const int SIZE = 28 * 28;

    Vector<SIZE> data;
    std::string label;

    static Vector<SIZE> loadImage(const char *filename);

public:
    Data(const Vector<SIZE> &data, std::string label);

    static std::vector<Data> loadLabeledData(const char *directoryName);

    [[nodiscard]] const Vector<SIZE> &getData() const;

    [[nodiscard]] const std::string &getLabel() const;
};


#endif //NEURALNETWORK_DATA_H