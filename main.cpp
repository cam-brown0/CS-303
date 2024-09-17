#include "Link_List.h" // Includes the header file for the Link_List class

using namespace std;

#include "stack_operations.cpp" // Includes the stack operations code (not shown in this snippet)

int main() {
    // Step 1: Create a stack object
    // Create an instance of the Stack class, which will be used to perform stack operations.
    Stack myStack;

    // Step 2: Check if the stack is empty
    // The 'isEmpty()' method checks if the stack contains any elements.
    // It returns true if empty and false otherwise.
    cout << "Is the stack empty? " << (myStack.isEmpty() ? "Yes" : "No") << endl;

    // Step 3: Insert some integer values onto the stack
    // The 'push()' method adds elements to the stack.
    // Elements 10, 20, 30, and 40 are pushed onto the stack in sequence.
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);
    myStack.push(40);

    // Step 2 (again): Check if the stack is empty after inserting elements
    // The stack should no longer be empty since elements have been added.
    cout << "Is the stack empty? " << (myStack.isEmpty() ? "Yes" : "No") << endl;

    // Step 4: Remove an element from the stack
    // The 'pop()' method removes the top element from the stack (last-in element).
    // This removes the most recently added element (40).
    myStack.pop();

    // Step 5: Find the top element of the stack
    // The 'top()' method retrieves the value of the top element without removing it.
    // A try-catch block is used to handle potential errors, such as attempting to get the top element from an empty stack.
    try {
        cout << "Top of the stack: " << myStack.top() << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    // Step 6: Find the average value of the stack elements
    // The 'average()' method calculates the average of the values currently on the stack.
    // A try-catch block handles the case where the stack is empty.
    try {
        cout << "Average value of stack elements: " << myStack.average() << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0; // Program ends successfully
}

// ---- Link_List Class Implementation ----

// Constructor
// Initializes an empty linked list by setting head and tail pointers to nullptr and num_items to 0.
template <typename Item_Type>
Link_List<Item_Type>::Link_List() : head(nullptr), tail(nullptr), num_items(0) {}

// Copy Constructor
// Copies another linked list by iterating through its elements and pushing each element to the back of the new list.
template <typename Item_Type>
Link_List<Item_Type>::Link_List(const Link_List& other) : head(nullptr), tail(nullptr), num_items(0) {
    for (auto itr = other.begin(); itr != other.end(); ++itr) {
        push_back(*itr);
    }
}

// Destructor
// Deletes all nodes in the list, ensuring memory is released by iterating through the nodes and deleting each one.
template <typename Item_Type>
Link_List<Item_Type>::~Link_List() {
    while (head != nullptr) {
        Node<Item_Type>* current = head;
        head = head->next;
        delete current; // Delete current node
    }
    tail = nullptr; // Set tail to nullptr
    num_items = 0;  // Reset number of items to 0
}

// Deletes the node before the given node
// This method removes the node that directly precedes the 'given' node in the list.
// It handles several special cases: if the list is empty, only one node exists, or 'given' is the head.
template <typename Item_Type>
void Link_List<Item_Type>::delete_before(Node<Item_Type>* head, Node<Item_Type>* given) {
    if (head == nullptr || head->next == nullptr || head == given)
        throw runtime_error("Cannot delete the node"); // Special case checks

    if (head->next == given) {
        // If 'head' is the node directly before 'given', delete 'head'.
        Node<Item_Type>* tmp = head;
        head = head->next; // Move head forward
        delete tmp;        // Delete the node
        return;
    }

    Node<Item_Type>* current_node = head;
    while (current_node->next != nullptr) {
        if (current_node->next->next == given) {
            // If the node before 'given' is found, delete it.
            Node<Item_Type>* to_be_deleted = current_node->next;
            current_node->next = current_node->next->next;
            delete to_be_deleted;
            return;
        }
        current_node = current_node->next; // Traverse to the next node
    }
}

// Remove an element from the list
// (The logic for this function is left to be implemented by the user)
template <typename Item_Type>
void Link_List<Item_Type>::remove(const Item_Type& item) {
    // Implement the remove logic here
}

// Insert a new element at the front of the list
// This method adds a new node with 'item' at the front of the list and adjusts the head pointer.
template <typename Item_Type>
void Link_List<Item_Type>::push_front(const Item_Type& item) {
    head = new Node<Item_Type>(item, nullptr, head); // Create a new node as the new head
    if (head->next != nullptr)
        head->next->prev = head; // Link back to the new head
    if (tail == nullptr)
        tail = head; // If the list was empty, the new node becomes both head and tail
    num_items++; // Increment the item count
}

// Insert a new element at the back of the list
// Adds a new node at the end (tail) of the list.
template <typename Item_Type>
void Link_List<Item_Type>::push_back(const Item_Type& item) {
    if (tail != nullptr) {
        // If there is a tail, link the new node to it and update the tail.
        tail->next = new Node<Item_Type>(item, tail, nullptr);
        tail = tail->next;
        num_items++;
    } else {
        // If the list is empty, use push_front to add the first node.
        push_front(item);
    }
}

// Remove the first element from the list
// This method deletes the head node and moves the head pointer to the next node.
template <typename Item_Type>
void Link_List<Item_Type>::pop_front() {
    if (head == nullptr)
        throw invalid_argument("Attempt to call pop_front() on an empty list");

    Node<Item_Type>* removed_node = head; // Save the current head
    head = head->next; // Move head to the next node
    delete removed_node; // Delete the old head

    if (head != nullptr)
        head->prev = nullptr; // Update the new head's previous pointer
    else
        tail = nullptr; // If the list becomes empty, set tail to nullptr
    num_items--; // Decrement the item count
}

// Remove the last element from the list
// This method deletes the tail node and moves the tail pointer to the previous node.
template <typename Item_Type>
void Link_List<Item_Type>::pop_back() {
    if (tail == nullptr)
        throw invalid_argument("Attempt to call pop_back() on an empty list");

    Node<Item_Type>* removed_node = tail; // Save the current tail
    tail = tail->prev; // Move tail to the previous node
    delete removed_node; // Delete the old tail

    if (tail != nullptr)
        tail->next = nullptr; // Update the new tail's next pointer
    else
        head = nullptr; // If the list becomes empty, set head to nullptr
    num_items--; // Decrement the item count
}
