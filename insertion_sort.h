#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <vector>
using namespace std;

template <typename T>
void insertion_sort(vector<T>& arr) {
    for (size_t j = 1; j < arr.size(); j++) {
        T key = arr[j];
        int i = j - 1;
        while (i >= 0 && arr[i] > key) {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}

#endif
