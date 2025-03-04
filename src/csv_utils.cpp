#include "csv_utils.h"

#include <fstream>
#include <sstream>

#include "config.h"
#include "error.h"

unsigned int getDatasetSize(std::string datasetName)
{
    std::ifstream file(datasetName);
    if(!file.is_open())
        throwFileCannotBeOpenedError(datasetName);

    std::string line;

    if(std::getline(file, line))
        if(line.empty())
            throwDatasetEmptyError();

    unsigned int size = 0;
    for(; std::getline(file, line); ++size)
        if(line.empty())
        {
            --size;
            continue;
        }

    return size;
}

unsigned int getDatasetSampleSize(std::string datasetName)
{
    std::ifstream file(datasetName);
    if(!file.is_open())
        throwFileCannotBeOpenedError(datasetName);

    std::string line;

    unsigned int size = -1;
    if(std::getline(file, line))
    {
        if(line.empty())
            throwDatasetEmptyError();

        std::stringstream ss(line);
        std::string cell;
        for(; std::getline(ss, cell, ','); ++size);
    }

    return size;
}

Matrix readDataset(unsigned int startIndex, unsigned int endIndex, std::string datasetName)
{
    if(startIndex >= endIndex)
        throwValueCannotBeGreaterError("StartIndex", startIndex, "EndIndex", endIndex);

    std::ifstream file(datasetName);
    if(!file.is_open())
        throwFileCannotBeOpenedError(datasetName);

    std::string line;

    if(std::getline(file, line))
        if(line.empty())
            throwDatasetEmptyError();

    std::vector<std::vector<double>> dataset(std::min(endIndex - startIndex, getDatasetSize(datasetName) - startIndex), std::vector<double>(getDatasetSampleSize(datasetName)));
    for(unsigned int currentIndex = 0; std::getline(file, line); ++currentIndex) 
    {
        if(currentIndex < startIndex)
            continue;
        if(currentIndex >= endIndex)
            break;

        if(line.empty())
        {
            --currentIndex;
            continue;
        }

        std::stringstream ss(line);
        std::string cell;
        for(unsigned int i = 0; std::getline(ss, cell, ','); ++i)
            dataset[currentIndex - startIndex][i] = std::stod(cell);
    }

    file.close();

    if(dataset.empty())
        throwDatasetEmptyError();

    return Matrix(std::min(endIndex - startIndex, getDatasetSize(datasetName) - startIndex), getDatasetSampleSize(datasetName), dataset);
}

void writeDataset(Matrix* matrix, std::string datasetName)
{
    std::ofstream file(datasetName);
    if(!file.is_open())
        throwFileCannotBeOpenedError(datasetName);

    file << "row\\col";
    for(unsigned int i = 0; i < matrix -> getCols(); ++i)
        file << "," << i + 1;
    file << std::endl;

    for(unsigned int i = 0; i < matrix -> getRows(); ++i)
    {
        file << i + 1;
        for(unsigned int j = 0; j < matrix -> getCols(); ++j)
            file << "," << matrix -> getValue(i, j);
        file << std::endl;
    }

    file.close();
}

unsigned int getBatchCount(std::string datasetName)
{
    unsigned int datasetSize = getDatasetSize(datasetName);
    
    unsigned int batchCount = datasetSize % batchSize == 0 ? 0 : 1;
    batchCount += datasetSize / batchSize;

    return batchCount;
}

Matrix getDatasetBatch(unsigned int batchIndex, std::string datasetName)
{
    unsigned int batchCount = getBatchCount(datasetName);
    if(batchIndex >= batchCount)
        throwValueCannotBeGreaterError("BatchIndex", batchIndex, "BatchCount", batchCount);

    unsigned int datasetSize = getDatasetSize(datasetName);
    return readDataset(batchIndex * batchSize, std::min((batchIndex * batchSize) + batchSize, datasetSize), datasetName);
}

Matrix getLabels(unsigned int batchIndex, std::string datasetName)
{
    Matrix datasetBatch = getDatasetBatch(batchIndex, datasetName);
 
    std::vector<std::vector<double>> labels(datasetBatch.getRows(), std::vector<double>(1));
    for(unsigned int i = 0; i < datasetBatch.getRows(); ++i)
        labels[i][0] = datasetBatch.getValue(i, 0);

    return Matrix(datasetBatch.getRows(), 1, labels);
}

Matrix getSamples(unsigned int batchIndex, std::string datasetName)
{
    Matrix datasetBatch = getDatasetBatch(batchIndex, datasetName);

    std::vector<std::vector<double>> samples(datasetBatch.getRows(), std::vector<double>(getDatasetSampleSize(datasetName)));
    for(unsigned int i = 0; i < datasetBatch.getRows(); ++i)
        for(unsigned int j = 1; j < datasetBatch.getCols(); ++j)
            samples[i][j - 1] = datasetBatch.getValue(i, j);

    return Matrix(datasetBatch.getRows(), getDatasetSampleSize(datasetName), samples);
}