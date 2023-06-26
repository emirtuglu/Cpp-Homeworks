#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

template <class T>
class LinkedList {
    private:
        Node<T>* headPtr;
        
    public:
        LinkedList();
        ~LinkedList();
        Node<T>* getHead() const;
        Node<T>* getNodeAt(int index) const;
        bool isEmpty() const;
        int getLength() const;
        bool add(T aData);
        bool remove(int index);
        bool exists(T aData) const;
        int indexOf(T aData) const;
};


template<class T>
LinkedList<T>::LinkedList() {
    this->headPtr = nullptr;
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node<T>* curr = this->headPtr;
    while (curr != nullptr) {
        Node<T>* next = curr->next;
        delete curr;
        curr = next;
    }
}

template<class T>
Node<T>* LinkedList<T>::getHead() const {
    return this->headPtr;
}

template<class T>
Node<T>* LinkedList<T>::getNodeAt(int index) const {
    if (this->isEmpty()) {
        return nullptr;
    }
    if (this->getLength() <= index || index < 0) {
        return nullptr;
    }
    int counter = 0;
    Node<T>* curr = this->headPtr;
    while (counter < index) {
        curr = curr->next;
        counter++;
    }
    return curr;
} 

template<class T>
bool LinkedList<T>::isEmpty() const {
    return this->headPtr == nullptr;
}

template<class T>
int LinkedList<T>::getLength() const {
    if (this->isEmpty()) {
        return 0;
    }
    int length = 0;
    Node<T>* curr = this->headPtr;
    while (curr != nullptr) {
        curr = curr->next;
        length++;
    }
    return length;
}


template<class T>
bool LinkedList<T>::add(T aData) {
    Node<T>* newNode = new Node<T>(aData, this->headPtr);
    this->headPtr = newNode;
    return true;
}

template<class T>
bool LinkedList<T>::remove(int index) {
    if (this->getNodeAt(index) == nullptr) {
        return false;
    }

    // index = 0 case
    if (index == 0) {
        Node<T>* temp = this->headPtr;
        this->headPtr = this->headPtr->next;
        delete temp;
        return true;
    }

    // index = 1 case
    if (index == 1) {
        Node<T>* temp = this->headPtr->next;
        this->headPtr->next = this->headPtr->next->next;
        delete temp;
        return true;
    }

    // other cases
    Node<T>* prev = this->getNodeAt(index - 1);
    Node<T>* curr = this->getNodeAt(index);
    prev->next = curr->next;
    delete curr;
    return true;
}

template<class T>
bool LinkedList<T>::exists(T aData) const {
    if (this->isEmpty()) { 
        return false;
    }
    Node<T>* curr = this->headPtr;
    while (curr != nullptr) {
        if (curr->data == aData) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template<class T>
int LinkedList<T>::indexOf(T aData) const {
    if (!this->exists(aData)) {
        return -1;
    }
    int index = 0;
    Node<T>* curr = this->headPtr;
    while (curr != nullptr) {
        if (curr->data == aData) {
            return index;
        }
        curr = curr->next;
        index++;
    }
    return index;
}


#endif
