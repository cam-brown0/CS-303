#include "array_operations.h"

using namespace std;

// Constructor
template <typename Item_Type>
Link_List<Item_Type>::Link_List() : head(nullptr), tail(nullptr), num_items(0) {}

// Copy constructor
template <typename Item_Type>
Link_List<Item_Type>::Link_List(const Link_List& other) : head(nullptr), tail(nullptr), num_items(0) {
    for (auto itr = other.begin(); itr != other.end(); ++itr) {
        push_back(*itr);
    }
}

// Destructor
template <typename Item_Type>
Link_List<Item_Type>::~Link_List() {
    while (head != nullptr) {
        Node<Item_Type>* current = head;
        head = head->next;
        delete current;
    }
    tail = nullptr;
    num_items = 0;
}

// Deletes the node before the given node
template <typename Item_Type>
void Link_List<Item_Type>::delete_before(Node<Item_Type>* head, Node<Item_Type>* given) {
    if (head == nullptr || head->next == nullptr || head == given)
        throw runtime_error("Cannot delete the node");
    if (head->next == given) {
        Node<Item_Type>* tmp = head;
        head = head->next;
        delete tmp;
        return;
    }

    Node<Item_Type>* current_node = head;
    while (current_node->next != nullptr) {
        if (current_node->next->next == given) {
            Node<Item_Type>* to_be_deleted = current_node->next;
            current_node->next = current_node->next->next;
            delete to_be_deleted;
            return;
        }
        current_node = current_node->next;
    }
}

template <typename Item_Type>
void Link_List<Item_Type>::remove(const Item_Type& item) {
    // Implement the remove logic
}

template <typename Item_Type>
void Link_List<Item_Type>::push_front(const Item_Type& item) {
    head = new Node<Item_Type>(item, nullptr, head);
    if (head->next != nullptr)
        head->next->prev = head;
    if (tail == nullptr)
        tail = head;
    num_items++;
}

template <typename Item_Type>
void Link_List<Item_Type>::push_back(const Item_Type& item) {
    if (tail != nullptr) {
        tail->next = new Node<Item_Type>(item, tail, nullptr);
        tail = tail->next;
        num_items++;
    } else {
        push_front(item);
    }
}

template <typename Item_Type>
void Link_List<Item_Type>::pop_front() {
    if (head == nullptr)
        throw invalid_argument("Attempt to call pop_front() on an empty list");

    Node<Item_Type>* removed_node = head;
    head = head->next;
    delete removed_node;

    if (head != nullptr)
        head->prev = nullptr;
    else
        tail = nullptr;
    num_items--;
}

template <typename Item_Type>
void Link_List<Item_Type>::pop_back() {
    if (tail == nullptr)
        throw invalid_argument("Attempt to call pop_back() on an empty list");

    Node<Item_Type>* removed_node = tail;
    tail = tail->prev;
    delete removed_node;

    if (tail != nullptr)
        tail->next = nullptr;
    else
        head = nullptr;
    num_items--;
}

template <typename Item_Type>
typename list<Item_Type>::iterator Link_List<Item_Type>::begin() {
    // Implement your logic for begin
}

template <typename Item_Type>
typename list<Item_Type>::iterator Link_List<Item_Type>::erase(typename list<Item_Type>::iterator pos) {
    if (empty())
        throw invalid_argument("Attempt to call erase on an empty list");

    if (pos == end())
        throw invalid_argument("Attempt to call erase at end()");

    typename list<Item_Type>::iterator return_value = pos;
    ++return_value;

    if (pos == head) {
        pop_front();
        return return_value;
    } else if (pos == tail) {
        pop_back();
        return return_value;
    } else {
        Node<Item_Type>* removed_node = pos.current;
        removed_node->prev->next = removed_node->next;
        removed_node->next->prev = removed_node->prev;
        delete removed_node;
        return return_value;
    }
}

template <typename Item_Type>
typename list<Item_Type>::iterator Link_List<Item_Type>::insert(typename list<Item_Type>::iterator pos, const Item_Type& item) {
    if (pos == begin()) {
        push_front(item);
        return begin();
    } else if (pos == end()) {
        push_back(item);
        return typename list<Item_Type>::iterator(this, tail);
    }

    Node<Item_Type>* new_node = new Node<Item_Type>(item, pos.current->prev, pos.current);
    pos.current->prev->next = new_node;
    pos.current->prev = new_node;
    num_items++;
    return typename list<Item_Type>::iterator(this, new_node);
}

template <typename Item_Type>
bool Link_List<Item_Type>::empty() const {
    return num_items == 0;
}

template <typename Item_Type>
size_t Link_List<Item_Type>::size() const {
    return num_items;
}

template <typename Item_Type>
Item_Type& Link_List<Item_Type>::front() {
    if (head == nullptr)
        throw invalid_argument("Attempt to access front() of empty list");
    return head->data;
}

template <typename Item_Type>
const Item_Type& Link_List<Item_Type>::front() const {
    if (head == nullptr)
        throw invalid_argument("Attempt to access front() of empty list");
    return head->data;
}

template <typename Item_Type>
Item_Type& Link_List<Item_Type>::back() {
    if (tail == nullptr)
        throw invalid_argument("Attempt to access back() of empty list");
    return tail->data;
}

template <typename Item_Type>
const Item_Type& Link_List<Item_Type>::back() const {
    if (tail == nullptr)
        throw invalid_argument("Attempt to access back() of empty list");
    return tail->data;
}

template <typename Item_Type>
void Link_List<Item_Type>::swap(Link_List<Item_Type>& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(num_items, other.num_items);
}
