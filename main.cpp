
#include "neuralNetwork/NeuralNetwork.h"

int main()
{
    constexpr const int INPUT = 2;
    constexpr const int HIDDEN = 2;
    constexpr const int OUTPUT = 1;

    NeuralNetwork<INPUT, HIDDEN, OUTPUT> network;

    Vector<INPUT> inputNodes({0.8, 0.2});
    Vector<OUTPUT> answer({1});

    network.train(inputNodes, answer);


    return 0;
}
