#ifndef ARRAY_OPERATIONS_H
#define ARRAY_OPERATIONS_H

#include <iostream>
#include <fstream>
#include <array>
#include <stdexcept>

const int ARRAY_SIZE = 150; // Fixed size of the array

// Function prototypes
bool readNumbersFromFile(const std::string& filename, std::array<int, ARRAY_SIZE>& numbers, int& currentSize);
void printNumbers(const std::array<int, ARRAY_SIZE>& numbers, int currentSize);
int findIndexOfInteger(const std::array<int, ARRAY_SIZE>& numbers, int target, int currentSize);
void modifyValueAtIndex(std::array<int, ARRAY_SIZE>& numbers, int index, int newValue);
bool addIntegerToEnd(std::array<int, ARRAY_SIZE>& numbers, int& currentSize, int newValue);
void replaceOrRemoveAtIndex(std::array<int, ARRAY_SIZE>& numbers, int& currentSize, int index, bool remove);

#endif // ARRAY_OPERATIONS_H
