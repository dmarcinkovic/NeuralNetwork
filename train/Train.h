//
// Created by david on 19. 03. 2020..
//

#ifndef NEURALNETWORK_TRAIN_H
#define NEURALNETWORK_TRAIN_H

#include <vector>
#include <chrono>
#include <unordered_map>

#include "../imageLoader/Data.h"
#include "../neuralNetwork/NeuralNetwork.h"

/**
 * Class that represents an interface to training neural network.
 * It contains methods for training and testing neural network on
 * labeled images and makes it very easy to use. <br>
 * Example of use: <br>
 * <pre>
 *  // Create instance of neural network <br>
 *  NeuralNetwork&lt INPUT, HIDDEN, OUTPUT > network; <br>
 *  std::vector<std::string> labels = {"dog", "cat"}; <br> <br>
 *  Train train(labels, 100, 100); <br>
 *  train.train("directoryWithImages", network); <br>
 *  train.predict("image.png", network); // Prints dog or cat
 * </pre>
 *
 *  @author David
 */
class Train
{
private:
    std::unordered_map<std::string, int> m_Labels;
    std::vector<std::string> m_NameOfLabels;

    const int imageWidth;
    const int imageHeight;

public:

    /**
     * Constructor.
     *
     * @param labels Vector of strings that represents labels.
     * @param imageWidth Desired width of all images.
     * @param imageHeight Desired height of all images.
     */
    Train(const std::vector<std::string> &labels, int imageWidth, int imageHeight)
            : m_NameOfLabels(labels), imageWidth(imageWidth), imageHeight(imageHeight)
    {
        int counter = 0;
        for (auto const &label : labels)
        {
            m_Labels[label] = counter++;
        }
    }

    /**
     * Method used to train the neural network on all images in given the given directory.
     * Directory should be in the form: <br>
     * .<br>
     * |__ label1 <br>
     * |__ label2 <br>
     * |__ label3<br>
     * |__ label4<br>
     * ... <br>
     * where label1, label2, label3 and label4 are directories that contain images
     * with labels label1, label2, label3 and label4, respectively.
     *
     * @tparam INPUT Number of nodes in the input layer of the neural network.
     * @tparam HIDDEN Number of nodes in the hidden layer of the neural network.
     * @tparam OUTPUT Number of nodes in the output layer of the neural network.
     * @param directoryName Directory where the training images are located.
     * @param network Network to be trained.
     */
    template<int INPUT, int HIDDEN, int OUTPUT>
    void train(const char *directoryName, NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network)
    {
        std::vector<Data<INPUT>> trainData = Data<INPUT>::loadLabeledData(directoryName, imageWidth, imageHeight);

        constexpr static const int numberOfEpochs = 1;

        double totalDuration = 0;
        for (int j = 0; j < numberOfEpochs; ++j)
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (auto &i : trainData)
            {
                Vector<OUTPUT> data{};
                data[m_Labels[i.getLabel()]] = 1;

                network.train(i.getData(), data);
            }

            auto end = std::chrono::high_resolution_clock::now();
            totalDuration += std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

            std::cout << "Completed: " << static_cast<double>(j + 1) / numberOfEpochs * 100 << "%\n";
        }

        std::cout << "Time took: " << totalDuration << " s\n";
    }

    /**
     * Method used to test the neural network on all images in the given directory.
     * Directory should be in the form: <br>
     * .<br>
     * |__ label1 <br>
     * |__ label2 <br>
     * |__ label3<br>
     * |__ label4<br>
     * ... <br>
     * where label1, label2, label3 and label4 are directories that contain images
     * with labels label1, label2, label3 and label4, respectively.
     *
     * @tparam INPUT Number of nodes in the input layer of the neural network.
     * @tparam HIDDEN Number of nodes in the hidden layer of the neural network.
     * @tparam OUTPUT Number of nodes in the output layer of the neural network.
     * @param directoryName Directory where the training images are located.
     * @param network  Network to be trained.
     */
    template<int INPUT, int HIDDEN, int OUTPUT>
    void test(const char *directoryName, const NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network)
    {
        std::vector<Data<INPUT>> testData = Data<INPUT>::loadLabeledData(directoryName, imageWidth, imageHeight);

        int correct = 0;
        for (auto &i : testData)
        {
            int guess = network.guess(i.getData());
            if (guess == m_Labels[i.getLabel()])
            {
                ++correct;
            }
        }

        std::cout << "Correct: " << static_cast<double>(correct) / testData.size() * 100 << "%\n";
    }

    /**
     * Method used to guess the label on image with the given path, or if the path represents directory, then
     * it guesses the label on every image in that directory.
     *
     * @tparam INPUT Number of nodes in the input layer of the neural network.
     * @tparam HIDDEN Number of nodes in the hidden layer of the neural network.
     * @tparam OUTPUT Number of nodes in the output layer of the neural network.
     * @param path  Path to image or path to directory of images.
     * @param network  Trained neural network.
     */
    template<int INPUT, int HIDDEN, int OUTPUT>
    void predict(const char *path, const NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network)
    {
        if (std::filesystem::is_directory(path))
        {
            predictImagesFromDirectory(path, network);
        } else
        {
            predictImage(path, network);
        }
    }

private:

    /**
     * Guesses the label on image with given path.
     *
     * @tparam INPUT Number of nodes in the input layer of the neural network.
     * @tparam HIDDEN  Number of nodes in the hidden layer of the neural network.
     * @tparam OUTPUT Number of nodes in the output layer of the neural network.
     * @param imagePath Path to the image.
     * @param network Trained neural network.
     */
    template<int INPUT, int HIDDEN, int OUTPUT>
    void predictImage(const char *imagePath, const NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network)
    {
        Vector<INPUT> image = Data<INPUT>::loadImage(imagePath, imageWidth, imageHeight);

        int guess = network.guess(image);
        std::cout << "Prediction: " << m_NameOfLabels[guess] << "\n";
    }

    /**
     * Guesses the label on every image in given directory.
     *
     * @tparam INPUT Number of nodes in the input layer of the neural network.
     * @tparam HIDDEN  Number of nodes in the hidden layer of the neural network.
     * @tparam OUTPUT  Number of nodes in the output layer of the neural network.
     * @param directory Path to the directory.
     * @param network Trained neural network.
     */
    template<int INPUT, int HIDDEN, int OUTPUT>
    void predictImagesFromDirectory(const char *directory, const NeuralNetwork<INPUT, HIDDEN, OUTPUT> &network)
    {
        auto images = Data<INPUT>::loadImagesFromDirectory(directory, imageWidth, imageHeight);

        for (auto const &data : images)
        {
            int guess = network.guess(data.getData());

            std::cout << "Image " << data.getLabel() << " represents " << m_NameOfLabels[guess] << '\n';
        }
    }
};


#endif //NEURALNETWORK_TRAIN_H
