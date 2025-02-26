#include "layer.hpp"
#include "layer_utils.h"
#include "activation.h"

int main()
{
    Matrix inputs = genRandomMatrix(3, 3);

    Layer layer1 = Layer(3, 4);
    Layer layer2 = Layer(4, 4);
    Layer layer3 = Layer(4, 2);

    Matrix layer1Outputs = layer1.forward(&inputs);
    Matrix activation1Outputs = activationReLU(&layer1Outputs);

    Matrix layer2Outputs = layer2.forward(&layer1Outputs);
    Matrix activation2Outputs = activationReLU(&layer2Outputs);

    Matrix layer3Outputs = layer3.forward(&layer2Outputs);
    Matrix activation3Outputs = activationSoftmax(&layer3Outputs);
    
    activation3Outputs.displayData();
    
    return 0;
}