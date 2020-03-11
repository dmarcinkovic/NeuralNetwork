
#include "neuralNetwork/NeuralNetwork.h"
#include <cmath>

int main()
{
    constexpr const int INPUT = 2;
    constexpr const int HIDDEN = 4;
    constexpr const int OUTPUT = 1;

    NeuralNetwork<INPUT, HIDDEN, OUTPUT> network;

    std::array<Vector<INPUT>, 4> inputs{Vector<INPUT>{{0, 0}},
                                        Vector<INPUT>{{0, 1}},
                                        Vector<INPUT>{{1, 0}},
                                        Vector<INPUT>{{1, 1}}};

    std::array<Vector<OUTPUT>, 4> outputs{Vector<OUTPUT>{{0}},
                                          Vector<OUTPUT>{{1}},
                                          Vector<OUTPUT>{{1}},
                                          Vector<OUTPUT>{{0}}};

    constexpr const int numberOfEpochs = 10000;
    for (int i = 0; i < numberOfEpochs; ++i)
    {
        int index = std::floor(Util::getRandomUniformDistribution(0, 4));
        network.train(inputs[index], outputs[index]);
    }

    std::cout << "guessing output\n";
    Vector<INPUT> input{{0, 0}};
    network.guess(input);

    return 0;
}
