#include <iostream>
#include <string>

#include "layer.hpp"
#include "layer_utils.h"
#include "csv_utils.h"
#include "activation.h"

int main()
{
    Layer layer1 = Layer(784, 256);
    Layer layer2 = Layer(256, 256);
    Layer layer3 = Layer(256, 10);

    for(unsigned int i = 0; i < getBatchCount(true); ++i)
    {
        Matrix inputs = getSamples(i, true);

        Matrix layer1Outputs = layer1.forward(&inputs);
        Matrix activation1Outputs = activationReLU(&layer1Outputs);

        Matrix layer2Outputs = layer2.forward(&layer1Outputs);
        Matrix activation2Outputs = activationReLU(&layer2Outputs);

        Matrix layer3Outputs = layer3.forward(&layer2Outputs);
        Matrix activation3Outputs = activationSoftmax(&layer3Outputs);
    
        Matrix labels = getLabels(i, true);

        std::cout << "Epoch: " << i + 1 << std::endl;
        std::cout << "Loss: " << calculateCategoricalLoss(&activation3Outputs, &labels) << std::endl;
        std::cout << "Accuracy: " << calculateAccuracy(&activation3Outputs, &labels) << std::endl << std::endl;
    }
    
    return 0;
}