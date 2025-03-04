#include <string>

#ifndef CONFIG_H
#define CONFIG_H

extern const unsigned int dotMulBlockSize;

extern const double randomGenMean;
double randomGenStdDeviation(unsigned int inputs);

extern const std::string trainDatasetPath;
extern const std::string testDatasetPath;

extern const std::string layer1WeightsPath;
extern const std::string layer1BiasesPath;
extern const std::string layer2WeightsPath;
extern const std::string layer2BiasesPath;
extern const std::string layer3WeightsPath;
extern const std::string layer3BiasesPath;

extern const unsigned int batchSize;

extern const double epsilon;

extern const double learningRate;
extern const double decay;
extern const double momentum;

#endif