
#include "imageLoader/Data.h"
#include "neuralNetwork/NeuralNetwork.h"
#include "train/Train.h"

int main()
{
    constexpr const int INPUT = 28 * 28;
    constexpr const int HIDDEN = 128;
    constexpr const int OUTPUT = 10;

    NeuralNetwork<INPUT, HIDDEN, OUTPUT> network({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});

//    network.loadTrainedModel("trainedModel.txt");
    Train::train("trainingData", network);

    Train::predict("/home/david/sketchbook/Paint/image.png", network);

    Train::test("testData", network);

    return 0;
}
