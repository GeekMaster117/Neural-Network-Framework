#include <string>

#ifndef CONFIG_H
#define CONFIG_H

extern const unsigned int dotMulBlockSize;

extern const double randomGenMean;
double randomGenStdDeviation(unsigned int inputs);

extern const std::string trainDatasetPath;
extern const std::string testDatasetPath;

extern const std::string paramsPath;

extern const unsigned int chunkSize;
extern const unsigned int batchSize;

extern const double epsilon;

extern const double learningRate;
extern const double decay;
extern const double momentum;

#endif