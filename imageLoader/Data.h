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
#include "stb_image_resize.h"

template<int SIZE>
class Data
{
private:
    Vector<SIZE> m_Data;
    std::string m_Label;

    static void shuffleData(std::vector<Data> &data)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::shuffle(data.begin(), data.end(), std::default_random_engine(seed));
    }

    static inline Vector<SIZE> loadImageInVector(const std::uint8_t *image, int width, int height)
    {
        Vector<SIZE> data{};

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                int index = i * width + j;
                double color = (image[3 * index] + image[3 * index + 1] + image[3 * index + 2]) / 3.0;
                data[index] = color / 255.0;
            }
        }

        return data;
    }

public:
    Data(Vector<SIZE> data, std::string label)
            : m_Data(std::move(data)), m_Label(std::move(label))
    {}

    const Vector<SIZE> &getData() const
    {
        return m_Data;
    }

    [[nodiscard]] const std::string &getLabel() const
    {
        return m_Label;
    }

    static Vector<SIZE> loadImage(const char *filename, int desiredImageWidth, int desiredImageHeight)
    {
        constexpr int numberOfChannels = 3;
        int width, height, BPP;
        std::uint8_t *localBuffer = stbi_load(filename, &width, &height, &BPP, numberOfChannels);

        if (localBuffer == nullptr)
        {
            throw std::invalid_argument("Cannot load image " + std::string(filename));
        }

        Vector<SIZE> data{};

        std::uint8_t *resizedImage;
        if (width != desiredImageWidth || height != desiredImageHeight)
        {
            resizedImage = new std::uint8_t[numberOfChannels * desiredImageHeight * desiredImageWidth];
            stbir_resize_uint8(localBuffer, width, height, 0, resizedImage, desiredImageWidth, desiredImageHeight, 0,
                               numberOfChannels);

            data = loadImageInVector(resizedImage, desiredImageWidth, desiredImageHeight);

            delete[] resizedImage;
        } else
        {
            data = loadImageInVector(localBuffer, width, height);
        }

        stbi_image_free(localBuffer);

        return data;
    }

    static std::vector<Data> loadLabeledData(const char *directoryName, int desiredImageWidth, int desiredImageHeight)
    {
        std::filesystem::directory_iterator directoryIterator(directoryName);
        std::vector<Data> labeledData;

        for (auto const &directory : directoryIterator)
        {
            std::string label = directory.path().filename();
            std::filesystem::directory_iterator files(directory.path().c_str());

            for (auto const &file : files)
            {
                Vector<SIZE> image = loadImage(file.path().c_str(), desiredImageWidth, desiredImageHeight);
                labeledData.emplace_back(Data(image, label));
            }
        }

        shuffleData(labeledData);
        return labeledData;
    }

    static std::vector<Data>
    loadImagesFromDirectory(const char *directory, int desiredImageWidth, int desiredImageHeight)
    {
        std::vector<Data> result;
        std::filesystem::directory_iterator directoryIterator(directory);

        for (auto const &image : directoryIterator)
        {
            result.emplace_back(loadImage(image.path().c_str(), desiredImageWidth, desiredImageHeight),
                                image.path().filename());
        }

        return result;
    }
};


#endif //NEURALNETWORK_DATA_H
