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
        void sort();
        void print() const;
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
    this->sort();
    return true;
}

template<class T>
bool LinkedList<T>::remove(int index) {
    if (this->getNodeAt(index) == nullptr) {
        return false;
    }

    // Index == 0 case
    if (index == 0) {
        Node<T>* temp = this->headPtr;
        this->headPtr = this->headPtr->next;
        delete temp;
        return true;
    }

    // Index == 1 case
    if (index == 1) {
        Node<T>* temp = this->headPtr->next;
        this->headPtr->next = this->headPtr->next->next;
        delete temp;
        return true;
    }

    // Other cases
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

template<class T>
void LinkedList<T>::sort() {
    // Handle 0 or 1 element cases
    if (this->isEmpty() || this->getLength() == 1) {
        return;
    }

    // Handle 2 element case
    if (this->getLength() == 2) {
        if (this->getNodeAt(0)->data > this->getNodeAt(1)->data) {
            // Swap 0th and 1st element
            Node<T>* temp = this->getNodeAt(0);
            this->headPtr = this->getNodeAt(1);
            this->headPtr->next = temp;
            temp->next = nullptr;
        }
        return;
    }

    int length = this->getLength();
    // Use bubble sort algorithm to sort the linked list
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (this->getNodeAt(j)->data > this->getNodeAt(j+1)->data) {
                // Swap j and j+1
                Node<T>* tempJ = this->getNodeAt(j);
                Node<T>* tempJnext = this->getNodeAt(j+1);

                // Adjust pointers to swap nodes
                if (j == 0) {
                    this->headPtr = tempJnext;
                } else {
                    this->getNodeAt(j-1)->next = tempJnext;
                }
                tempJ->next = tempJnext->next;
                tempJnext->next = tempJ;
            }
        }
    }
}

template<class T>
void LinkedList<T>::print() const {
    int length = this->getLength();
    for (int i = 0; i < length; i++) {
        cout << this->getNodeAt(i)->data;
    }
}

#endif
