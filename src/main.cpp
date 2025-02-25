#include "layer.hpp"

int main()
{
    Matrix inputs = Matrix(3, 3);
    inputs.fillMatrix(1.00);

    Layer layer1 = Layer(3, 4);
    Layer layer2 = Layer(4, 4);
    Layer layer3 = Layer(4, 2);

    Matrix layer1Outputs = layer1.forward(&inputs);
    Matrix layer2Outputs = layer2.forward(&layer1Outputs);
    Matrix layer3Outputs = layer3.forward(&layer2Outputs);

    layer3Outputs.displayData();
    
    return 0;
}