//
// Created by david on 07. 03. 2020..
//

#ifndef NEURALNETWORK_VECTOR_H
#define NEURALNETWORK_VECTOR_H

#include <array>
#include <ostream>
#include <functional>
#include "../util/Util.h"

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

    static Vector<N> mapValues(Vector<N> &vector, const std::function<double(double)> &function)
    {
        for (int i = 0; i < N; ++i)
        {
            vector[i] = function(vector[i]);
        }

        return vector;
    }

public:
    explicit Vector(const std::array<double, N> &vector)
            : m_Vector(vector)
    {
    }

    Vector() = default;

    double &operator[](int index)
    {
        return m_Vector[index];
    }

    Vector<N> operator+(const Vector<N> &vector) const
    {
        Vector<N> result{};

        calculate(result, vector, Util::add());

        return result;
    }

    static Vector<N> getRandomVector(double rangeStart, double rangeEnd)
    {
        Vector<N> result{};

        for (int i = 0; i < N; ++i)
        {
            result[i] = Util::getRandomNumber(-1, 1);
        }

        return result;
    }

    void map(const std::function<double(double)> &function)
    {
        *this = mapValues(*this, function);
    }

    static Vector<N> map(Vector<N> &vector, const std::function<double(double)> &function)
    {
        Vector<N> result{};

        result = mapValues(vector, function);
        return result;
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
