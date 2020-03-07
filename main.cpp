#include <iostream>

#include "math/Vector.h"
#include "math/Matrix.h"

int main()
{
    Vector<3> vector({1, 2, 3});

    std::cout << vector << "\n";

    Matrix<2, 2> matrix1({std::array<double, 2>{1, 1}, {3, 4}});
    Matrix<2, 2> matrix2({std::array<double, 2>{3, 4}, {1, 2}});

    matrix1 += matrix2;

    std::cout << matrix1 << "\n";

    return 0;
}
