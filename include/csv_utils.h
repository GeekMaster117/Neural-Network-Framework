#include <string>
#include <vector>

#include "matrix.hpp"

#ifndef CSV_UTILS_H
#define CSV_UTILS_H

unsigned int getDatasetSize(bool isTrainDataset);
unsigned int getDatasetSampleSize();

Matrix readDataset(unsigned int startIndex, unsigned int endIndex, bool isTrainDataset);

unsigned int getBatchCount(bool isTrainDataset);
Matrix getDatasetBatch(unsigned int batchIndex, bool isTrainDataset);

Matrix getLabels(unsigned int batchIndex, bool isTrainDataset);
Matrix getSamples(unsigned int batchIndex, bool isTrainDataset);

#endif