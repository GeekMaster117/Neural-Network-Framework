#include <iostream>

#include "layer.hpp"
#include "csv_utils.hpp"
#include "activation.h"
#include "config.h"

int main()
{
    CSV layer1WeightsDataset = CSV(paramsPath + "/layer1_weights.csv");
    CSV layer1BiasesDataset = CSV(paramsPath + "/layer1_biases.csv");
    CSV layer2WeightsDataset = CSV(paramsPath + "/layer2_weights.csv");
    CSV layer2BiasesDataset = CSV(paramsPath + "/layer2_biases.csv");
    CSV layer3WeightsDataset = CSV(paramsPath + "/layer3_weights.csv");
    CSV layer3BiasesDataset = CSV(paramsPath + "/layer3_biases.csv");

    CSV dataset = CSV(testDatasetPath);

    layer1WeightsDataset.loadAll();
    layer1BiasesDataset.loadAll();
    layer2WeightsDataset.loadAll();
    layer2BiasesDataset.loadAll();
    layer3WeightsDataset.loadAll();
    layer3BiasesDataset.loadAll();

    dataset.loadAll();

    Matrix layer1Weights = layer1WeightsDataset.getSamples();
    Matrix layer1Biases = layer1BiasesDataset.getSamples();
    Matrix layer2Biases = layer2BiasesDataset.getSamples();
    Matrix layer2Weights = layer2WeightsDataset.getSamples();
    Matrix layer3Biases = layer3BiasesDataset.getSamples();
    Matrix layer3Weights = layer3WeightsDataset.getSamples();

    Layer layer1 = Layer(784, 256, &layer1Weights, &layer1Biases);
    Layer layer2 = Layer(256, 256, &layer2Weights, &layer2Biases);
    Layer layer3 = Layer(256, 10, &layer3Weights, &layer3Biases);

    Matrix inputs = dataset.getSamples();
    Matrix inputsNormalized = inputs.div(255.00);

    Matrix layer1Outputs = layer1.forward(&inputsNormalized);
    Matrix activation1Outputs = activationReLU(&layer1Outputs);

    Matrix layer2Outputs = layer2.forward(&activation1Outputs);
    Matrix activation2Outputs = activationReLU(&layer2Outputs);

    Matrix layer3Outputs = layer3.forward(&activation2Outputs);
    Matrix activation3Outputs = activationSoftmax(&layer3Outputs);
    
    Matrix labels = dataset.getLabels();

    std::cout << "Accuracy: " << calculateAccuracy(&activation3Outputs, &labels) << std::endl;

    return 0;
}