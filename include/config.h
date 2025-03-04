#include <string>

#ifndef CONFIG_H
#define CONFIG_H

extern const unsigned int dotMulBlockSize;

extern const double randomGenMean;
double randomGenStdDeviation(unsigned int inputs);

extern const std::string trainDataset;
extern const std::string testDataset;

extern const std::string layer1Weights;
extern const std::string layer1Biases;
extern const std::string layer2Weights;
extern const std::string layer2Biases;
extern const std::string layer3Weights;
extern const std::string layer3Biases;

extern const unsigned int batchSize;

extern const double epsilon;

extern const double learningRate;
extern const double decay;
extern const double momentum;

#endif