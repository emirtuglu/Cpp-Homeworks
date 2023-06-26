#ifndef __MAXPRIORITYQUEUE_H
#define __MAXPRIORITYQUEUE_H


#include <iostream>
#include "MaxHeap.h"

using namespace std;

template <class T>
class MaxPriorityQueue {
    private:
        MaxHeap<T> heap;
    public:
        bool isEmpty() const;
        void insert(T item);
        void remove();
        T getNext();
        T* getItems();
        int getSize();
};

template <class T>
bool MaxPriorityQueue<T>::isEmpty() const {
    return heap.isEmpty();
}

template <class T>
void MaxPriorityQueue<T>::insert(T item) {
    heap.insert(item);
}

template <class T>
void MaxPriorityQueue<T>::remove() {
    heap.remove();
}

template <class T>
T MaxPriorityQueue<T>::getNext() {
    return heap.getRoot();
}

template <class T>
T* MaxPriorityQueue<T>::getItems() {
    return heap.getItems();
}

template <class T>
int MaxPriorityQueue<T>::getSize() {
    return heap.getSize();
}


#endif