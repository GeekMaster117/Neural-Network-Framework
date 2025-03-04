#include "config.h"

#include <math.h>
#include <string>

const unsigned int dotMulBlockSize = 32;

const double randomGenMean = 0.00;
double randomGenStdDeviation(unsigned int inputs)
{
    return std::sqrt(2.00 / inputs);
}

const std::string trainDataset = "data/mnist_train.csv";
const std::string testDataset = "data/mnist_test.csv";

const std::string layer1Weights = "data/layer1_weights.csv";
const std::string layer1Biases = "data/layer1_biases.csv";
const std::string layer2Weights = "data/layer2_weights.csv";
const std::string layer2Biases = "data/layer2_biases.csv";
const std::string layer3Weights = "data/layer3_weights.csv";
const std::string layer3Biases = "data/layer3_biases.csv";

const unsigned int batchSize = 64;

const double epsilon = 0.0000001;

const double learningRate = 0.01;
const double decay = 0.001;
const double momentum = 0.9;