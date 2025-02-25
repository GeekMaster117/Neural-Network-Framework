#include "layer.hpp"

#include "layer_utils.h"
#include "matrix.hpp"

Layer::Layer(unsigned int inputNeurons, unsigned int outputNeurons): weights(genRandomMatrix(inputNeurons, outputNeurons)), biases(genRandomMatrix(1, outputNeurons))
{
    this -> weights = this -> weights.mul(0.01);
}

Matrix Layer::getWeights()
{
    return this -> weights;
}

Matrix Layer::getBiases()
{
    return this -> biases;
}