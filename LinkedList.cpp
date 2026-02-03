#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() : head(nullptr), size(0) {}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::insert(int value) {
    Node* newNode = new Node(value);
    
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

void LinkedList::remove() {
    if (head == nullptr) return;
    
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    size--;
}

void LinkedList::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

bool LinkedList::isEmpty() const {
    return head == nullptr;
}

int LinkedList::getSize() const {
    return size;
}

std::vector<int> LinkedList::getValues() const {
    std::vector<int> values;
    Node* current = head;
    while (current != nullptr) {
        values.push_back(current->data);
        current = current->next;
    }
    return values;
}
