#include <string>

#ifndef CONFIG_H
#define CONFIG_H

extern const unsigned int dotMulBlockSize;

extern const double randomGenMean;
double randomGenStdDeviation(unsigned int inputs);

extern const std::string trainDataset;
extern const std::string testDataset;

#endif