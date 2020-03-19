
#include "imageLoader/Data.h"
#include "neuralNetwork/NeuralNetwork.h"
#include <chrono>

int main()
{
    constexpr const int INPUT = 28 * 28;
    constexpr const int HIDDEN = 256;
    constexpr const int OUTPUT = 10;

//    std::vector<Data> input = Data::loadLabeledData("trainingData");
    std::vector<Data> testData = Data::loadLabeledData("testData");

    NeuralNetwork<INPUT, HIDDEN, OUTPUT> network;

    network.loadTrainedModel("trainedModel.txt");

//    std::cout << "Done preparing data\n";
//
//    double totalDuration = 0;
//    for (int j = 0; j < 1; ++j)
//    {
//        auto start = std::chrono::high_resolution_clock::now();
//        for (auto &i : input)
//        {
//            network.train(i.getData(), Data::getAnswerData(i.getLabel()));
//        }
//        auto end = std::chrono::high_resolution_clock::now();
//        double duration =  std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
//        std::cout << "Time took: " << duration << " s\n";
//
//        totalDuration += duration;
//    }
//    std::cout << "Total time: " << totalDuration << "s\n";

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

    //network.saveTrainedModel("trainedModel.txt");

    return 0;
}
