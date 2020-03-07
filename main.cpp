#include <iostream>

#include "math/Vector.h"
#include "math/Matrix.h"

int main()
{
    Matrix<2,2> matrix({std::array<double, 2>{2,1}, {3,1}});
    Vector<2> vector({1, 1});

    std::cout << matrix << "\n";

    std::cout << vector << "\n";

    auto resultVector = matrix * vector;

    std::cout << resultVector << "\n";

    return 0;
}
