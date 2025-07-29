# Neural Network Framework

## What is Neural Network Framework?
- A framework built from the ground up to use Neural Networks in C++
- Uses Adaptive Momentum for backwards propagation
  
## How to use the framework?
- **CSV-Utils.hpp** - Can be used to handle CSV files. It needs the CSV files to have the first column as labels, and each row representing data for each input neuron. Loads a chunk of the dataset into memory at a time to reduce overhead on the drive.
  - **CSV(datasetname)** - Constructor can be initialised with a path to the dataset.

  - **getDatasetSize()** - Returns the size of the dataset.
  - **getSampleSize()** - Returns the size of each sample.
  - **getChunkCount()** - Returns the number of chunks that can be loaded from the dataset.
  - **loadAll()** - Loads the entire dataset into memory. Recommended only when enough memory is available.
  - **loadChunk(chunkIndex)** - Loads the nth chunk into memory, where n = chunkIndex + 1.
  
  - **Ensure to call loadChunk() or loadAll() before invoking below methods**:
    - **getBatchCount()** - Returns the number of batches that can be fed to the network from the loaded chunk.
    - **getDatasetBatch(batchIndex)** - Returns the nth batch (labels + samples), where n = batchIndex + 1.
    - **getLabels(batchIndex)** - Returns the labels of nth batch, where n = batchIndex + 1.
    - **getLabels()** - Returns all the labels of the loaded chunk.
    - **getSamples(batchIndex)** - Returns the samples of nth batch, where n = batchIndex + 1.
   
- **Matrix.cpp** - Can be used to handle Matrices. Ensure to pass a two-dimensional vector whenever a vector needs to be passed.
  - **Matrix()** - Constructor to initialise an empty matrix.
  - **Matrix(rows, cols)** - Constructor to initialise an empty matrix with set rows and columns.
  - **Matrix(rows, cols, vector)** - Constructor to initialise an empty matrix with set rows and columns. Fills the matrix with data from the vector.
  
  - **getRows()** - Returns the rows of matrix.
  - **getCols()** - Returns the columns of matrix.
  - **getVector()** - Returns a two-dimensional vector representing matrix data.
  - **getValue(row, col)** - Returns the value at a particular row and column of the matrix.
  - **inputVector(vector)** - Fills the matrix with data from the matrix.
  - **fillMatrix(value)** - Fills the matrix with single value.
  - **displayData()** - Prints matrix data.
  
  - **add(value)** - Adds a single value to the entire Matrix.
  - **add(matrix)** - Returns a matrix which is the sum of itself and the matrix passed.

  - **sub(value)** - Subtracts a single value from the entire Matrix.
  - **sub(matrix)** - Returns a matrix which is the difference of itself and the matrix passed.

  - **mul(value)** - Multiplies a single value by the entire Matrix.
  - **mul(matrix)** - Returns a matrix which is the product of itself and the matrix passed.

  - **div(value)** - Divides a single value from the entire Matrix.
  - **div(matrix)** - Returns a matrix which is the quotient of itself and the matrix passed.
 
  - **If broadcast is set to true and the dimensions of matrices do not match, it tries to broadcast the smaller matrix; if unable will throw an error, for the below methods:**
    - **add(matrix, broadcast)** - Similar to add(matrix) but with broadcast.
    - **sub(matrix, broadcast)** - Similar to sub(matrix) but with broadcast.
    - **mul(matrix, broadcast)** - Similar to mul(matrix) but with broadcast.
    - **div(matrix, broadcast)** - Similar to div(matrix) but with broadcast.
   
  - **dot(matrix) - Returns a matrix which is the dot product of itself and the matrix passed.
 
- **layer.hpp** - Can be used to handle network layers.
  - **Layer(inputNeurons, outputNeurons)** - Constructor to initialise a layer with set input and output neurons.
  - **Layer(inputNeurons, outputNeurons, weights, biases)** - Constructor to initialise a layer with set input and output neurons, weights and biases. Ensure weights is a matrix of size inputNeurons, outputNeurons, and biases is a matrix of size 1, outputNeurons.

  - **getWeights()** - Returns a matrix of weights.
  - **getBiases()** - Returns a matrix of biases.
 
  - **forward(inputs)** - Returns a matrix which is the output of forward propagation of inputs. Ensure the sample size and input neurons of the layer are the same.
  - **backward(inputs, dLoss_dOutputs (derivative of change in network loss by change in layer outputs), epoch)** - Returns a matrix which is dLoss_dInputs (derivative of change in network loss by change in layer inputs) for the respective epoch. Uses adaptive momentum.
 
  - **saveParama(paramsName)** - Saves weights and biases to the paramsName file in the drive.

- **activation.h** - Can be used for activation functions and calculating loss.
  - **activationReLU(inputs)** - Returns a matrix containing ReLU activation of the inputs passed.
  - **activationReLUBackward(inputs, dLoss_dOutputs (derivative of change in network loss by change in activation outputs))** - Returns a matrix which is dLoss_dInputs (derivative of change in network loss by change in activation inputs).
    
  - **activationSoftman(inputs)** - Returns a matrix containing Softmax activation of the inputs passed.
  - **activationSoftmaxCategoricalLossBackward(outputs, labels)** - Returns a matrix which is dLoss_dInputs (derivative of change in network loss by change in activation inputs) for the output passed through Softmax Activation and then loss calculated with Categorical Loss.
 
- **config.h** - To be used for configuring the framework.
  - **dotMulBlockSize** - Matrix.dot() performs dot product in blocks, to take advantage of the CPU cache. It can be adjusted depending on the size of the CPU cache.
    
  - **randomGenMean** - Mean used for generating random weights and biases. Default value generates in normal distribution manner.
  - **randomGenStdDeviation(inputs)** - Standard Deviation used for generating weights and biases, inputs represent the size of input neurons.
 
  - **trainDatasetPath** - Path to training dataset.
  - **testDatasetPath** - Path to testing dataset.
  - **paramsPath** - Path to store and retrieve weights and biases.
 
  - **chunkSize** - Size of a chunk of the dataset to be loaded into memory at a time.
  - **batchSize** - Number of samples to be passed into the network at a time for training.
 
  - **epsilon** - Small value used in backwards propagation to prevent division by zero.
  - **learningRate** - How fast the network learns, too high may cause the network to jump over global minima, too low may cause the network to be stuck in local minima.
  - **decay** - How fast the learning rate decays, too high may cause the network to converge to minima too fast, too low may cause the network to converge to minima too slow.
  - **momentum** - How much of the previous weights to consider to preserve inertia, too high may cause the network to not accept change, too low may cause the network to ignore inertia.
    
## Trained and tested on MNIST digit database with 95% accuracy.
Dataset:- https://www.kaggle.com/datasets/oddrationale/mnist-in-csv
