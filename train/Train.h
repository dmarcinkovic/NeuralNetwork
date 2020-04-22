//
// Created by david on 19. 03. 2020..
//

#ifndef NEURALNETWORK_TRAIN_H
#define NEURALNETWORK_TRAIN_H

#include <vector>
#include <chrono>

#include "../imageLoader/Data.h"
#include "../neuralNetwork/NeuralNetwork.h"

class Train
{
public:
    template<int INPUT, int HIDDEN, int OUTPUT>
    static void train(const char *directoryName, NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network,
                      int desiredImageWidth, int desiredImageHeight)
    {
        std::vector<Data<INPUT>> trainData = Data<INPUT>::loadLabeledData(directoryName, desiredImageWidth,
                                                                          desiredImageHeight);

        constexpr static const int numberOfEpochs = 50;

        double totalDuration = 0;
        for (int j = 0; j < numberOfEpochs; ++j)
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (auto &i : trainData)
            {
                Vector<OUTPUT> data{};
                data[network.getLabel(i.getLabel())] = 1;

                network.train(i.getData(), data);
            }

            auto end = std::chrono::high_resolution_clock::now();
            totalDuration += std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

            std::cout << "Completed: " << static_cast<double>(j + 1) / numberOfEpochs * 100 << "%\n";
        }

        std::cout << "Time took: " << totalDuration << " s\n";
    }

    template<int INPUT, int HIDDEN, int OUTPUT>
    static void test(const char *directoryName, const NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network,
                     int desiredImageWidth, int desiredImageHeight)
    {
        std::vector<Data<INPUT>> testData = Data<INPUT>::loadLabeledData(directoryName, desiredImageWidth,
                                                                         desiredImageHeight);

        int correct = 0;
        for (auto &i : testData)
        {
            if (network.guess(i.getData()) == i.getLabel())
            {
                ++correct;
            }
        }

        std::cout << "Correct: " << static_cast<double>(correct) / testData.size() * 100 << "%\n";
    }

    template<int INPUT, int HIDDEN, int OUTPUT>
    static void predict(const char *path, const NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network,
                        int desiredImageWidth, int desiredImageHeight)
    {
        if (std::filesystem::is_directory(path))
        {
            predictImagesFromDirectory(path, network, desiredImageWidth, desiredImageHeight);
        } else
        {
            predictImage(path, network, desiredImageWidth, desiredImageHeight);
        }
    }

private:
    template<int INPUT, int HIDDEN, int OUTPUT>
    static void predictImage(const char *imagePath, const NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network,
                             int width, int height)
    {
        Vector<INPUT> image = Data<INPUT>::loadImage(imagePath, width, height);

        auto const &result = network.guess(image);
        std::cout << "Prediction: " << result << "\n";
    }

    template<int INPUT, int HIDDEN, int OUTPUT>
    static void predictImagesFromDirectory(const char *directory, const NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network,
                                           int width, int height)
    {
        auto images = Data<INPUT>::loadImagesFromDirectory(directory, width, height);

        for (auto const&[image, imagePath] : images)
        {
            auto const &guess = network.guess(image);

            std::cout << "Image " << imagePath << " represents " << guess << '\n';
        }
    }
};


#endif //NEURALNETWORK_TRAIN_H
