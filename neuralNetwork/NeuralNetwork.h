//
// Created by david on 07. 03. 2020..
//

#ifndef NEURALNETWORK_NEURALNETWORK_H
#define NEURALNETWORK_NEURALNETWORK_H

#include "../math/Vector.h"
#include "../math/Matrix.h"

#include <iostream>

template<int INPUT, int HIDDEN, int OUTPUT>
class NeuralNetwork
{
private:
    Matrix<HIDDEN, INPUT> m_HiddenInputWeights;
    Matrix<OUTPUT, HIDDEN> m_OutputHiddenWeights;

    Vector<HIDDEN> m_InputBias;
    Vector<OUTPUT> m_HiddenBias;

public:
    NeuralNetwork()
    {
        m_HiddenInputWeights = Matrix<HIDDEN, INPUT>::getRandomMatrix(-1, 1);
        m_OutputHiddenWeights = Matrix<OUTPUT, HIDDEN>::getRandomMatrix(-1, 1);

        m_InputBias = Vector<HIDDEN>::getRandomVector(-1, 1);
        m_HiddenBias = Vector<OUTPUT>::getRandomVector(-1, 1);
    }

    template<int N>
    void feedForward(Vector<N> &inputNodes)
    {
        auto hiddenNodes = m_HiddenInputWeights * inputNodes + m_InputBias;
        hiddenNodes.map(Util::getSigmoid());

        auto outputNodes = m_OutputHiddenWeights * hiddenNodes + m_HiddenBias;
        outputNodes.map(Util::getSigmoid());

        std::cout << "Output nodes\n";
        std::cout << outputNodes << "\n";
    }
};


#endif //NEURALNETWORK_NEURALNETWORK_H
