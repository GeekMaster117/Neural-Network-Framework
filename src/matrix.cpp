#include <iostream>
#include <stdexcept>

#include "utils.h"

class Matrix
{
    private:
        double** arr;
        int rows, cols;

    public:
        Matrix(int r, int c): rows(r), cols(c)
        {
            this -> arr = new double*[rows];
            for(int i = 0; i < rows; ++i)
                this -> arr[i] = new double[cols];
        }

        void inputData(double** arr, int rows, int cols)
        {
            if(this -> rows != rows || this -> cols != cols)
                throw std::invalid_argument("Input Matrix Dimensions "
                "(" + std::to_string(rows) + ", " + std::to_string(cols) + ")"
                " do not match with Matrix Dimensions"
                "(" + std::to_string(this -> rows) + ", " + std::to_string(this -> cols) + ")");

            for(int i = 0; i < rows; ++i)
                for(int j = 0; j < cols; ++j)
                    this -> arr[i][j] = arr[i][j];
        }

        void displayData()
        {
            for(int i = 0; i < rows; ++i)
            {
                std::cout << this -> arr[i][0];
                for(int j = 1; j < cols; ++j)
                    std::cout << ", " << this -> arr[i][j];
                std::cout << std::endl;
            }
        }

        void add(Matrix* matrix)
        {
            if(this -> rows != matrix -> rows || this -> cols != matrix -> cols)
                throw std::invalid_argument("Matrix Dimensions do not match");

            for(int i = 0; i < this -> rows; ++i)
                for(int j = 0; j < this -> cols; ++j)
                    this -> arr[i][j] += matrix -> arr[i][j];
        }
};

int main()
{
    double** arr1 = new double*[2];
    double** arr2 = new double*[2];
    for (int i = 0; i < 2; ++i)
    {
        arr1[i] = new double[2];
        arr2[i] = new double[2];
    }

    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)
        {
            arr1[i][j] = 1.00;
            arr2[i][j] = 1.00;
        }

    Matrix* matrix1 = new Matrix(2, 2);
    Matrix* matrix2 = new Matrix(2, 2);

    matrix1 -> inputData(arr1, 2, 2);
    matrix1 -> displayData();

    std::cout << std::endl;

    matrix2 -> inputData(arr2, 2, 2);
    matrix2 -> displayData();

    std::cout << std::endl;

    matrix1 -> add(matrix2);
    matrix1 -> displayData();
    
    return 0;
}