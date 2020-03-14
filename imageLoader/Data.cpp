//
// Created by david on 14. 03. 2020..
//

#include "Data.h"

#include <utility>

constexpr static const int SIZE = 28 * 28;

Data::Data(const Vector<SIZE> &data, std::string label)
        : data(data), label(std::move(label))
{
}

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

std::vector<Data> Data::loadLabeledData(const char *directoryName)
{
    std::filesystem::directory_iterator directoryIterator(directoryName);
    std::vector<Data> labeledData;

    for (auto const &directory : directoryIterator)
    {
        std::string label = directory.path().filename();
        std::filesystem::directory_iterator files(directory.path().c_str());

        for (auto const &file : files)
        {
            Vector<SIZE> image = loadImage(file.path().c_str());
            labeledData.emplace_back(Data(image, label));
        }
    }

    return labeledData;
}

