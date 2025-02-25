#include "layer_utils.h"

#include <random>
#include <vector>

#include "config.h"

Matrix genRandomMatrix(unsigned int rows, unsigned int cols)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(randomGenMean, randomGenStdDeviation(rows));

    std::vector<std::vector<double>> randomVector;
    
    for(unsigned int i = 0; i < rows; ++i)
    {
        std::vector<double> randomVectorRow;
        for(unsigned int j = 0; j < cols; ++j)
            randomVectorRow.push_back(dist(gen));
        randomVector.push_back(randomVectorRow);
    }

    return Matrix(rows, cols, randomVector);
}