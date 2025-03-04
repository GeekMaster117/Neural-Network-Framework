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

const std::string paramsPath = "data/params";

const unsigned int batchSize = 64;

const double epsilon = 0.0000001;

const double learningRate = 0.01;
const double decay = 0.001;
const double momentum = 0.9;