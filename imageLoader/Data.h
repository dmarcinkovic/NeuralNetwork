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

/**
 *
 * Class that represents training and testing data.
 *
 * @author David
 *
 * @tparam SIZE
 */
template<int SIZE>
class Data
{
private:
    Vector<SIZE> m_Data;
    std::string m_Label;

    /**
     * Method used to shuffle data.
     *
     * @param data Data to be shuffled.
     */
    static void shuffleData(std::vector<Data> &data)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::shuffle(data.begin(), data.end(), std::default_random_engine(seed));
    }

    /**
     * Method loads image given as array of bytes to a vector of integers.
     *
     * @param image Image represented as array of bytes to be loaded in vector.
     * @param width Width of the image.
     * @param height Height of the image.
     * @return  Vector of pixels.
     */
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

    /**
     * Constructor.
     *
     * @param data Image pixels represented as vector.
     * @param label Label
     */
    Data(Vector<SIZE> data, std::string label)
            : m_Data(std::move(data)), m_Label(std::move(label))
    {}

    /**
     * Getter for data.
     *
     * @return Data.
     */
    const Vector<SIZE> &getData() const
    {
        return m_Data;
    }

    /**
     * Getter for label.
     *
     * @return  Label
     */
    [[nodiscard]] const std::string &getLabel() const
    {
        return m_Label;
    }

    /**
     * Method loads image from disk and returns vector of size equal to imageWidth * imageHeight,
     * where each element in vector is represented with double value in range [0, 1]. Value 0 corresponds
     * to black pixel, while value 1 corresponds to white pixel. If the image does not exists on disk, or
     * current user does not have permission to read given image, this method will throw an exception.
     *
     * @param filename Relative or absolute path to the image.
     * @param desiredImageWidth Desired image width. If the image does not have width equal to desired
     * width it will be resized to desired width.
     * @param desiredImageHeight Desired image height. If the image does not have height equal to desired
     * height it will be resized to desired height.
     * @return Vector of pixels. Explained below.
     */
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

    /**
     * Used to load labeled from the given directory.
     * Directory should be in the form: <br>
     * .<br>
     * |__ label1 <br>
     * |__ label2 <br>
     * |__ label3<br>
     * |__ label4<br>
     * ... <br>
     * where label1, label2, label3 and label4 are directories that contain images
     * with labels label1, label2, label3 and label4, respectively.
     *
     * @param directoryName Directory with images.
     * @param desiredImageWidth Desired width of every image in the given directory. If some
     * image does not have width equal to desired width, it will be resized to desired width.
     * @param desiredImageHeight Desired height of every image in the given directory. If some
     * image does not have height equal to desired height, it will be resize to desired height.
     * @return Vector of labeled data.
     */
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

    /**
     * Loads all images in the given directory to vector of labeled data.
     *
     * @param directory Directory that contains images to be loaded.
     * @param desiredImageWidth Desired width of every image in the given directory. If some
     * image does not have width equal to desired width, it will be resized to desired width.
     * @param desiredImageHeight Desired height of every image in the given directory. If some
     * image does not have height equal to desired height, it will be resize to desired height.
     * @return Vector of labeled data.
     */
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
