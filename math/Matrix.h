//
// Created by david on 07. 03. 2020..
//

#ifndef NEURALNETWORK_MATRIX_H
#define NEURALNETWORK_MATRIX_H

#include <array>
#include <ostream>
#include <functional>
#include <random>
#include <iostream>
#include <fstream>

#include "Vector.h"
#include "../util/Util.h"

template<int N>
class Vector;

template<int ROWS, int COLS>
class Matrix
{
private:
    std::array<std::array<double, COLS>, ROWS> m_Matrix;

    void calculate(Matrix<ROWS, COLS> &result, const Matrix<ROWS, COLS> &matrix,
                   const std::function<double(double, double)> &binaryOperation) const
    {
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                result[i][j] = binaryOperation(m_Matrix[i][j], matrix.m_Matrix[i][j]);
            }
        }
    }

    void calculate(Matrix<ROWS, COLS> &result, double number,
                   const std::function<double(double, double)> &binaryOperation) const
    {
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                result[i][j] = m_Matrix[i][j] * number;
            }
        }
    }

public:
    Matrix() = default;

    Matrix<ROWS, COLS> &operator*=(double number)
    {
        calculate(*this, number, std::multiplies<double>());

        return *this;
    }

    Matrix<ROWS, COLS> operator*(int number)
    {
        Matrix<ROWS, COLS> result{};

        calculate(result, number, std::multiplies<double>());

        return result;
    }

    std::array<double, COLS> &operator[](int index)
    {
        return m_Matrix[index];
    }

    const std::array<double, COLS> &operator[](int index) const
    {
        return m_Matrix[index];
    }

    template<int C>
    Matrix<ROWS, C> operator*(const Matrix<COLS, C> &matrix) const
    {
        Matrix<ROWS, C> result{};

        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < C; ++j)
            {
                double sum = 0;
                for (int k = 0; k < COLS; ++k)
                {
                    sum += m_Matrix[i][k] * matrix[k][j];
                }
                result[i][j] = sum;
            }
        }

        return result;
    }

    Vector<ROWS> operator*(const Vector<COLS> &vector) const
    {
        Vector<ROWS> result{};
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                result[i] += vector[j] * m_Matrix[i][j];
            }
        }

        return result;
    }

    Matrix<ROWS, COLS> operator+(const Matrix<ROWS, COLS> &matrix) const
    {
        Matrix<ROWS, COLS> result;

        calculate(result, matrix, std::plus<double>());

        return result;
    }

    Matrix<ROWS, COLS> &operator+=(const Matrix<ROWS, COLS> &matrix)
    {
        calculate(*this, matrix, std::plus<double>());

        return *this;
    }

    Matrix<ROWS, COLS> operator-(const Matrix<ROWS, COLS> &matrix) const
    {
        Matrix<ROWS, COLS> result;

        calculate(result, matrix, std::minus<double>());

        return result;
    }

    Matrix<ROWS, COLS> &operator-=(const Matrix<ROWS, COLS> &matrix)
    {
        calculate(*this, matrix, std::minus<double>());

        return *this;
    }

    Matrix<COLS, ROWS> transpose() const
    {
        Matrix<COLS, ROWS> result{};

        for (int i = 0; i < COLS; ++i)
        {
            for (int j = 0; j < ROWS; ++j)
            {
                result[i][j] = m_Matrix[j][i];
            }
        }

        return result;
    }

    static Matrix<ROWS, COLS> getRandomMatrix(int numberOfInputUnits, int numberOfOutputUnits)
    {
        Matrix<ROWS, COLS> result{};

        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                result[i][j] = Util::getRandomNormalDistribution(0,
                                                                 Util::getNormalXavierDeviation(numberOfInputUnits,
                                                                                                numberOfOutputUnits));
            }
        }

        return result;
    }

    friend std::istream &operator>>(std::istream &is, Matrix &matrix)
    {
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                is >> matrix.m_Matrix[i][j];
            }
        }

        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
    {
        for (auto const &array : matrix.m_Matrix)
        {
            for (auto const &element : array)
            {
                os << element << ' ';
            }
            os << '\n';
        }

        return os;
    }
};


#endif //NEURALNETWORK_MATRIX_H
