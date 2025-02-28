#include "loss.h"

#include "error.h"

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