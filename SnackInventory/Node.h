#ifndef __NODE_H
#define __NODE_H
#include <iostream>

using namespace std;

template<class T>
class Node {
    public:
        T data;
        Node<T>* next;
        Node(T data = T(), Node<T>* next = nullptr) { 
            this->data = data; 
            this->next = next; 
        }
        T* getData() { return &(this->data); }
};


#endif
