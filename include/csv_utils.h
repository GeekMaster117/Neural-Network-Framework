#include <string>
#include <vector>

#ifndef CSV_UTILS_H
#define CSV_UTILS_H

std::vector<std::vector<std::string>> readDataset(unsigned int startIndex, unsigned int endIndex, bool isTrainDataset);

unsigned int getDatasetSize(bool isTrainDataset);
unsigned int getDatasetSampleSize();

unsigned int getBatchCount(bool isTrainDataset);
std::vector<std::vector<std::string>> getDatasetBatch(unsigned int batchIndex, bool isTrainDataset);

#endif