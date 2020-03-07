//
// Created by david on 07. 03. 2020..
//

#ifndef NEURALNETWORK_MATRIX_H
#define NEURALNETWORK_MATRIX_H

#include <array>
#include <ostream>

template<int ROWS, int COLS>
class Matrix
{
private:
    std::array<std::array<double, COLS>, ROWS> matrix;

public:
    explicit Matrix(const std::array<std::array<double, COLS>, ROWS> &matrix)
            : matrix(matrix)
    {

    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat)
    {
        for (auto const &array : mat.matrix)
        {
            for (auto const &element : array)
            {
                os << element << ' ';
            }
            std::cout << '\n';
        }

        return os;
    }
};


#endif //NEURALNETWORK_MATRIX_H
