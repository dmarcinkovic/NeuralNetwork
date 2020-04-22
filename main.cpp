
#include "imageLoader/Data.h"
#include "neuralNetwork/NeuralNetwork.h"
#include "train/Train.h"

int main()
{
    constexpr const int IMAGE_WIDTH = 28;
    constexpr const int IMAGE_HEIGHT = 28;
    constexpr const int INPUT = IMAGE_WIDTH * IMAGE_HEIGHT;
    constexpr const int HIDDEN = 128;
    constexpr const int OUTPUT = 10;

    NeuralNetwork<INPUT, HIDDEN, OUTPUT> network({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});

    network.loadTrainedModel("trainedModel.txt");

    Train::predict("/home/david/sketchbook/Paint/image.png", network, IMAGE_WIDTH, IMAGE_HEIGHT);

    return 0;
}
