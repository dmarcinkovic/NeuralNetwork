
#include "imageLoader/Data.h"
#include "neuralNetwork/NeuralNetwork.h"
#include <chrono>

int main()
{
    constexpr const int INPUT = 28 * 28;
    constexpr const int HIDDEN = 128;
    constexpr const int OUTPUT = 10;

    std::vector<Data> input = Data::loadLabeledData("trainingData");
    std::vector<Data> testData = Data::loadLabeledData("testData");

    NeuralNetwork<INPUT, HIDDEN, OUTPUT> network;

    std::cout << "Done preparing data\n";

    for (int j = 0; j < 20; ++j)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (auto &i : input)
        {
            network.train(i.getData(), Data::getAnswerData(i.getLabel()));
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Time took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms\n";
    }

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

    return 0;
}
