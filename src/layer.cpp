#include "layer.hpp"

#include "layer_utils.h"
#include "csv_utils.hpp"
#include "matrix.hpp"
#include "config.h"

double currentLearningRate(int epoch)
{
    return learningRate * (1 + (decay * epoch));
}

Layer::Layer(unsigned int inputNeurons, unsigned int outputNeurons): weights(genRandomMatrix(inputNeurons, outputNeurons)), 
biases(Matrix(1, outputNeurons)),
weightMomentums(Matrix(inputNeurons, outputNeurons)),
biasMomentums(Matrix(1, outputNeurons)) {}

Layer::Layer(unsigned int inputNeurons, unsigned int outputNeurons, Matrix* weights, Matrix* biases): weights(*weights), 
biases(*biases),
weightMomentums(Matrix(inputNeurons, outputNeurons)),
biasMomentums(Matrix(1, outputNeurons)) {}

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
    return inputs -> dot(&(this->weights)).add(&(this->biases), true);
}

Matrix Layer::backward(Matrix* inputs, Matrix* dLoss_dOutputs, int epoch)
{
    Matrix inputsTransposed = inputs -> transpose();
    Matrix dLoss_dWeights = inputsTransposed.dot(dLoss_dOutputs);
    Matrix weightUpdates = dLoss_dWeights.mul(currentLearningRate(epoch));
    weightUpdates = this -> weightMomentums.mul(momentum).sub(&weightUpdates);
    this -> weightMomentums = weightUpdates;

    std::vector<std::vector<double>> dLoss_dBiasesVector(1, std::vector<double>(this -> biases.getCols(), 0.0));
    for(unsigned int i = 0; i < dLoss_dOutputs -> getRows(); ++i)
    {
        for(unsigned int j = 0; j < dLoss_dOutputs -> getCols(); ++j)
            dLoss_dBiasesVector[0][j] += dLoss_dOutputs -> getValue(i, j);
    }
    Matrix dLoss_dBiases = Matrix(1, this -> biases.getCols(), dLoss_dBiasesVector);
    Matrix biasUpdates = dLoss_dBiases.mul(currentLearningRate(epoch));
    biasUpdates = this -> biasMomentums.mul(momentum).sub(&biasUpdates);
    biasMomentums = biasUpdates;

    Matrix weightsTransposed = this -> weights.transpose();
    Matrix dLoss_dInputs = dLoss_dOutputs -> dot(&weightsTransposed);

    this -> weights = this -> weights.add(&weightUpdates);
    this -> biases = this -> biases.add(&biasUpdates);

    return dLoss_dInputs;
}

void Layer::saveParams(std::string paramsName)
{
    writeDataset(&(this -> weights), paramsPath + "/" + paramsName + "_weights.csv");
    writeDataset(&(this -> biases), paramsPath + "/" + paramsName + "_biases.csv");
}