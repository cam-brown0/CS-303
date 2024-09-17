#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate

using namespace std;

// Stack class using vector to store integers
class Stack {
private:
    vector<int> stack; // Vector to represent stack

public:
    // Check if the stack is empty
    bool isEmpty() const {
        return stack.empty();
    }

    // Push an integer onto the stack
    void push(int value) {
        stack.push_back(value);
        cout << "Pushed " << value << " onto the stack." << endl;
    }

    // Pop an integer from the stack
    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot pop." << endl;
        } else {
            int value = stack.back();
            stack.pop_back();
            cout << "Popped " << value << " from the stack." << endl;
        }
    }

    // Get the top element of the stack
    int top() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty. No top element.");
        }
        return stack.back();
    }

    // Get the average value of the stack elements
    double average() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty. No elements to calculate average.");
        }
        int sum = accumulate(stack.begin(), stack.end(), 0);
        return static_cast<double>(sum) / stack.size();
    }
};

int main() {
    // Step 1: Create a stack object
    Stack myStack;

    // Step 2: Check if the stack is empty
    cout << "Is the stack empty? " << (myStack.isEmpty() ? "Yes" : "No") << endl;

    // Step 3: Insert some integer values onto the stack
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);
    myStack.push(40);

    // Step 2 (again): Check if the stack is empty after inserting elements
    cout << "Is the stack empty? " << (myStack.isEmpty() ? "Yes" : "No") << endl;

    // Step 4: Remove an element from the stack
    myStack.pop();

    // Step 5: Find the top element of the stack
    try {
        cout << "Top of the stack: " << myStack.top() << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    // Step 6: Find the average value of the stack elements
    try {
        cout << "Average value of stack elements: " << myStack.average() << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
