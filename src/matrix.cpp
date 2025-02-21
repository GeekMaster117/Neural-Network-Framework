#include "matrix.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols), vector(rows, std::vector<double>(cols, 0.00)) {}

Matrix::Matrix(int rows, int cols, std::vector<std::vector<double>> vector): rows(rows), cols(cols), vector(rows, std::vector<double>(cols, 0.00))
{
    this -> inputVector(vector);
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
        throw std::invalid_argument("Input Matrix Dimensions "
        "(" + std::to_string(vector.size()) + ", " + std::to_string(vector[0].size()) + ")"
        " do not match with Matrix Dimensions"
        "(" + std::to_string(this -> rows) + ", " + std::to_string(this -> cols) + ")");

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
        throw std::invalid_argument("Input Matrix Dimensions "
        "(" + std::to_string(matrix -> rows) + ", " + std::to_string(matrix -> cols) + ")"
        " do not match with Matrix Dimensions"
        "(" + std::to_string(this -> rows) + ", " + std::to_string(this -> cols) + ")");

    std::vector<std::vector<double>> resultVector = std::vector<std::vector<double>>(this -> rows, std::vector<double>(this -> cols, 0.00));

    for(int i = 0; i < this -> rows; ++i)
        for(int j = 0; j < this -> cols; ++j)
            resultVector[i][j] += matrix -> vector[i][j];

    return new Matrix(this -> rows, this -> cols, resultVector);
}

Matrix* Matrix::dot(Matrix* matrix)
{
    if(this -> cols != matrix -> rows)
        throw std::invalid_argument("Input Matrix Rows "
        "(" + std::to_string(rows) + ", " + "~)"
        " do not match with Matrix Columns"
        "(~" + ", " + std::to_string(this -> cols) + ")");

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