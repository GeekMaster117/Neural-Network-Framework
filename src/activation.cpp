#include "activation.h"

#include <cmath>

#include "config.h"
#include "error.h"

Matrix activationReLU(Matrix* outputs)
{
    std::vector<std::vector<double>> resultVector(outputs -> getRows(), std::vector<double>(outputs -> getCols()));

    for(unsigned int i = 0; i < outputs -> getRows(); ++i)
        for(unsigned int j = 0; j < outputs -> getCols(); ++j)
            resultVector[i][j] = std::max(0.00, outputs -> getValue(i, j));

    return Matrix(outputs -> getRows(), outputs -> getCols(), resultVector);
}

Matrix activationSoftmax(Matrix* outputs)
{
    std::vector<std::vector<double>> softmaxVector(outputs -> getRows(), std::vector<double>(outputs -> getCols()));
    
    for(unsigned int i = 0; i < outputs -> getRows(); ++i)
    {
        double max = outputs -> getValue(i, 0);
        for(unsigned int j = 1; j < outputs -> getCols(); ++j)
            max = std::max(max, outputs -> getValue(i, j));

        double sum = 0;
        for(unsigned int j = 0; j < outputs -> getCols(); ++j)
        {
            double temp = std::exp((outputs -> getValue(i, j)) - max);
            softmaxVector[i][j] = temp;
            sum += temp;
        }
        
        for(unsigned int j = 0; j < outputs -> getCols(); ++j)
            softmaxVector[i][j] /= sum;
    }

    return Matrix(outputs -> getRows(), outputs -> getCols(), softmaxVector);
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

Matrix activationSoftmaxCategoricalLossBackward(Matrix* softmaxOutputs, Matrix* labels)
{
    if(softmaxOutputs -> getRows() != labels -> getRows())
        throwValueMustBeEqualError("Softmax Outputs Rows", softmaxOutputs -> getRows(), "Labels Rows", labels -> getRows());

    std::vector<std::vector<double>> dLoss_dOutputs = softmaxOutputs -> getVector();

    for(unsigned int i = 0; i < softmaxOutputs -> getRows(); ++i)
        for(unsigned int j = 0; j < softmaxOutputs -> getCols(); ++j)
        {
            unsigned int label = static_cast<int>(labels -> getValue(i, 0));
            if(label < 0)
                throwValueCannotBeLesserError("Label", label, "Zero", 0);
            if(label >= softmaxOutputs -> getCols())
                throwValueCannotBeGreaterError("Label", label, "Softmax Outputs Columns", softmaxOutputs -> getCols());

            if(j == label)
                dLoss_dOutputs[i][j] -= 1;

            dLoss_dOutputs[i][j] /= softmaxOutputs -> getRows();
        }

    return Matrix(softmaxOutputs -> getRows(), softmaxOutputs -> getCols(), dLoss_dOutputs);
}