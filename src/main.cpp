#include "layer.hpp"

int main()
{
    Matrix inputs = Matrix(10, 3);
    inputs.fillMatrix(1.00);

    Layer inputLayer = Layer(3, 4);

    Matrix outputs = inputLayer.forward(&inputs);
    outputs.displayData();
    
    return 0;
}