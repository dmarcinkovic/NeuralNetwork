//
// Created by david on 07. 03. 2020..
//

#ifndef NEURALNETWORK_MATRIX_H
#define NEURALNETWORK_MATRIX_H

#include <array>
#include <ostream>
#include <functional>
#include <random>

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
        for (int i = 0; i < m_Matrix.size(); ++i)
        {
            for (int j = 0; j < m_Matrix[0].size(); ++j)
            {
                result[i][j] = m_Matrix[i][j] * number;
            }
        }
    }

    static Matrix<ROWS, COLS> mapValues(Matrix<ROWS, COLS> &matrix, const std::function<double(double)> &function)
    {
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                matrix[i][j] = function(matrix[i][j]);
            }
        }

        return matrix;
    }

    static double getRandomNumber(double rangeStart, double rangeEnd)
    {
        std::random_device device;
        std::mt19937_64 mt(device());
        std::uniform_real_distribution<double> distribution(rangeStart, rangeEnd);

        return distribution(mt);
    }

public:
    explicit Matrix(const std::array<std::array<double, COLS>, ROWS> &matrix)
            : m_Matrix(matrix)
    {}

    Matrix() = default;

    Matrix<ROWS, COLS> &operator*=(double number)
    {
        calculate(*this, number, [](double a, double b) {
            return a * b;
        });

        return *this;
    }

    Matrix<ROWS, COLS> operator*(int number)
    {
        Matrix<ROWS, COLS> result{};

        calculate(result, number, [](double a, double b) {
            return a * b;
        });

        return result;
    }

    std::array<double, COLS> &operator[](int index)
    {
        return m_Matrix[index];
    }

    template<int R, int C>
    Matrix<ROWS, C> operator*(Matrix<R, C> &matrix) const
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

    Matrix<ROWS, COLS> operator+(const Matrix<ROWS, COLS> &matrix) const
    {
        Matrix<ROWS, COLS> result;

        calculate(result, matrix, [](double a, double b) {
            return a + b;
        });

        return result;
    }

    Matrix<ROWS, COLS> &operator+=(const Matrix<ROWS, COLS> &matrix)
    {
        calculate(*this, matrix, [](double a, double b) {
            return a + b;
        });

        return *this;
    }

    Matrix<ROWS, COLS> operator-(const Matrix<ROWS, COLS> &matrix) const
    {
        Matrix<ROWS, COLS> result;

        calculate(result, matrix, [](double a, double b) {
            return a - b;
        });

        return result;
    }

    Matrix<ROWS, COLS> &operator-=(const Matrix<ROWS, COLS> &matrix)
    {
        calculate(*this, matrix, [](double a, double b) {
            return a - b;
        });

        return *this;
    }

    static Matrix<COLS, ROWS> transpose(Matrix<ROWS, COLS> &matrix)
    {
        Matrix<COLS, ROWS> result{};

        for (int i = 0; i < COLS; ++i)
        {
            for (int j = 0; j < ROWS; ++j)
            {
                result[i][j] = matrix[j][i];
            }
        }

        return result;
    }

    void map(const std::function<double(double)> &function)
    {
        *this = mapValues(*this, function);
    }

    static Matrix<ROWS, COLS> map(Matrix<ROWS, COLS> &matrix, const std::function<double(double)> &function)
    {
        Matrix<ROWS, COLS> result{};

        result = mapValues(matrix, function);
        return result;
    }

    static Matrix<ROWS, COLS> getRandomMatrix(double rangeStart, double rangeEnd)
    {
        Matrix<ROWS, COLS> result{};

        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                result[i][j] = getRandomNumber(rangeStart, rangeEnd);
            }
        }

        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
    {
        for (auto const &array : matrix.m_Matrix)
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
