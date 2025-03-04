#include "matrix.hpp"

#include <string>

#ifndef LAYER_HPP
#define LAYER_HPP

class Layer
{
    private:
        Matrix weights;
        Matrix biases;

        Matrix weightMomentums;
        Matrix biasMomentums;
    public:
        Layer(unsigned int inputNeurons, unsigned int outputNeurons);
        Layer(unsigned int inputNeurons, unsigned int outputNeurons, Matrix* weights, Matrix* biases);

        Matrix getWeights();
        Matrix getBiases();

        Matrix forward(Matrix* inputs);

        Matrix backward(Matrix* inputs, Matrix* dLoss_dOutputs, int epoch);

        void saveParams(std::string paramsName);
};

#endif