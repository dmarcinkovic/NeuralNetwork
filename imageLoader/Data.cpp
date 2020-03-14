//
// Created by david on 14. 03. 2020..
//

#include "Data.h"

constexpr static const int SIZE = 28 * 28;

Vector<SIZE> Data::loadImage(const char *filename)
{
    Vector<SIZE> data{};

    int width, height, BPP;
    std::uint8_t *localBuffer = stbi_load(filename, &width, &height, &BPP, 3);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int index = i * width + j;
            double color = (localBuffer[3 * index] + localBuffer[3 * index + 1] + localBuffer[3 * index + 2]) / 3.0;
            data[index] = color / 255.0;
        }
    }

    return data;
}