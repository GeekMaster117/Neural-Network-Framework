#include "matrix.hpp"

#ifndef LOSS_H
#define LOSS_H

double calculateCategoricalLoss(Matrix* outputs, Matrix* labels);

double calculateAccuracy(Matrix* outputs, Matrix* labels);

#endif