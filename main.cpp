#include <iostream>

#include "math/Vector.h"
#include "math/Matrix.h"

int main()
{
    Vector<3> vector({1, 2, 3});

    Matrix<2, 1> matrix({std::array<double, 1>{2}, {3}});
    Matrix<1, 3> matrix1({std::array<double, 3>{1, 2, 3}});

    std::cout << vector << "\n";

    std::cout << matrix << "\n";
    std::cout << matrix1 << "\n";

    auto result = matrix * matrix1;

    std::cout << result << "\n";

    return 0;
}
