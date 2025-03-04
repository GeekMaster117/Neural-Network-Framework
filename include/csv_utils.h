#include <string>
#include <vector>

#include "matrix.hpp"

#ifndef CSV_UTILS_H
#define CSV_UTILS_H

unsigned int getDatasetSize(std::string datasetName);
unsigned int getDatasetSampleSize(std::string datasetName);

Matrix readDataset(unsigned int startIndex, unsigned int endIndex, std::string datasetName);
void writeDataset(Matrix* matrix, std::string datasetName);

unsigned int getBatchCount(std::string datasetName);
Matrix getDatasetBatch(unsigned int batchIndex, std::string datasetName);

Matrix getLabels(std::string datasetName);
Matrix getLabels(unsigned int batchIndex, std::string datasetName);
Matrix getSamples(std::string datasetName);
Matrix getSamples(unsigned int batchIndex, std::string datasetName);

#endif