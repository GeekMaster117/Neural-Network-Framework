Neural Network Framework
-------------------------------------
What is Neural Network Framework?
- A framework built from the ground up to use Neural Networks in C++
- Uses Adaptive Momentum for backwards propagation
-------------------------------------
How to use the framework?
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
  - **Matrix(rows, cols, vector)** - Constructor to initialise an empty matrix with set rows and columns. Fills the matrix with data from vector.
  
  - **getRows()** - Returns the rows of matrix.
  - **getCols()** - Returns the columns of matrix.
  - **getVector()** - Returns a two-dimensional vector representing matrix data.
  - **getValue(row, col)** - Returns the value at a particular row and column of the matrix.
  - **inputVector(vector)** - Fills the matrix with data from matrix.
  - **fillMatrix(value)** - Fills the matrix with single value.
  - **displayData()** - Prints matrix data.
  
  - **add(value)** - Adds a single value to the entire Matrix.
  - **add(matrix)** - Returns a matrix which is the sum of itself and the matrix passed.

  - **sub(value)** - Subtracts a single value from the entire Matrix.
  - **sub(matrix)** - Returns a matrix which is the difference of itself and the matrix passed.

  - **mul(value)** - Multiplies a single value to the entire Matrix.
  - **mul(matrix)** - Returns a matrix which is the product of itself and the matrix passed.

  - **div(value)** - Divides a single value from the entire Matrix.
  - **div(matrix)** - Returns a matrix which is the quotient of itself and the matrix passed.
 
  - **If broadcast is set to true and the dimensions of matrices do not match, it tries to broadcast the smaller matrix; if unable will throw an error, for the below methods:**
    - **add(matrix, broadcast)** - Similar to add(matrix) but with broadcast.
    - **sub(matrix, broadcast)** - Similar to sub(matrix) but with broadcast.
    - **mul(matrix, broadcast)** - Similar to mul(matrix) but with broadcast.
    - **div(matrix, broadcast)** - Similar to div(matrix) but with broadcast.
   
  - **dot(matrix) - Returns a matrix which is the dot product of itself and the matrix passed.

Dataset:- https://www.kaggle.com/datasets/oddrationale/mnist-in-csv
