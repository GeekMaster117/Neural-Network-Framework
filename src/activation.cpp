#include "activation.h"

#include <cmath>

#include "config.h"
#include "error.h"

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

double calculateCategoricalLoss(Matrix* outputs, Matrix* labels)
{
    if(outputs -> getRows() != labels -> getRows())
        throwValueMustBeEqualError("Outputs Rows", outputs -> getRows(), "Labels Rows", labels -> getRows());

    double negLogSum = 0.00;
    for(unsigned int i = 0; i < outputs -> getRows(); ++i)
    {
        double confidence = outputs -> getValue(i, labels -> getValue(i, 0));
        confidence = std::max(epsilon, confidence);
        confidence = std::min(confidence, 1 - epsilon);

        negLogSum += -log(confidence);
    }

    return negLogSum / (outputs -> getRows());
}

double calculateAccuracy(Matrix* outputs, Matrix* labels)
{
    if(outputs -> getRows() != labels -> getRows())
        throwValueMustBeEqualError("Outputs Rows", outputs -> getRows(), "Labels Rows", labels -> getRows());

    unsigned int correctPredictions = 0;

    for(unsigned int i = 0; i < outputs -> getRows(); ++i)
    {
        unsigned int max = 0;
        for(unsigned int j = 1; j < outputs -> getCols(); ++j)
            max = (outputs -> getValue(i, j)) > (outputs -> getValue(i, max)) ? j : max;
        
        if(max == labels -> getValue(i, 0))
            ++correctPredictions;
    }

    return (static_cast<double>(correctPredictions) / static_cast<double>(outputs -> getRows())) * 100.00;
}