#include "matrix.hpp"

#include <iostream>
#include <vector>

#include "error.h"
#include "config.h"

Matrix::Matrix(unsigned int rows, unsigned int cols, std::vector<double>& vector): rows(rows), cols(cols), vector(vector) {}

Matrix::Matrix(unsigned int rows, unsigned int cols): rows(rows), cols(cols), vector(rows * cols) {}

Matrix::Matrix(unsigned int rows, unsigned int cols, std::vector<std::vector<double>>& vector): rows(rows), cols(cols), vector(rows * cols)
{
    this -> inputVector(vector);
}

unsigned int Matrix::getRows()
{
    return this -> rows;
}

unsigned int Matrix::getCols()
{
    return this -> cols;
}

std::vector<std::vector<double>> Matrix::getVector()
{
    std::vector<std::vector<double>> resultVector(this -> rows, std::vector<double>(this -> cols));

    std::vector<double>::iterator it = this -> vector.begin();
    for(size_t i = 0; i < static_cast<size_t>(this -> rows); ++i, it += static_cast<size_t>(this -> cols))
        resultVector[i] = std::vector<double>(it, it + static_cast<size_t>(this -> cols));

    return resultVector;
}

double Matrix::getValue(unsigned int row, unsigned int col)
{
    return this -> vector[(row * this -> cols) + col];
}

void Matrix::inputVector(std::vector<std::vector<double>>& vector)
{
    if(vector.size() != static_cast<size_t>(this -> rows) || vector[0].size() != static_cast<size_t>(this -> cols))
        throwMismatchDimensionsError(this -> rows, this -> cols, vector.size(), vector[0].size());

    for(unsigned int i = 0; i < this -> rows; ++i)
        for(unsigned int j = 0; j < this -> cols; ++j)
            this -> vector[(i * this -> cols) + j] = vector[i][j];
}

void Matrix::fillMatrix(double value)
{
    for(unsigned int i = 0; i < (this -> rows) * (this -> cols); ++i)
            this -> vector[i] = value;
}

