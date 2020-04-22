//
// Created by david on 14. 03. 2020..
//

#include "Data.h"

#include <utility>

constexpr static const int SIZE = 28 * 28;
constexpr static const int N = 10;

Data::Data(Vector<SIZE> data, std::string label)
        : data(std::move(data)), label(std::move(label))
{
}

Vector<SIZE> Data::loadImage(const char *filename)
{
    Vector<SIZE> data{};

    int width, height, BPP;
    std::uint8_t *localBuffer = stbi_load(filename, &width, &height, &BPP, 3);

    if (localBuffer == nullptr)
    {
        throw std::invalid_argument("Cannot load image " + std::string(filename));
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int index = i * width + j;
            double color = (localBuffer[3 * index] + localBuffer[3 * index + 1] + localBuffer[3 * index + 2]) / 3.0;
            data[index] = color / 255.0;
        }
    }

    stbi_image_free(localBuffer);

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

    shuffleData(labeledData);
    return labeledData;
}

const Vector<SIZE> &Data::getData() const
{
    return data;
}

const std::string &Data::getLabel() const
{
    return label;
}

void Data::shuffleData(std::vector<Data> &data)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(data.begin(), data.end(), std::default_random_engine(seed));
}

Vector<N> Data::getAnswerData(const std::string &label)
{
    int number = std::stoi(label);

    Vector<N> answer{};

    answer[number] = 1;
    return answer;
}

std::vector<std::pair<Vector<SIZE>, std::string>> Data::loadImagesFromDirectory(const char *directory)
{
    std::vector<std::pair<Vector<SIZE>, std::string>> result;

    std::filesystem::directory_iterator directoryIterator(directory);

    for (auto const& image : directoryIterator)
    {
        result.emplace_back(loadImage(image.path().c_str()), image.path().filename());
    }

    return result;
}
