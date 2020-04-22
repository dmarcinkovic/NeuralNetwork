
#include "imageLoader/Data.h"
#include "neuralNetwork/NeuralNetwork.h"
#include "train/Train.h"

int main()
{
    constexpr const int INPUT = 28 * 28;
    constexpr const int HIDDEN = 128;
    constexpr const int OUTPUT = 10;

    NeuralNetwork<INPUT, HIDDEN, OUTPUT> network;

    network.loadTrainedModel("trainedModel.txt");

    Train::predict("/home/david/sketchbook/Paint/image.png", network);

    return 0;
}
