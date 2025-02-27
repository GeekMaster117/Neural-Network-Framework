#include <iostream>
#include <string>

#ifndef ERROR_H
#define ERROR_H

void throwMismatchDimensionsError(int row1, int col1, int row2, int col2);
void throwCustomMismatchDimensionsError(std::string message, int row1, int col1, int row2, int col2);

void throwFileCannotBeOpenedError(std::string filename);

void throwValueCannotBeGreaterError(int value, int threshold);

void throwDatasetEmptyError();

#endif