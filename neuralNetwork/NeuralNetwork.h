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
    constexpr static const double learningRate = 0.2;

    Matrix<HIDDEN, INPUT> m_InputHiddenWeights;
    Matrix<OUTPUT, HIDDEN> m_HiddenOutputWeights;

    Vector<HIDDEN> m_InputBias;
    Vector<OUTPUT> m_HiddenBias;

    Vector<INPUT> m_InputNodes;
    Vector<HIDDEN> m_HiddenNodes;
    Vector<OUTPUT> m_OutputNodes;

public:
    NeuralNetwork()
    {
        m_InputHiddenWeights = Matrix<HIDDEN, INPUT>::getRandomMatrix(INPUT, HIDDEN);
        m_HiddenOutputWeights = Matrix<OUTPUT, HIDDEN>::getRandomMatrix(HIDDEN, OUTPUT);

        m_InputBias = Vector<HIDDEN>::getRandomVector(-1, 1);
        m_HiddenBias = Vector<OUTPUT>::getRandomVector(-1, 1);
    }

    void feedForward(Vector<INPUT> &inputNodes)
    {
        m_InputNodes = inputNodes;

        m_HiddenNodes = m_InputHiddenWeights * inputNodes + m_InputBias;
        m_HiddenNodes.map(Util::getSigmoid());

        m_OutputNodes = m_HiddenOutputWeights * m_HiddenNodes + m_HiddenBias;
        m_OutputNodes.map(Util::getSigmoid());
    }

    void backPropagation(const Vector<OUTPUT> &answer)
    {
        Vector<OUTPUT> outputError = calculateError(answer, m_OutputNodes);
        Vector<OUTPUT> outputNodesDerivation = Vector<OUTPUT>::map(m_OutputNodes, Util::getSigmoidDerivation());
        Matrix<OUTPUT, HIDDEN> deltaOutputHiddenWeights =
                outputError * learningRate * outputNodesDerivation * m_HiddenNodes.transpose();

        Vector<HIDDEN> hiddenError = m_HiddenOutputWeights.transpose() * outputError;
        Vector<HIDDEN> hiddenNodesDerivation = Vector<HIDDEN>::map(m_HiddenNodes,Util::getSigmoidDerivation());
        Matrix<HIDDEN, INPUT> deltaInputsHiddenWeights =
                hiddenError * learningRate * hiddenNodesDerivation * m_InputNodes.transpose();
    }

private:

    template<int N>
    static Vector<N> calculateError(const Vector<N> &answer, const Vector<N> &guess)
    {
        return answer - guess;
    }
};


#endif //NEURALNETWORK_NEURALNETWORK_H
