#include "csv_utils.h"

#include <fstream>
#include <sstream>

#include "config.h"
#include "error.h"

std::vector<std::vector<std::string>> readDataset(unsigned int startIndex, unsigned int endIndex, bool isTrainDataset)
{
    if(startIndex >= endIndex)
        throwValueCannotBeGreaterError("StartIndex", startIndex, "EndIndex", endIndex);

    std::string datasetName = isTrainDataset ? trainDataset : testDataset;

    std::ifstream file(datasetName);
    if(!file.is_open())
        throwFileCannotBeOpenedError(datasetName);

    unsigned int sampleSize = 0;

    std::string line;

    if(std::getline(file, line))
    {
        if(line.empty())
            throwDatasetEmptyError();

        std::stringstream ss(line);
        std::string cell;
        for(; std::getline(ss, cell, ','); ++sampleSize);
    }

    std::vector<std::vector<std::string>> dataset = std::vector(endIndex - startIndex, std::vector<std::string>(sampleSize));
    for(unsigned int currentIndex = 0; std::getline(file, line); ++currentIndex) 
    {
        if(currentIndex < startIndex)
        {
            --currentIndex;
            continue;
        }
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
            dataset[currentIndex - startIndex][i] = cell;
    }

    file.close();

    if(dataset.empty())
        throwDatasetEmptyError();

    return dataset;
}

unsigned int getDatasetSize(bool isTrainDataset)
{
    std::string datasetName = isTrainDataset ? trainDataset : testDataset;

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

unsigned int getDatasetSampleSize()
{
    std::ifstream file(trainDataset);
    if(!file.is_open())
        throwFileCannotBeOpenedError(trainDataset);

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

unsigned int getBatchCount(bool isTrainDataset)
{
    unsigned int datasetSize = getDatasetSize(isTrainDataset);
    
    unsigned int batchCount = datasetSize % batchSize == 0 ? 0 : 1;
    batchCount += datasetSize / batchSize;

    return batchCount;
}

std::vector<std::vector<std::string>> getDatasetBatch(unsigned int batchIndex, bool isTrainDataset)
{
    unsigned int batchCount = getBatchCount(isTrainDataset);
    if(batchIndex >= batchCount)
        throwValueCannotBeGreaterError("BatchIndex", batchIndex, "BatchCount", batchCount);

    unsigned int datasetSize = getDatasetSize(isTrainDataset);
    return readDataset(batchIndex * batchSize, std::min((batchIndex * batchSize) + batchSize, datasetSize), isTrainDataset);
}