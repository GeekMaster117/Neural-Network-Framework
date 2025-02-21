#include "matrix.hpp"

#include <iostream>
#include <vector>

#include "utils.h"

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols), vector(rows, std::vector<double>(cols, 0.00)) {}

Matrix::Matrix(int rows, int cols, std::vector<std::vector<double>> vector): rows(rows), cols(cols), vector(rows, std::vector<double>(cols, 0.00))
{
    this -> inputVector(vector);
}

int Matrix::getRows()
{
    return this -> rows;
}

int Matrix::getCols()
{
    return this -> cols;
}

std::vector<std::vector<double>> Matrix::getVector()
{
    return this -> vector;
}

double Matrix::getValue(int row, int col)
{
    return this -> vector[row][col];
}

void Matrix::inputVector(std::vector<std::vector<double>>& vector)
{
    if(static_cast<size_t>(this -> rows) != vector.size() || static_cast<size_t>(this -> cols) != vector[0].size())
        throwMismatchDimensionsError(this -> rows, this -> cols, vector.size(), vector[0].size());

    this -> vector = vector;
}

void Matrix::fillMatrix(double number)
{
    for(int i = 0; i < this -> rows; ++i)
        for(int j = 0; j < this -> cols; ++j)
            this -> vector[i][j] = number;
}

void Matrix::displayData()
{
    for (std::vector<double>& row : this -> vector)
    {
        if (!row.empty())
        {
            std::cout << row[0];
            for (int i = 1; i < this -> cols; ++i)
                std::cout << ", " << row[i];
        }
        std::cout << std::endl;
    }
}

Matrix* Matrix::add(Matrix* matrix)
{
    if(this -> rows != matrix -> rows || this -> cols != matrix -> cols)
        throwMismatchDimensionsError(this -> rows, this -> cols, matrix -> rows, matrix -> cols);

    std::vector<std::vector<double>> resultVector = std::vector<std::vector<double>>(this -> rows, std::vector<double>(this -> cols, 0.00));

    for(int i = 0; i < this -> rows; ++i)
        for(int j = 0; j < this -> cols; ++j)
            resultVector[i][j] += matrix -> vector[i][j];

    return new Matrix(this -> rows, this -> cols, resultVector);
}

Matrix* Matrix::add(Matrix* matrix, bool broadcast)
{
    if(!broadcast || (this -> rows == matrix -> rows && this -> cols == matrix -> cols))
        return this -> add(matrix);

    if((this -> rows != matrix -> rows && this -> cols != matrix -> cols)
    ||
    (this -> rows != 1 && this -> cols != 1 && matrix -> rows != 1 && matrix -> cols != 1))
        throwCustomMismatchDimensionsError("Neither Matrice could not be broadcast.\n"
        "Atleast one of the dimensions should be same and the other dimension of the smaller matrix should be 1.", 
        this -> rows, this -> cols, matrix -> rows, matrix -> cols);

    int resultRows = std::max(this -> rows, matrix -> rows);
    int resultCols = std::max(this -> cols, matrix -> cols);

    std::vector<std::vector<double>> resultVector = std::vector<std::vector<double>>(resultRows, std::vector<double>(resultCols, 0.00));

    for (int i = 0; i < resultRows; i++) 
    {
        for (int j = 0; j < resultCols; j++) 
        {
            int thisMatrixRow = (this -> rows == 1) ? 0 : i;
            int thisMatrixCol = (this -> cols == 1) ? 0 : j;
            int inputMatrixRow = (matrix -> rows == 1) ? 0 : i;
            int inputMatrixCol = (matrix -> cols == 1) ? 0 : j;

            resultVector[i][j] = this -> getValue(thisMatrixRow, thisMatrixCol) + matrix -> getValue(inputMatrixRow, inputMatrixCol);
        }
    }

    return new Matrix(resultRows, resultCols, resultVector);
}

Matrix* Matrix::dot(Matrix* matrix)
{
    if(this -> cols != matrix -> rows)
        throwCustomMismatchDimensionsError("First Matrix Columns do not match with Second Matrix Rows", 
        this -> rows, this -> cols, matrix -> rows, matrix -> cols);

    std::vector<std::vector<double>> resultVector = std::vector<std::vector<double>>(this -> rows, std::vector<double>(matrix -> cols, 0.00));

    for(int i = 0; i < this -> rows; ++i)
        for(int j = 0; j < matrix -> cols; ++j)
            for(int k = 0; k < this -> cols; ++k)
                resultVector[i][j] += this -> vector[i][k] * matrix -> vector[k][j];

    return new Matrix(this -> rows, matrix -> cols, resultVector);
}

Matrix* Matrix::transpose()
{
    std::vector<std::vector<double>> resultVector = std::vector<std::vector<double>>(this -> cols, std::vector<double>(this -> rows, 0.00));

    for(int i = 0; i < this -> rows; ++i)
        for(int j = 0; j < this -> cols; ++j)
            resultVector[j][i] = this -> vector[i][j];

    return new Matrix(this -> cols, this -> rows, resultVector);
}