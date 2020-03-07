//
// Created by david on 07. 03. 2020..
//

#ifndef NEURALNETWORK_VECTOR_H
#define NEURALNETWORK_VECTOR_H

#include <array>
#include <ostream>

template<int N>
class Vector
{
private:
    std::array<double, N> vector;

public:
    explicit Vector(const std::array<double, N> &vector)
        : vector(vector)
    {
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector &vec)
    {
        for (auto const &element : vec.vector)
        {
            os << element << ' ';
        }
        os << '\n';

        return os;
    }
};


#endif //NEURALNETWORK_VECTOR_H
