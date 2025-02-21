#include <iostream>

#include "matrix.hpp"

int main()
{
    Matrix* matrix1 = new Matrix(2, 3);
    Matrix* matrix2 = new Matrix(3, 2);

    matrix1 -> fillMatrix(2.00);
    matrix1 -> displayData();

    std::cout << std::endl;

    matrix2 -> fillMatrix(4.00);
    matrix2 -> displayData();

    std::cout << std::endl;

    Matrix* dotMatrix = matrix1 -> dot(matrix2);
    dotMatrix -> displayData();
    
    return 0;
}