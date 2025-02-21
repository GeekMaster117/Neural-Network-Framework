#include <iostream>

#include "matrix.hpp"

int main()
{
    Matrix* inputs = new Matrix(3, 4);
    Matrix* weights = new Matrix(3, 4);

    inputs -> fillMatrix(2.00);
    weights -> fillMatrix(4.00);

    Matrix* outputs = inputs -> dot(weights -> transpose());
    outputs -> displayData();
    
    return 0;
}