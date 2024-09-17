#ifndef ARRAY_OPERATIONS_H
#define ARRAY_OPERATIONS_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <list> // For std::list

using namespace std;

template <typename Item_Type>
struct Node {
    Item_Type data;
    Node* prev;
    Node* next;

    Node(const Item_Type& item, Node* prev = nullptr, Node* next = nullptr)
        : data(item), prev(prev), next(next) {}
};

template <typename Item_Type>
class Link_List {
public:
    // Constructor and Destructor
    Link_List();
    Link_List(const Link_List& other);
    ~Link_List();

    // List operations
    void remove(const Item_Type& item);
    void push_front(const Item_Type& item);
    void push_back(const Item_Type& item);
    void pop_front();
    void pop_back();
    typename list<Item_Type>::iterator begin();
    typename list<Item_Type>::iterator erase(typename list<Item_Type>::iterator pos);
    typename list<Item_Type>::iterator insert(typename list<Item_Type>::iterator pos, const Item_Type& item);
    typename list<Item_Type>::const_iterator begin() const;
    typename list<Item_Type>::iterator end();
    typename list<Item_Type>::const_iterator end() const;

    // Accessors
    Item_Type& front();
    const Item_Type& front() const;
    Item_Type& back();
    const Item_Type& back() const;

    // Utility functions
    void swap(Link_List<Item_Type>& other);
    bool empty() const;
    size_t size() const;

    void delete_before(Node<Item_Type>* head, Node<Item_Type>* given);

private:
    Node<Item_Type>* head;
    Node<Item_Type>* tail;
    size_t num_items;
};

#endif // ARRAY_OPERATIONS_H
