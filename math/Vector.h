//
// Created by david on 07. 03. 2020..
//

#ifndef NEURALNETWORK_VECTOR_H
#define NEURALNETWORK_VECTOR_H

#include <array>
#include <ostream>
#include <functional>
#include <fstream>

#include "../util/Util.h"
#include "Matrix.h"

template<int N>
class Vector
{
private:
    std::array<double, N> m_Vector;

    void calculate(Vector<N> &result, const Vector<N> &vector,
                   const std::function<double(double, double)> &binaryOperation) const
    {
        for (int i = 0; i < N; ++i)
        {
            result[i] = binaryOperation(m_Vector[i], vector.m_Vector[i]);
        }
    }

public:
    Vector(const std::array<double, N> &vector)
            : m_Vector(vector)
    {

    }

    Vector() = default;

    double &operator[](int index)
    {
        return m_Vector[index];
    }

    const double operator[](int index) const
    {
        return m_Vector[index];
    }

    Vector<N> operator+(const Vector<N> &vector) const
    {
        Vector<N> result{};

        calculate(result, vector, std::plus<double>());

        return result;
    }

    Vector<N> &operator+=(const Vector<N> &vector)
    {
        calculate(*this, vector, std::plus<double>());

        return *this;
    }

    Vector<N> operator-(const Vector<N> &vector) const
    {
        Vector<N> result{};

        calculate(result, vector, std::minus<double>());

        return result;
    }

    Vector<N> operator*(const Vector<N> &vector) const
    {
        Vector<N> result{};

        calculate(result, vector, std::multiplies<double>());

        return result;
    }

    template<int M>
    Matrix<N, M> operator*(const Matrix<1, M> &matrix) const
    {
        Matrix<N, M> result{};

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                result[i][j] = m_Vector[i] * matrix[0][j];
            }
        }

        return result;
    }

    Matrix<1, N> transpose() const
    {
        Matrix<1, N> matrix{};

        for (int i = 0; i < N; ++i)
        {
            matrix[0][i] = m_Vector[i];
        }

        return matrix;
    }

    Vector<N> &operator*(double number)
    {
        for (int i = 0; i < N; ++i)
        {
            m_Vector[i] *= number;
        }

        return *this;
    }

    static Vector<N> getRandomVector(double rangeStart, double rangeEnd)
    {
        Vector<N> result{};

        for (int i = 0; i < N; ++i)
        {
            result[i] = Util::getRandomUniformDistribution(-1, 1);
        }

        return result;
    }

    void map(const std::function<double(double)> &function)
    {
        for (int i = 0; i < N; ++i)
        {
            m_Vector[i] = function(m_Vector[i]);
        }
    }

    static Vector<N> map(const Vector<N> &vector, const std::function<double(double)> &function)
    {
        Vector<N> result{};

        for (int i = 0; i < N; ++i)
        {
            result[i] = function(vector.m_Vector[i]);
        }

        return result;
    }

    static Vector<N> loadVector(std::ifstream &reader)
    {
        Vector<N> vector{};

        std::string line;
        std::getline(reader, line);
        std::array<double, N> array = Util::loadArray<N>(line);

        vector = Vector(array);

        return vector;
    }

    auto begin() const
    {
        return m_Vector.begin();
    }

    auto end() const
    {
        return m_Vector.end();
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector &vec)
    {
        for (auto const &element : vec.m_Vector)
        {
            os << element << ' ';
        }
        os << '\n';

        return os;
    }
};


#endif //NEURALNETWORK_VECTOR_H
