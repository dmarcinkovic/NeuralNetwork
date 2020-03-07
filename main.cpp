#include <iostream>

#include "math/Vector.h"
#include "math/Matrix.h"

int main()
{
    Vector<3> vector({1, 2, 3});

    Matrix<3, 2> matrix({std::array<double, 2>{1, 6},
                         {5, 4},
                         {6, 7}});

    std::cout << vector << "\n";

    std::cout << matrix << "\n";

    return 0;
}
