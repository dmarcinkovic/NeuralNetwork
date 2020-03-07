#include <iostream>

#include "math/Vector.h"
#include "math/Matrix.h"

int main()
{
    Vector<3> vector({1, 2, 3});

    std::cout << vector << "\n";

    Matrix<3, 2> matrix({std::array<double, 2>{3, 4}, {1, 2}, {0.5, 0.3}});

    std::cout << matrix << "\n";

    auto result = Matrix<3, 2>::transpose(matrix);

    std::cout << result << "\n";

    result.map([](double a) {
        return a * (a - 1);
    });

    std::cout << result << "\n";

    Matrix<3, 3> randomMatrix = Matrix<3, 3>::getRandomMatrix(-1, 1);

    std::cout << randomMatrix << "\n";

    return 0;
}
