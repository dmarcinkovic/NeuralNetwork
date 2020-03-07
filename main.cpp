#include <iostream>

#include "math/Vector.h"
#include "math/Matrix.h"

int main()
{
    Matrix<2, 2> matrix({std::array<double, 2>{2, 1}, {3, 1}});
    Vector<2> vector({1, 1});

    std::cout << matrix << "\n";

    std::cout << vector << "\n";

    auto resultVector = matrix * vector;

    std::cout << resultVector << "\n";

    Matrix<4, 3> matrix1({std::array<double, 3>{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {0, 1, 2}});
    Matrix<3, 5> matrix2({std::array<double, 5>{1, 2, 3, 4, 5}, {6, 7, 8, 9, 0}, {1, 1, 1, 1, 1}});

    auto result = matrix1 * matrix2;

    std::cout << result << "\n";

    return 0;
}
