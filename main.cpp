#include "array_operations.h"

using namespace std;


int main() {
    array<int, ARRAY_SIZE> numbers = {}; // Initialize an array to hold 100 integers
    int currentSize = 0; // Track the number of valid integers in the array

    try {
        // Read numbers from the file
        if (!readNumbersFromFile("123.txt", numbers, currentSize)) {
            throw runtime_error("Failed to read numbers from file!");
        }

        // Print the numbers to verify
        printNumbers(numbers, currentSize);

        // Example usage of the new functions
        int target = 42;
        int index = findIndexOfInteger(numbers, target, currentSize);
        if (index != -1) {
            cout << "Number " << target << " found at index " << index << "." << endl;
        } else {
            cout << "Number " << target << " not found." << endl;
        }

        // Modify a value at a specific index with exception handling
        try {
            int indexToModify = 5; // Index 6 is the 5th index (0-based index)
            int newValue = 99;
            modifyValueAtIndex(numbers, indexToModify, newValue);
        } catch (out_of_range& e) {
            cout << "Error: " << e.what() << endl;
        }

        // Add a new integer to the end of the array if there is space
        try {
            if (addIntegerToEnd(numbers, currentSize, 123)) {
                cout << "Added new integer to the array." << endl;
            } else {
                throw runtime_error("Failed to add new integer, array is full.");
            }
        } catch (runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }

        // Replace or remove an integer at a specific index
        replaceOrRemoveAtIndex(numbers, currentSize, 10, true); // true means remove

        // Print the modified numbers
        cout << "Modified numbers:" << endl;
        printNumbers(numbers, currentSize);

    } catch (const exception& e) {
        cout << "An error occurred: " << e.what() << endl;
        return 1; // Exit with an error code
    }

    return 0; // Success
}

// Function to read numbers from a file into an array and update currentSize
bool readNumbersFromFile(const string& filename, array<int, ARRAY_SIZE>& numbers, int& currentSize) {
    ifstream file(filename); // Open the file

    if (!file) { // Check if the file was opened successfully
        cout << "Error opening file: " << filename << endl;
        return false; // Indicate failure
    }

    int number;
    currentSize = 0;

    // Read integers from the file into the array
    while (file >> number && currentSize < ARRAY_SIZE) {
        numbers[currentSize++] = number;
    }

    file.close(); // Close the file
    return true; // Indicate success
}

// Function to print numbers from an array
void printNumbers(const array<int, ARRAY_SIZE>& numbers, int currentSize) {
    cout << "Numbers read from file:" << endl;
    for (int i = 0; i < currentSize; ++i) {
        cout << numbers[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl; // Print in rows of 10
    }
    cout << endl;
}

// Function to find the index of a specific integer in the array
int findIndexOfInteger(const array<int, ARRAY_SIZE>& numbers, int target, int currentSize) {
    for (int i = 0; i < currentSize; ++i) {
        if (numbers[i] == target) {
            return i; // Return the index if found
        }
    }
    return -1; // Return -1 if not found
}

// Function to modify the value at a specific index
void modifyValueAtIndex(array<int, ARRAY_SIZE>& numbers, int index, int newValue) {
    if (index >= 0 && index < ARRAY_SIZE) {
        int oldValue = numbers[index];
        numbers[index] = newValue;
        cout << "Value at index " << index << " changed from " << oldValue << " to " << newValue << "." << endl;
    } else {
        throw out_of_range("Index out of bounds.");
    }
}

// Function to add a new integer to the end of the array
bool addIntegerToEnd(array<int, ARRAY_SIZE>& numbers, int& currentSize, int newValue) {
    if (currentSize < ARRAY_SIZE) {
        numbers[currentSize++] = newValue;
        return true; // Successfully added
    }
    return false; // Array is full
}

// Function to replace or remove an integer at a specific index
void replaceOrRemoveAtIndex(array<int, ARRAY_SIZE>& numbers, int& currentSize, int index, bool remove) {
    if (index >= 0 && index < currentSize) {
        if (remove) {
            // Move elements left to fill the gap
            for (int i = index; i < currentSize - 1; ++i) {
                numbers[i] = numbers[i + 1];
            }
            numbers[--currentSize] = 0; // Set the last element to 0 after shifting
        } else {
            numbers[index] = 0; // Replace with 0
        }
    } else {
        throw out_of_range("Index out of bounds.");
    }
}
