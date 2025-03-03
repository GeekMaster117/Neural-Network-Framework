#include "layer.hpp"

#include "layer_utils.h"
#include "matrix.hpp"
#include "config.h"

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

Matrix Layer::forward(Matrix* inputs)
{
    Matrix forwardPass = inputs -> dot(&(this -> weights));
    return forwardPass.add(&(this -> biases), true);
}

Matrix Layer::backward(Matrix* inputs, Matrix* dLoss_dOutputs)
{
    Matrix inputsTransposed = inputs -> transpose();
    Matrix dLoss_dWeights = inputsTransposed.dot(dLoss_dOutputs);
    Matrix weightsUpdateStep = dLoss_dWeights.mul(learningRate);

    std::vector<std::vector<double>> dLoss_dBiasesVector(1, std::vector<double>(this -> biases.getCols(), 0.0));
    for(unsigned int i = 0; i < dLoss_dOutputs -> getRows(); ++i)
    {
        for(unsigned int j = 0; j < dLoss_dOutputs -> getCols(); ++j)
            dLoss_dBiasesVector[0][j] += dLoss_dOutputs -> getValue(i, j);
    }
    Matrix dLoss_dBiases = Matrix(1, this -> biases.getCols(), dLoss_dBiasesVector);
    Matrix biasesUpdateStep = dLoss_dBiases.mul(learningRate);

    Matrix weightsTransposed = this -> weights.transpose();
    Matrix dLoss_dInputs = dLoss_dOutputs -> dot(&weightsTransposed);

    this -> weights = this -> weights.add(&weightsUpdateStep);
    this -> biases = this -> biases.add(&biasesUpdateStep);

    return dLoss_dInputs;
}