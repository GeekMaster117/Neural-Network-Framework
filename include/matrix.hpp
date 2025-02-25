#include <vector>

#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix
{
    private:
        unsigned int rows, cols;
        std::vector<double> vector;

        Matrix(unsigned int rows, unsigned int cols, std::vector<double>& vector);
    public:
        Matrix(unsigned int rows, unsigned int cols);
        Matrix(unsigned int rows, unsigned int cols, std::vector<std::vector<double>>& vector);
        
        unsigned int getRows();
        unsigned int getCols();
        std::vector<std::vector<double>> getVector();
        double getValue(unsigned int row, unsigned int col);

        void inputVector(std::vector<std::vector<double>>& vector);
        void fillMatrix(double value);

        void displayData();
        
        Matrix add(Matrix* matrix);
        Matrix add(Matrix* matrix, bool broadcast);
        Matrix dot(Matrix* matrix);
        Matrix transpose();
};

#endif