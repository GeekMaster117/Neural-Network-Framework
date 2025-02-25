#include "config.h"
#include <math.h>

const unsigned int dotMulBlockSize = 32;

const double randomGenMean = 0.00;
double randomGenStdDeviation(unsigned int inputs)
{
    return std::sqrt(2.00 / inputs);
}