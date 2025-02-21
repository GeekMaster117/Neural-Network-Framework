#include <iostream>

#ifndef UTILS_H
#define UTILS_H

void throwMismatchDimensionsError(int row1, int col1, int row2, int col2);
void throwCustomMismatchDimensionsError(std::string message, int row1, int col1, int row2, int col2);

#endif