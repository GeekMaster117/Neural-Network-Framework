#include "matrix.hpp"

#ifndef LAYER_HPP
#define LAYER_HPP

class Layer
{
    private:
        Matrix weights;
        Matrix biases;
    public:
        Layer(unsigned int inputNeurons, unsigned int outputNeurons);

        Matrix getWeights();
        Matrix getBiases();

        Matrix forward(Matrix* inputs);

        Matrix backward(Matrix* inputs, Matrix* dLoss_dOutputs);
};

#endif