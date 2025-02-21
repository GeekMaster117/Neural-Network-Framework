#include "utils.h"

#include <stdexcept>

void throwMismatchDimensionsError(int row1, int col1, int row2, int col2)
{
    throw std::invalid_argument("Matrice Dimensions do not match "
        "(" + std::to_string(row1) + ", " + std::to_string(col1) + ") "
        "(" + std::to_string(row2) + ", " + std::to_string(col2) + ")");
}

void throwCustomMismatchDimensionsError(std::string message1, int row1, int col1, int row2, int col2)
{
    throw std::invalid_argument(message1 + " "
        "(" + std::to_string(row1) + ", " + std::to_string(col1) + ") "
        "(" + std::to_string(row2) + ", " + std::to_string(col2) + ")");
}