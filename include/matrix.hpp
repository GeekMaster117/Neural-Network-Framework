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
        Matrix();
        Matrix(unsigned int rows, unsigned int cols);
        Matrix(unsigned int rows, unsigned int cols, std::vector<std::vector<double>>& vector);
        
        unsigned int getRows();
        unsigned int getCols();

        std::vector<std::vector<double>> getVector();
        double getValue(unsigned int row, unsigned int col);

        void inputVector(std::vector<std::vector<double>>& vector);
        void fillMatrix(double value);

        void displayData();
        
        Matrix add(double value);
        Matrix add(Matrix* matrix);
        Matrix add(Matrix* matrix, bool broadcast);

        Matrix sub(double value);
        Matrix sub(Matrix* matrix);
        Matrix sub(Matrix* matrix, bool broadcast);

        Matrix mul(double value);
        Matrix mul(Matrix* matrix);
        Matrix mul(Matrix* matrix, bool broadcast);

        Matrix div(double value);
        Matrix div(Matrix* matrix);
        Matrix div(Matrix* matrix, bool broadcast);

        Matrix dot(Matrix* matrix);

        Matrix transpose();
};

#endif