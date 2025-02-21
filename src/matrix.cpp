#include "matrix.hpp"

#include <iostream>
#include <vector>
#include <stdexcept>

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols), matrix(rows, std::vector<double>(cols, 0.00)) {}

Matrix::Matrix(int rows, int cols, std::vector<std::vector<double>> vector): rows(rows), cols(cols), matrix(rows, std::vector<double>(cols, 0.00))
{
    this -> inputVector(vector);
}

std::vector<std::vector<double>> Matrix::getVector()
{
    return this -> matrix;
}

double Matrix::getValue(int row, int col)
{
    return this -> matrix[row][col];
}

void Matrix::inputVector(std::vector<std::vector<double>>& matrix)
{
    if(static_cast<size_t>(this -> rows) != matrix.size() || static_cast<size_t>(this -> cols) != matrix[0].size())
        throw std::invalid_argument("Input Matrix Dimensions "
        "(" + std::to_string(matrix.size()) + ", " + std::to_string(matrix[0].size()) + ")"
        " do not match with Matrix Dimensions"
        "(" + std::to_string(this -> rows) + ", " + std::to_string(this -> cols) + ")");

    this -> matrix = matrix;
}

void Matrix::fillMatrix(double number)
{
    for(int i = 0; i < this -> rows; ++i)
        for(int j = 0; j < this -> cols; ++j)
            this -> matrix[i][j] = number;
}

void Matrix::displayData()
{
    for (std::vector<double>& row : this -> matrix)
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
            resultVector[i][j] += matrix -> getValue(i, j);

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
                resultVector[i][j] += this -> getValue(i, k) * matrix -> getValue(k, j);

    return new Matrix(this -> rows, matrix -> cols, resultVector);
}