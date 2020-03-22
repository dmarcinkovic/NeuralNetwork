
#include "imageLoader/Data.h"
#include "neuralNetwork/NeuralNetwork.h"
#include "train/Train.h"

int main()
{
    constexpr const int INPUT = 28 * 28;
    constexpr const int HIDDEN = 256;
    constexpr const int OUTPUT = 10;

    NeuralNetwork<INPUT, HIDDEN, OUTPUT> network;

//    network.loadTrainedModel("trainedModel.txt");
//
//    Vector<INPUT> image = Data::loadImage("testData/0/img_2.jpg");
//    Vector<INPUT> image = Data::loadImage("/home/david/sketchbook/Paint/image.png");
//
//    int result = network.guess(image);
//
//    std::cout << "Prediction: " << result << "\n";

    Train::train("trainingData",network);
    network.saveTrainedModel("trainedModel.txt");

    Train::test("testData", network);

    return 0;
}
