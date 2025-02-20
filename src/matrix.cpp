#include <iostream>
#include <vector>
#include <stdexcept>

#include "utils.h"

class Matrix
{
    private:
        int rows, cols;
        std::vector<std::vector<double>> matrix;

    public:
        Matrix(int rows, int cols): rows(rows), cols(cols), matrix(rows, std::vector<double>(cols, 0.00)) {}

        Matrix(int rows, int cols, std::vector<std::vector<double>> vector): rows(rows), cols(cols), matrix(rows, std::vector<double>(cols, 0.00))
        {
            this -> inputData(vector);
        }

        std::vector<std::vector<double>> getVector()
        {
            return this -> matrix;
        }

        double getValue(int row, int col)
        {
            return this -> matrix[row][col];
        }

        void inputData(std::vector<std::vector<double>>& matrix)
        {
            if(static_cast<size_t>(this -> rows) != matrix.size() || static_cast<size_t>(this -> cols) != matrix[0].size())
                throw std::invalid_argument("Input Matrix Dimensions "
                "(" + std::to_string(matrix.size()) + ", " + std::to_string(matrix[0].size()) + ")"
                " do not match with Matrix Dimensions"
                "(" + std::to_string(this -> rows) + ", " + std::to_string(this -> cols) + ")");

            this -> matrix = matrix;
        }

        void displayData()
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

        Matrix* add(Matrix* matrix)
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

        void dot(Matrix* matrix)
        {
            if(this -> cols != matrix -> rows)
                throw std::invalid_argument("Input Matrix Rows "
                "(" + std::to_string(rows) + ", " + "~)"
                " do not match with Matrix Columns"
                "(~" + ", " + std::to_string(this -> cols) + ")");

            
        }
};

int main()
{
    std::vector<std::vector<double>> vector1 = std::vector<std::vector<double>>(2, std::vector<double>(2, 0.00));
    std::vector<std::vector<double>> vector2 = std::vector<std::vector<double>>(2, std::vector<double>(2, 0.00));

    Matrix* matrix1 = new Matrix(2, 2);
    Matrix* matrix2 = new Matrix(2, 2);

    matrix1 -> inputData(vector1);
    matrix1 -> displayData();

    std::cout << std::endl;

    matrix2 -> inputData(vector2);
    matrix2 -> displayData();

    std::cout << std::endl;

    Matrix* sumMatrix = matrix1 -> add(matrix2);
    sumMatrix -> displayData();
    
    return 0;
}