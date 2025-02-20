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
                "(" + std::to_string(rows) + ", " + std::to_string(cols) + ")"
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

        void add(Matrix* matrix)
        {
            if(this -> rows != matrix -> rows || this -> cols != matrix -> cols)
                throw std::invalid_argument("Matrix Dimensions do not match");

            for(int i = 0; i < this -> rows; ++i)
                for(int j = 0; j < this -> cols; ++j)
                    this -> matrix[i][j] += matrix -> getValue(i, j);
        }
};

int main()
{
    std::vector<std::vector<double>> vector1 = std::vector<std::vector<double>>(2, std::vector<double>(2, 0.00));
    std::vector<std::vector<double>> vector2 = std::vector<std::vector<double>>(2, std::vector<double>(2, 0.00));

    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)
        {
            vector1[i][j] = 1.00;
            vector2[i][j] = 2.00;
        }

    Matrix* matrix1 = new Matrix(2, 2);
    Matrix* matrix2 = new Matrix(2, 2);

    matrix1 -> inputData(vector1);
    matrix1 -> displayData();

    std::cout << std::endl;

    matrix2 -> inputData(vector2);
    matrix2 -> displayData();

    std::cout << std::endl;

    matrix1 -> add(matrix2);
    matrix1 -> displayData();
    
    return 0;
}