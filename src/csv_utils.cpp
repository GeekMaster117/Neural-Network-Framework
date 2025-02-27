#include "csv_utils.h"

#include <fstream>
#include <sstream>

#include "config.h"
#include "error.h"

std::vector<std::vector<std::string>> readDataset(unsigned int startIndex, unsigned int endIndex, bool isTrainDataset)
{
    if(startIndex >= endIndex)
        throwValueCannotBeGreaterError(startIndex, endIndex);

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