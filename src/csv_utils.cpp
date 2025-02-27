#include "csv_utils.h"

#include <fstream>
#include <sstream>

#include "config.h"
#include "error.h"

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

Matrix readDataset(unsigned int startIndex, unsigned int endIndex, bool isTrainDataset)
{
    if(startIndex >= endIndex)
        throwValueCannotBeGreaterError("StartIndex", startIndex, "EndIndex", endIndex);

    std::string datasetName = isTrainDataset ? trainDataset : testDataset;

    std::ifstream file(datasetName);
    if(!file.is_open())
        throwFileCannotBeOpenedError(datasetName);

    std::string line;

    if(std::getline(file, line))
        if(line.empty())
            throwDatasetEmptyError();

    std::vector<std::vector<double>> dataset(endIndex - startIndex, std::vector<double>(getDatasetSampleSize()));
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
            dataset[currentIndex - startIndex][i] = std::stod(cell);
    }

    file.close();

    if(dataset.empty())
        throwDatasetEmptyError();

    return Matrix(endIndex - startIndex, getDatasetSampleSize(), dataset);
}

unsigned int getBatchCount(bool isTrainDataset)
{
    unsigned int datasetSize = getDatasetSize(isTrainDataset);
    
    unsigned int batchCount = datasetSize % batchSize == 0 ? 0 : 1;
    batchCount += datasetSize / batchSize;

    return batchCount;
}

Matrix getDatasetBatch(unsigned int batchIndex, bool isTrainDataset)
{
    unsigned int batchCount = getBatchCount(isTrainDataset);
    if(batchIndex >= batchCount)
        throwValueCannotBeGreaterError("BatchIndex", batchIndex, "BatchCount", batchCount);

    unsigned int datasetSize = getDatasetSize(isTrainDataset);
    return readDataset(batchIndex * batchSize, std::min((batchIndex * batchSize) + batchSize, datasetSize), isTrainDataset);
}

Matrix getLabels(unsigned int batchIndex, bool isTrainDataset)
{
    Matrix datasetBatch = getDatasetBatch(batchIndex, isTrainDataset);
 
    std::vector<std::vector<double>> labels;
    for(unsigned int i = 0; i < datasetBatch.getRows(); ++i)
    {
        std::vector<double> label(1);
        label[0] = datasetBatch.getValue(i, 0);
        labels.push_back(label);
    }

    return Matrix(datasetBatch.getRows(), 1, labels);
}

Matrix getSamples(unsigned int batchIndex, bool isTrainDataset)
{
    Matrix datasetBatch = getDatasetBatch(batchIndex, isTrainDataset);

    std::vector<std::vector<double>> samples;
    for(unsigned int i = 0; i < datasetBatch.getRows(); ++i)
    {
        std::vector<double> sample(getDatasetSampleSize());
        for(unsigned int j = 1; j < datasetBatch.getCols(); ++j)
            sample.push_back(datasetBatch.getValue(i, j));
        samples.push_back(sample);
    }

    return Matrix(datasetBatch.getRows(), getDatasetSampleSize(), samples);
}