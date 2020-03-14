//
// Created by david on 14. 03. 2020..
//

#ifndef NEURALNETWORK_DATA_H
#define NEURALNETWORK_DATA_H

#include <filesystem>

#include "stb_image.h"
#include "../math/Vector.h"

class Data
{
private:
    constexpr static const int SIZE = 28 * 28;

    Vector<SIZE> data;
    const char* label;

    static Vector<SIZE> loadImage(const char* filename);

public:

    static std::pair<Vector<SIZE>, const char*> loadLabeledData(const char* directory);

};


#endif //NEURALNETWORK_DATA_H
