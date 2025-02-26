#include "activation.h"

#include <cmath>

Matrix activationReLU(Matrix* inputs)
{
    std::vector<std::vector<double>> resultVector(inputs -> getRows(), std::vector<double>(inputs -> getCols()));

    for(unsigned int i = 0; i < inputs -> getRows(); ++i)
        for(unsigned int j = 0; j < inputs -> getCols(); ++j)
            resultVector[i][j] = std::max(0.00, inputs -> getValue(i, j));

    return Matrix(inputs -> getRows(), inputs -> getCols(), resultVector);
}

Matrix activationSoftmax(Matrix* inputs)
{
    std::vector<std::vector<double>> softmaxVector(inputs -> getRows(), std::vector<double>(inputs -> getCols()));
    
    for(unsigned int i = 0; i < inputs -> getRows(); ++i)
    {
        double max = inputs -> getValue(i, 0);
        for(unsigned int j = 1; j < inputs -> getCols(); ++j)
            max = std::max(max, inputs -> getValue(i, j));

        double sum = 0;
        for(unsigned int j = 0; j < inputs -> getCols(); ++j)
        {
            double temp = std::exp((inputs -> getValue(i, j)) - max);
            softmaxVector[i][j] = temp;
            sum += temp;
        }
        
        for(unsigned int j = 0; j < inputs -> getCols(); ++j)
            softmaxVector[i][j] /= sum;
    }

    return Matrix(inputs -> getRows(), inputs -> getCols(), softmaxVector);
}