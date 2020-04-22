
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

    NeuralNetwork<INPUT, HIDDEN, OUTPUT> network;

    network.loadTrainedModel("trainedModel.txt");

    std::vector<std::string> labels{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

    Train train(labels, IMAGE_WIDTH, IMAGE_HEIGHT);
    train.predict("/home/david/sketchbook/Paint/image.png", network);

    return 0;
}
