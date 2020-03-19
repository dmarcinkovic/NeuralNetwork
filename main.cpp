
#include "imageLoader/Data.h"
#include "neuralNetwork/NeuralNetwork.h"
#include "train/Train.h"

int main()
{
    constexpr const int INPUT = 28 * 28;
    constexpr const int HIDDEN = 256;
    constexpr const int OUTPUT = 10;

    NeuralNetwork<INPUT, HIDDEN, OUTPUT> network;

    Train::train("trainingData", network);

    Train::test("testData", network);

    return 0;
}
