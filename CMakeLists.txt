cmake_minimum_required(VERSION 3.15)
project(NeuralNetwork)

set(CMAKE_CXX_STANDARD 20)

add_executable(NeuralNetwork main.cpp math/Vector.h math/Matrix.h neuralNetwork/NeuralNetwork.h util/Util.cpp util/Util.h imageLoader/Data.h imageLoader/Data.cpp imageLoader/stb_image.h imageLoader/stb_image.cpp)