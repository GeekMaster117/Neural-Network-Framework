#include <iostream>

#include "matrix.hpp"
#include "layer_utils.h"

int main()
{
    Matrix inputs = genRandomMatrix(3, 4);
    Matrix weights = genRandomMatrix(3, 4);
    Matrix biases = genRandomMatrix(1, 3);

    Matrix weightsTransposed = weights.transpose();
    Matrix forwardPass = inputs.dot(&weightsTransposed);
    Matrix outputs = biases.add(&forwardPass, true);

    outputs.displayData();
    
    return 0;
}