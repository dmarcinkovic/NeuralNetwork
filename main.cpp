
#include "imageLoader/Data.h"
#include "neuralNetwork/NeuralNetwork.h"
#include <chrono>

int main()
{
    constexpr const int INPUT = 28 * 28;
    constexpr const int HIDDEN = 64;
    constexpr const int OUTPUT = 10;

    std::vector<Data> input = Data::loadLabeledData("trainingData");
    Data::shuffleData(input);

    NeuralNetwork<INPUT, HIDDEN, OUTPUT> network;

    std::cout << "Done preparing data\n";

    auto start = std::chrono::high_resolution_clock::now();
    for (auto & i : input)
    {
        network.train(i.getData(), Data::getAnswerData(i.getLabel()));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    network.guess(input[0].getData());

    std::cout << "result should be : " << input[0].getLabel() << "\n";

    return 0;
}
