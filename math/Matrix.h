//
// Created by david on 07. 03. 2020..
//

#ifndef NEURALNETWORK_MATRIX_H
#define NEURALNETWORK_MATRIX_H

#include <array>
#include <ostream>
#include <functional>

template<int ROWS, int COLS>
class Matrix
{
private:
    std::array<std::array<double, COLS>, ROWS> matrix;

    Matrix<ROWS, COLS>
    calculate(const Matrix<ROWS, COLS> &mat, const std::function<double(double, double)> &binaryOperation)
    {
        Matrix<ROWS, COLS> result{};

        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                result[i][j] = binaryOperation(matrix[i][j], mat[i][j]);
            }
        }

        return result;
    }

public:
    explicit Matrix(const std::array<std::array<double, COLS>, ROWS> &matrix)
            : matrix(matrix)
    {

    }

    Matrix() = default;

    Matrix &operator*(int number)
    {
        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[0].size(); ++j)
            {
                matrix[i][j] *= number;
            }
        }

        return *this;
    }

    std::array<double, COLS> &operator[](int index)
    {
        return matrix[index];
    }

    template<int R, int C>
    Matrix<ROWS, C> operator*(Matrix<R, C> &mat) const
    {
        Matrix<ROWS, C> result{};

        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < C; ++j)
            {
                double sum = 0;
                for (int k = 0; k < COLS; ++k)
                {
                    sum += matrix[i][k] * mat[k][j];
                }
                result[i][j] = sum;
            }
        }

        return result;
    }

    Matrix<ROWS, COLS> operator+(const Matrix<ROWS, COLS> &mat) const
    {
        return calculate(mat, [](double a, double b) {
            return a + b;
        });
    }

    Matrix<ROWS, COLS> operator-(const Matrix<ROWS, COLS> &mat) const
    {
        return calculate(mat, [](double a, double b) {
            return a - b;
        });
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
