#include "matrix.hpp"

#ifndef ACTIVATION_H
#define ACTIVATION_H

Matrix activationReLU(Matrix* inputs);
Matrix activationSoftmax(Matrix* inputs);

double calculateCategoricalLoss(Matrix* outputs, Matrix* labels);
double calculateAccuracy(Matrix* outputs, Matrix* labels);

#endif