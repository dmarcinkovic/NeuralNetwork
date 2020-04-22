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
    static void train(const char *directoryName, NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network)
    {
        std::vector<Data> trainData = Data::loadLabeledData(directoryName);

        constexpr static const int numberOfEpochs = 50;

        double totalDuration = 0;
        for (int j = 0; j < numberOfEpochs; ++j)
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (auto &i : trainData)
            {
                network.train(i.getData(), Data::getAnswerData(i.getLabel()));
            }
            auto end = std::chrono::high_resolution_clock::now();
            totalDuration += std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

            std::cout << "Completed: " << static_cast<double>(j + 1) / numberOfEpochs * 100 << "%\n";
        }

        std::cout << "Time took: " << totalDuration << " s\n";
    }

    template<int INPUT, int HIDDEN, int OUTPUT>
    static void test(const char *directoryName, const NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network)
    {
        std::vector<Data> testData = Data::loadLabeledData(directoryName);

        int correct = 0;
        for (auto &i : testData)
        {
            int guess = network.guess(i.getData());

            if (guess == std::stoi(i.getLabel()))
            {
                ++correct;
            }
        }

        std::cout << "Correct: " << static_cast<double>(correct) / testData.size() * 100 << "%\n";
    }

    template<int INPUT, int HIDDEN, int OUTPUT>
    static void predict(const char *path, const NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network)
    {
        if (std::filesystem::is_directory(path))
        {
            predictImagesFromDirectory(path, network);
        } else
        {
            predictImage(path, network);
        }
    }

private:
    template<int INPUT, int HIDDEN, int OUTPUT>
    static void predictImage(const char *imagePath, const NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network)
    {
        Vector<INPUT> image = Data::loadImage(imagePath);

        int result = network.guess(image);
        std::cout << "Prediction: " << result << "\n";
    }

    template<int INPUT, int HIDDEN, int OUTPUT>
    static void predictImagesFromDirectory(const char *directory, const NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network)
    {
        auto images = Data::loadImagesFromDirectory(directory);

        for (auto const&[image, imagePath] : images)
        {
            int guess = network.guess(image);

            std::cout << "Image " << imagePath << " represents " << guess << '\n';
        }
    }
};


#endif //NEURALNETWORK_TRAIN_H
