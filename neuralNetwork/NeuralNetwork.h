//
// Created by david on 07. 03. 2020..
//

#ifndef NEURALNETWORK_NEURALNETWORK_H
#define NEURALNETWORK_NEURALNETWORK_H

#include "../math/Vector.h"
#include "../math/Matrix.h"

#include <iostream>
#include <fstream>


/**
 *
 *  Class represents simple neural network which consists of only one
 *  hidden layer. <br>
 *  Example of use: <pre>
 *      // Labels are: dog, cat <br>
 *      constexpr int INPUT = 2; <br>
 *      constexpr int HIDDEN = 2; <br>
 *      constexpr int  OUTPUT = 2; <br> <br>
 *      NeuralNetwork&lt INPUT, HIDDEN, OUTPUT > network; <br> <br>
 *      // prepareData loads input data. For example loads image pixels. <br>
 *      Vector&lt INPUT > input = prepareData(); <br>
 *      Vector&lt OUTPUT > output{0, 1}; // Expected value is cat <br> <br>
 *      network.train(input, output); <br>
 *      Vector&lt INPUT > test = prepareData(); <br> <br>
 *      // Returns index 0 if prediction is dog. If prediction is cat returns 1. <br>
 *      int guess = network.guess(test); <br>
 *      network.saveTrainedModel("file.txt"); // Save trained model
 *  </pre>
 *
 * @author David
 *
 * @tparam INPUT Number of nodes in input layer.
 * @tparam HIDDEN Number of nodes in hidden layer.
 * @tparam OUTPUT Number of nodes in output layer.
 */
template<int INPUT, int HIDDEN, int OUTPUT>
class NeuralNetwork
{
private:
    constexpr static const double learningRate = 0.3;

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

    /**
     * Method used to train this neural network.
     *
     * @param inputNodes Input data represented as vector of size
     * equal to number of nodes in input layer.
     *
     * @param answer Labeled data represented as vector of size
     * equal to number of nodes in output layer.
     */
    void train(const Vector<INPUT> &inputNodes, const Vector<OUTPUT> &answer)
    {
        feedForward(inputNodes);
        backPropagation(answer);
    }

    /**
     * Used to predict output for given input data.
     *
     * @param input Input data represented as vector of size equal
     * to number of nodes in input layer.
     *
     * @return Integer which represents the index (starting from zero) of given label.
     * For example, if labels are: dog, cat and mouse. If correct answer is cat, this
     * method will return number 1.
     */
    int guess(const Vector<INPUT> &input) const
    {
        Vector<HIDDEN> hiddenNodes = m_InputHiddenWeights * input + m_InputBias;
        hiddenNodes.map(Util::getSigmoid());

        Vector<OUTPUT> output = m_HiddenOutputWeights * hiddenNodes + m_HiddenBias;
        output.map(Util::getSigmoid());

        auto maxNumber = std::max_element(output.begin(), output.end());
        return maxNumber - output.begin();
    }

    /**
     * Saves the weights and biases of the the given neural network so
     * that it is not necessary to re-train neural network during the next use.
     *
     * @param filename File in which all weights and biases will be stored.
     * @see loadTrainedModel
     */
    void saveTrainedModel(const char *filename) const
    {
        std::ofstream writer(filename);

        writer << m_InputHiddenWeights << m_HiddenOutputWeights
               << m_InputBias << m_HiddenBias << m_HiddenNodes;

        writer.close();
    }

    /**
     * Loads the weights and biases of the given neural network so
     * that it is not necessary to re-train neural network in every use.
     *
     * @param filename File in which all weights and biases are stored.
     * @see saveTrainedModel
     */
    void loadTrainedModel(const char *filename)
    {
        std::ifstream reader(filename);

        reader >> m_InputHiddenWeights >> m_HiddenOutputWeights
               >> m_InputBias >> m_HiddenBias >> m_HiddenNodes;

        reader.close();
    }

private:

    /**
     * Implementation of feed forward algorithm.
     * @param inputNodes Input data represented as vector of size equal
     * to number of nodes in input layer.
     */
    void feedForward(const Vector<INPUT> &inputNodes)
    {
        m_InputNodes = inputNodes;

        m_HiddenNodes = m_InputHiddenWeights * inputNodes + m_InputBias;
        m_HiddenNodes.map(Util::getSigmoid());

        m_OutputNodes = m_HiddenOutputWeights * m_HiddenNodes + m_HiddenBias;
        m_OutputNodes.map(Util::getSigmoid());
    }

    /**
     * Implementation of backpropagation algorithm.
     *
     * @param answer Labeled data represented as vector of size
     * equal to number of nodes in output layer.
     */
    void backPropagation(const Vector<OUTPUT> &answer)
    {
        Vector<OUTPUT> outputError = calculateError(answer, m_OutputNodes);
        Vector<OUTPUT> outputGradient =
                outputError * learningRate * Vector<OUTPUT>::map(m_OutputNodes, Util::getSigmoidDerivation());

        m_HiddenOutputWeights += outputGradient * m_HiddenNodes.transpose();
        m_HiddenBias += outputGradient;

        Vector<HIDDEN> hiddenError = m_HiddenOutputWeights.transpose() * outputError;
        Vector<HIDDEN> hiddenGradient =
                hiddenError * learningRate * Vector<HIDDEN>::map(m_HiddenNodes, Util::getSigmoidDerivation());

        m_InputHiddenWeights += hiddenGradient * m_InputNodes.transpose();
        m_InputBias += hiddenGradient;
    }

    /**
     * Method used to calculate error of output layer of neural network.
     *
     * @tparam N Number of nodes in given layer.
     * @param answer Labeled data represented as vector of size
     * equal to number of nodes in output layer.
     * @param guess Output of neural network, i.e prediction.
     *
     * @return Vector representing error that occurred in the output layer of neural network.
     */
    template<int N>
    static Vector<N> calculateError(const Vector<N> &answer, const Vector<N> &guess)
    {
        return answer - guess;
    }
};


#endif //NEURALNETWORK_NEURALNETWORK_H
