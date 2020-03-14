//
// Created by david on 14. 03. 2020..
//

#ifndef NEURALNETWORK_DATA_H
#define NEURALNETWORK_DATA_H


#include "../math/Vector.h"

class Data
{
private:
    constexpr static const int SIZE = 28 * 28;

    static Vector<SIZE> loadImage(const char* filename);

public:

};


#endif //NEURALNETWORK_DATA_H
