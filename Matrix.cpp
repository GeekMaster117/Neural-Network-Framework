#include <iostream>
#include <stdexcept>

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
};

int main()
{
    double** arr = new double*[2];
    for (int i = 0; i < 2; ++i) 
        arr[i] = new double[2];

    arr[0][0] = 1.0; arr[0][1] = 2.0;
    arr[1][0] = 3.0; arr[1][1] = 4.0;

    Matrix* matrix = new Matrix(2, 2);

    try
    {
        matrix -> inputData(arr, 2, 2);
        matrix -> displayData();
    }
    catch(const std::exception& e)
    {
        std::cout << "Caught Exception: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}