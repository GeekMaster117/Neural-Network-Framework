#include <iostream>

#include "matrix.hpp"

int main()
{
    Matrix* inputs = new Matrix(3, 4);
    Matrix* weights = new Matrix(3, 4);
    Matrix* biases = new Matrix(1, 3);

    inputs -> fillMatrix(2.00);
    weights -> fillMatrix(4.00);
    biases -> fillMatrix(3.00);

    Matrix* outputs = biases -> add(inputs -> dot(weights -> transpose()), true);
    outputs -> displayData();
    
    return 0;
}