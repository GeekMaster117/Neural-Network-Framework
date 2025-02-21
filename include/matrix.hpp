#include <vector>

#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix
{
    private:
        int rows, cols;
        std::vector<std::vector<double>> vector;
    public:
        Matrix(int rows, int cols);
        Matrix(int rows, int cols, std::vector<std::vector<double>> vector);
        
        int getRows();
        int getCols();
        std::vector<std::vector<double>> getVector();
        double getValue(int row, int col);

        void inputVector(std::vector<std::vector<double>>& vector);
        void fillMatrix(double number);

        void displayData();

        Matrix* add(Matrix* matrix);
        Matrix* add(Matrix* matrix, bool broadcast);
        Matrix* dot(Matrix* matrix);
        Matrix* transpose();
};

#endif