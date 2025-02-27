#include <string>
#include <vector>

#ifndef CSV_UTILS_H
#define CSV_UTILS_H

std::vector<std::vector<std::string>> readDataset(unsigned int startIndex, unsigned int endIndex, bool isTrainDataset);

#endif