void Matrix::displayData()
{
    for(unsigned int i = 0; i < this -> rows; ++i)
    {
        std::cout << this -> vector[(i * this -> cols)];
        for(unsigned int j = 1; j < this -> cols; ++j)
        {
            std::cout << ", " << this -> vector[(i * this -> cols) + j];
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::add(double value)
{
    std::vector<double> resultVector((this -> rows) * (this -> cols));

    for(unsigned int i = 0; i < (this -> rows) * (this -> cols); ++i)
            resultVector[i] = (this -> vector[i]) + value;

    return Matrix(this -> getRows(), this -> getCols(), resultVector);
}

Matrix Matrix::add(Matrix* matrix)
{
    if(this -> rows != matrix -> rows || this -> cols != matrix -> cols)
        throwMismatchDimensionsError(this -> rows, this -> cols, matrix -> rows, matrix -> cols);

    std::vector<double> resultVector((this -> rows) * (this -> cols));

    for(unsigned int i = 0; i < (this -> rows) * (this -> cols); ++i)
            resultVector[i] = (this -> vector[i]) + (matrix -> vector[i]);

    return Matrix(this -> rows, this -> cols, resultVector);
}

Matrix Matrix::add(Matrix* matrix, bool broadcast)
{
    if(!broadcast || (this -> rows == matrix -> rows && this -> cols == matrix -> cols))
        return this -> add(matrix);

    if((this -> rows != matrix -> rows && this -> cols != matrix -> cols)
    ||
    (this -> rows != 1 && this -> cols != 1 && matrix -> rows != 1 && matrix -> cols != 1))
        throwCustomMismatchDimensionsError("Neither Matrice could not be broadcast.\n"
        "Atleast one of the dimensions should be same and the other dimension of the smaller matrix should be 1.", 
        this -> rows, this -> cols, matrix -> rows, matrix -> cols);

    unsigned int resultRows = std::max(this -> rows, matrix -> rows);
    unsigned int resultCols = std::max(this -> cols, matrix -> cols);

    std::vector<double> resultVector(resultRows * resultCols);

    for (unsigned int i = 0; i < resultRows; ++i) 
    {
        for (unsigned int j = 0; j < resultCols; ++j) 
        {
            unsigned int thisMatrixRow = (this -> rows == 1) ? 0 : i;
            unsigned int thisMatrixCol = (this -> cols == 1) ? 0 : j;
            unsigned int inputMatrixRow = (matrix -> rows == 1) ? 0 : i;
            unsigned int inputMatrixCol = (matrix -> cols == 1) ? 0 : j;

            resultVector[(i * resultCols) + j] = this -> vector[(thisMatrixRow * this -> cols) + thisMatrixCol] + 
            matrix -> vector[(inputMatrixRow * matrix -> cols) + inputMatrixCol];
        }
    }

    return Matrix(resultRows, resultCols, resultVector);
}

Matrix Matrix::sub(double value)
{
    std::vector<double> resultVector((this -> rows) * (this -> cols));

    for(unsigned int i = 0; i < (this -> rows) * (this -> cols); ++i)
            resultVector[i] = (this -> vector[i]) - value;

    return Matrix(this -> getRows(), this -> getCols(), resultVector);
}

Matrix Matrix::sub(Matrix* matrix)
{
    if(this -> rows != matrix -> rows || this -> cols != matrix -> cols)
        throwMismatchDimensionsError(this -> rows, this -> cols, matrix -> rows, matrix -> cols);

    std::vector<double> resultVector((this -> rows) * (this -> cols));

    for(unsigned int i = 0; i < (this -> rows) * (this -> cols); ++i)
            resultVector[i] = (this -> vector[i]) - (matrix -> vector[i]);

    return Matrix(this -> rows, this -> cols, resultVector);
}

Matrix Matrix::sub(Matrix* matrix, bool broadcast)
{
    if(!broadcast || (this -> rows == matrix -> rows && this -> cols == matrix -> cols))
        return this -> sub(matrix);

    if((this -> rows != matrix -> rows && this -> cols != matrix -> cols)
    ||
    (this -> rows != 1 && this -> cols != 1 && matrix -> rows != 1 && matrix -> cols != 1))
        throwCustomMismatchDimensionsError("Neither Matrice could not be broadcast.\n"
        "Atleast one of the dimensions should be same and the other dimension of the smaller matrix should be 1.", 
        this -> rows, this -> cols, matrix -> rows, matrix -> cols);

    unsigned int resultRows = std::max(this -> rows, matrix -> rows);
    unsigned int resultCols = std::max(this -> cols, matrix -> cols);

    std::vector<double> resultVector(resultRows * resultCols);

    for (unsigned int i = 0; i < resultRows; ++i) 
    {
        for (unsigned int j = 0; j < resultCols; ++j) 
        {
            unsigned int thisMatrixRow = (this -> rows == 1) ? 0 : i;
            unsigned int thisMatrixCol = (this -> cols == 1) ? 0 : j;
            unsigned int inputMatrixRow = (matrix -> rows == 1) ? 0 : i;
            unsigned int inputMatrixCol = (matrix -> cols == 1) ? 0 : j;

            resultVector[(i * resultCols) + j] = this -> vector[(thisMatrixRow * this -> cols) + thisMatrixCol] -
            matrix -> vector[(inputMatrixRow * matrix -> cols) + inputMatrixCol];
        }
    }

    return Matrix(resultRows, resultCols, resultVector);
}

Matrix Matrix::mul(double value)
{
    std::vector<double> resultVector((this -> rows) * (this -> cols));

    for(unsigned int i = 0; i < (this -> rows) * (this -> cols); ++i)
            resultVector[i] = (this -> vector[i]) * value;

    return Matrix(this -> getRows(), this -> getCols(), resultVector);
}

Matrix Matrix::mul(Matrix* matrix)
{
    if(this -> rows != matrix -> rows || this -> cols != matrix -> cols)
        throwMismatchDimensionsError(this -> rows, this -> cols, matrix -> rows, matrix -> cols);

    std::vector<double> resultVector((this -> rows) * (this -> cols));

    for(unsigned int i = 0; i < (this -> rows) * (this -> cols); ++i)
        resultVector[i] = (this -> vector[i]) * (matrix -> vector[i]);

    return Matrix(this -> rows, this -> cols, resultVector);
}

Matrix Matrix::mul(Matrix* matrix, bool broadcast)
{
    if(!broadcast || (this -> rows == matrix -> rows && this -> cols == matrix -> cols))
        return this -> mul(matrix);

    if((this -> rows != matrix -> rows && this -> cols != matrix -> cols)
    ||
    (this -> rows != 1 && this -> cols != 1 && matrix -> rows != 1 && matrix -> cols != 1))
        throwCustomMismatchDimensionsError("Neither Matrice could not be broadcast.\n"
        "Atleast one of the dimensions should be same and the other dimension of the smaller matrix should be 1.", 
        this -> rows, this -> cols, matrix -> rows, matrix -> cols);

    unsigned int resultRows = std::max(this -> rows, matrix -> rows);
    unsigned int resultCols = std::max(this -> cols, matrix -> cols);

    std::vector<double> resultVector(resultRows * resultCols);

    for (unsigned int i = 0; i < resultRows; ++i) 
    {
        for (unsigned int j = 0; j < resultCols; ++j) 
        {
            unsigned int thisMatrixRow = (this -> rows == 1) ? 0 : i;
            unsigned int thisMatrixCol = (this -> cols == 1) ? 0 : j;
            unsigned int inputMatrixRow = (matrix -> rows == 1) ? 0 : i;
            unsigned int inputMatrixCol = (matrix -> cols == 1) ? 0 : j;

            resultVector[(i * resultCols) + j] = this -> vector[(thisMatrixRow * this -> cols) + thisMatrixCol] *
            matrix -> vector[(inputMatrixRow * matrix -> cols) + inputMatrixCol];
        }
    }

    return Matrix(resultRows, resultCols, resultVector);
}

Matrix Matrix::div(double value)
{
    std::vector<double> resultVector((this -> rows) * (this -> cols));

    for(unsigned int i = 0; i < (this -> rows) * (this -> cols); ++i)
            resultVector[i] = (this -> vector[i]) / value;

    return Matrix(this -> getRows(), this -> getCols(), resultVector);
}

Matrix Matrix::div(Matrix* matrix)
{
    if(this -> rows != matrix -> rows || this -> cols != matrix -> cols)
        throwMismatchDimensionsError(this -> rows, this -> cols, matrix -> rows, matrix -> cols);

    std::vector<double> resultVector((this -> rows) * (this -> cols));

    for(unsigned int i = 0; i < (this -> rows) * (this -> cols); ++i)
        resultVector[i] = (this -> vector[i]) / (matrix -> vector[i]);

    return Matrix(this -> rows, this -> cols, resultVector);
}

Matrix Matrix::div(Matrix* matrix, bool broadcast)
{
    if(!broadcast || (this -> rows == matrix -> rows && this -> cols == matrix -> cols))
        return this -> div(matrix);

    if((this -> rows != matrix -> rows && this -> cols != matrix -> cols)
    ||
    (this -> rows != 1 && this -> cols != 1 && matrix -> rows != 1 && matrix -> cols != 1))
        throwCustomMismatchDimensionsError("Neither Matrice could not be broadcast.\n"
        "Atleast one of the dimensions should be same and the other dimension of the smaller matrix should be 1.", 
        this -> rows, this -> cols, matrix -> rows, matrix -> cols);

    unsigned int resultRows = std::max(this -> rows, matrix -> rows);
    unsigned int resultCols = std::max(this -> cols, matrix -> cols);

    std::vector<double> resultVector(resultRows * resultCols);

    for (unsigned int i = 0; i < resultRows; ++i) 
    {
        for (unsigned int j = 0; j < resultCols; ++j) 
        {
            unsigned int thisMatrixRow = (this -> rows == 1) ? 0 : i;
            unsigned int thisMatrixCol = (this -> cols == 1) ? 0 : j;
            unsigned int inputMatrixRow = (matrix -> rows == 1) ? 0 : i;
            unsigned int inputMatrixCol = (matrix -> cols == 1) ? 0 : j;

            resultVector[(i * resultCols) + j] = this -> vector[(thisMatrixRow * this -> cols) + thisMatrixCol] /
            matrix -> vector[(inputMatrixRow * matrix -> cols) + inputMatrixCol];
        }
    }

    return Matrix(resultRows, resultCols, resultVector);
}

Matrix Matrix::dot(Matrix* matrix)
{
    if(this -> cols != matrix -> rows)
        throwCustomMismatchDimensionsError("Matrix Columns do not match with Input Matrix Rows", 
        this -> rows, this -> cols, matrix -> rows, matrix -> cols);

    std::vector<double> resultVector((this -> rows) * (matrix -> cols));

    for(unsigned int i = 0; i < this -> rows; i += dotMulBlockSize)
        for(unsigned int j = 0; j < matrix -> cols; j += dotMulBlockSize)
            for(unsigned int k = 0; k < this -> cols; k += dotMulBlockSize)
            {
                for(unsigned int x = i; x < std::min(i + dotMulBlockSize, this -> rows); ++x)
                    for(unsigned int y = j; y < std::min(j + dotMulBlockSize, matrix -> cols); ++y)
                        for(unsigned int z = k; z < std::min(k + dotMulBlockSize, this -> cols); ++z)
                        {
                            resultVector[(x * matrix -> cols) + y] += this -> vector[(x * this -> cols) + z] *
                            matrix -> vector[(z * matrix -> cols) + y];
                        }
            }

    return Matrix(this -> rows, matrix -> cols, resultVector);
}

Matrix Matrix::transpose()
{
    std::vector<double> resultVector((this -> rows) * (this -> cols));

    for(unsigned int i = 0; i < this -> rows; ++i)
        for(unsigned int j = 0; j < this -> cols; ++j)
            resultVector[(j * this -> rows) + i] = this -> vector[(i * this -> cols) + j];

    return Matrix(this -> cols, this -> rows, resultVector);
}