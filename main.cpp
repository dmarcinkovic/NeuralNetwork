
#include "imageLoader/Data.h"
#include "neuralNetwork/NeuralNetwork.h"
#include <chrono>

int main()
{
    constexpr const int INPUT = 28 * 28;
    constexpr const int HIDDEN = 128;
    constexpr const int OUTPUT = 10;

    std::vector<Data> input = Data::loadLabeledData("trainingData");
    Data::shuffleData(input);

    NeuralNetwork<INPUT, HIDDEN, OUTPUT> network;

    std::cout << "Done preparing data\n";

    auto start = std::chrono::high_resolution_clock::now();
    for (auto &i : input)
    {
        network.train(i.getData(), Data::getAnswerData(i.getLabel()));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    int correct = 0;
    int totalNumberOfTests = 0;
    for (int i = 0; i < 20000; ++i)
    {
        int guess = network.guess(input[i].getData());

        if (guess == std::stoi(input[i].getLabel()))
        {
            ++correct;
        }

        ++totalNumberOfTests;
    }

    std::cout << "Correct: " << static_cast<double>(correct) / totalNumberOfTests * 100 << "%\n";

    return 0;
}
