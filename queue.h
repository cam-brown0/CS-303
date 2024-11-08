#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* frontPtr;
    Node* rearPtr;
    size_t count;

public:
    Queue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}
    ~Queue();

    void push(T value);
    void pop();
    T front() const;
    size_t size() const;
    bool empty() const;

    void move_to_rear(); // Custom function to move the front element to the rear
};

// Destructor to clean up nodes
template <typename T>
Queue<T>::~Queue() {
    while (!empty()) {
        pop();
    }
}

// Adds an element to the rear
template <typename T>
void Queue<T>::push(T value) {
    Node* newNode = new Node(value);
    if (empty()) {
        frontPtr = rearPtr = newNode;
    } else {
        rearPtr->next = newNode;
        rearPtr = newNode;
    }
    count++;
}

// Removes the front element
template <typename T>
void Queue<T>::pop() {
    if (empty()) {
        cerr << "Queue is empty\n";
        return;
    }
    Node* temp = frontPtr;
    frontPtr = frontPtr->next;
    delete temp;
    count--;
}

// Returns the front element
template <typename T>
T Queue<T>::front() const {
    if (empty()) {
        throw runtime_error("Queue is empty");
    }
    return frontPtr->data;
}

// Returns the size of the queue
template <typename T>
size_t Queue<T>::size() const {
    return count;
}

// Checks if the queue is empty
template <typename T>
bool Queue<T>::empty() const {
    return count == 0;
}

// Moves the front element to the rear
template <typename T>
void Queue<T>::move_to_rear() {
    if (size() <= 1) return; // No need to move if only one or no elements
    T frontValue = front();
    pop();
    push(frontValue);
}

#endif
