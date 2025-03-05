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
        CSV(std::string datasetName);

        unsigned int getDatasetSize();
        unsigned int getSampleSize();

        unsigned int getChunkCount();
        void loadChunk(unsigned int chunkIndex);

        unsigned int getBatchCount();
        Matrix getDatasetBatch(unsigned int batchIndex);

        Matrix getLabels();
        Matrix getLabels(unsigned int batchIndex);
        Matrix getSamples();
        Matrix getSamples(unsigned int batchIndex);
};

void writeDataset(Matrix* matrix, std::string datasetName);

#endif