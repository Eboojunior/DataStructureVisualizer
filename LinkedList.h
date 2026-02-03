#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <vector>

struct Node {
    int data;
    Node* next;
    
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    int size;

public:
    LinkedList();
    ~LinkedList();
    
    void insert(int value);
    void remove();
    void clear();
    bool isEmpty() const;
    int getSize() const;
    
    // For visualization
    std::vector<int> getValues() const;
    Node* getHead() const { return head; }
};

#endif
