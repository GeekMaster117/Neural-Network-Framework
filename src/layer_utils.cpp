#include "layer_utils.h"

#include <random>
#include <vector>

#include "config.h"

Matrix genRandomMatrix(unsigned int rows, unsigned int cols)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(randomGenMean, randomGenStdDeviation(rows));

    std::vector<std::vector<double>> randomVector(rows, std::vector<double>(cols));
    
    for(unsigned int i = 0; i < rows; ++i)
        for(unsigned int j = 0; j < cols; ++j)
            randomVector[i][j] = dist(gen);

    return Matrix(rows, cols, randomVector);
}