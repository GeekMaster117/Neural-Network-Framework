#include <string>
#include <vector>

#include "matrix.hpp"

#ifndef CSV_UTILS_HPP
#define CSV_UTILS_HPP

class CSV
{
    private:
        std::string datasetName;
        unsigned int datasetSize;
        unsigned int sampleSize;

        Matrix dataset;

        unsigned int readDatasetSize();
        unsigned int readSampleSize();
        Matrix readDataset(unsigned int startIndex, unsigned int endIndex);
    public:
        CSV(std::string datasetName, unsigned int initLoad);

        unsigned int getDatasetSize();
        unsigned int getSampleSize();

        unsigned int getBatchCount();
        Matrix getDatasetBatch(unsigned int batchIndex);

        Matrix getLabels();
        Matrix getLabels(unsigned int batchIndex);
        Matrix getSamples();
        Matrix getSamples(unsigned int batchIndex);
};

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