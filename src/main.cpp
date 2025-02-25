#include <iostream>

#include "matrix.hpp"

int main()
{
    Matrix inputs = Matrix(100, 200);
    Matrix weights = Matrix(100, 200);
    Matrix biases = Matrix(1, 100);

    inputs.fillMatrix(2.00);
    weights.fillMatrix(4.00);
    biases.fillMatrix(3.00);

    Matrix weightsTransposed = weights.transpose();
    Matrix forwardPass = inputs.dot(&weightsTransposed);
    Matrix outputs = biases.add(&forwardPass, true);

    outputs.displayData();
    
    return 0;
}