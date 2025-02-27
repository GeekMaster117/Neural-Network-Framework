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

const unsigned int batchSize = 128;