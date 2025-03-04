#include "config.h"

#include <math.h>
#include <string>

const unsigned int dotMulBlockSize = 32;

const double randomGenMean = 0.00;
double randomGenStdDeviation(unsigned int inputs)
{
    return std::sqrt(2.00 / inputs);
}

const std::string trainDatasetPath = "data/mnist_train.csv";
const std::string testDatasetPath = "data/mnist_test.csv";

const std::string layer1WeightsPath = "data/layer1_weights.csv";
const std::string layer1BiasesPath = "data/layer1_biases.csv";
const std::string layer2WeightsPath = "data/layer2_weights.csv";
const std::string layer2BiasesPath = "data/layer2_biases.csv";
const std::string layer3WeightsPath = "data/layer3_weights.csv";
const std::string layer3BiasesPath = "data/layer3_biases.csv";

const unsigned int batchSize = 64;

const double epsilon = 0.0000001;

const double learningRate = 0.01;
const double decay = 0.001;
const double momentum = 0.9;