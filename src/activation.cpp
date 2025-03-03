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
        unsigned int label = static_cast<unsigned int>(labels -> getValue(i, 0));
        if(label < 0)
            throwValueCannotBeLesserError("Label", label, "Zero", 0);
        if(label >= outputs -> getCols())
            throwValueCannotBeGreaterError("Label", label, "Softmax Outputs Columns", outputs -> getCols());

        double confidence = outputs -> getValue(i, label);
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

Matrix activationReLUBackward(Matrix* inputs, Matrix* dLoss_dOutputs)
{
    std::vector<std::vector<double>> dLoss_dInputs(dLoss_dOutputs -> getRows(), std::vector<double>(dLoss_dOutputs -> getCols()));
    for(unsigned int i = 0; i < dLoss_dOutputs -> getRows(); ++i)
        for(unsigned int j = 0; j < dLoss_dOutputs -> getCols(); ++j)
        {
            double value = inputs -> getValue(i, j);
            if(value < 0)
                dLoss_dInputs[i][j] = 0;
            else
                dLoss_dInputs[i][j] = dLoss_dOutputs -> getValue(i, j);
        }

    return Matrix(dLoss_dOutputs -> getRows(), dLoss_dOutputs -> getCols(), dLoss_dInputs);
}

Matrix activationSoftmaxCategoricalLossBackward(Matrix* outputs, Matrix* labels)
{
    if(outputs -> getRows() != labels -> getRows())
        throwValueMustBeEqualError("Softmax Outputs Rows", outputs -> getRows(), "Labels Rows", labels -> getRows());

    std::vector<std::vector<double>> dLoss_dOutputs = outputs -> getVector();

    for(unsigned int i = 0; i < outputs -> getRows(); ++i)
        for(unsigned int j = 0; j < outputs -> getCols(); ++j)
        {
            unsigned int label = static_cast<unsigned int>(labels -> getValue(i, 0));
            if(label < 0)
                throwValueCannotBeLesserError("Label", label, "Zero", 0);
            if(label >= outputs -> getCols())
                throwValueCannotBeGreaterError("Label", label, "Softmax Outputs Columns", outputs -> getCols());

            if(j == label)
                dLoss_dOutputs[i][j] -= 1;

            dLoss_dOutputs[i][j] /= outputs -> getRows();
        }

    return Matrix(outputs -> getRows(), outputs -> getCols(), dLoss_dOutputs);
}