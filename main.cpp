#include <iostream>
#include "Queue.h"
#include "linear_search.cpp" // For template instantiation
#include "insertion_sort.h"

using namespace std;

int main() {
    // Queue operations
    Queue<int> q;
    for (int i = 1; i <= 10; ++i) {
        q.push(i);
    }

    cout << "Queue contents:\n";
    // Display elements by popping them out one by one
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();  // Pop each element after displaying it
    }
    cout << endl;

    // Refill the queue for testing move_to_rear functionality
    for (int i = 1; i <= 10; ++i) {
        q.push(i);
    }

    // Demonstrate move_to_rear: Move the front element to the rear once
    cout << "\nQueue contents after moving front element to rear once:\n";
    q.move_to_rear();
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    // Linear search for the last occurrence
    vector<int> vec = {1, 2, 3, 4, 5, 2, 6, 2, 7};
    int target = 2;
    int last_occurrence = linear_search_last(vec, target, 0);
    cout << "Last occurrence of " << target << " is at index: " << last_occurrence << endl;

    // Insertion sort
    vector<int> arr = {9, 7, 5, 11, 12, 2, 14, 3, 10, 6};
    insertion_sort(arr);
    cout << "Sorted array:\n";
    for (const auto& val : arr) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
