#ifndef __MINPRIORITYQUEUE_H
#define __MINPRIORITYQUEUE_H


#include <iostream>
#include "MinHeap.h"

using namespace std;

template <class T>
class MinPriorityQueue {
    private:
        MinHeap<T> minHeap;
    public:
        bool isEmpty() const;
        void insert(T item);
        void remove();
        T getNext();
        T* getItems();
        int getSize();
};

template <class T>
bool MinPriorityQueue<T>::isEmpty() const {
    return minHeap.isEmpty();
}

template <class T>
void MinPriorityQueue<T>::insert(T item) {
    minHeap.insert(item);
}

template <class T>
void MinPriorityQueue<T>::remove() {
    minHeap.remove();
}

template <class T>
T MinPriorityQueue<T>::getNext() {
    return minHeap.getRoot();
}

template <class T>
T* MinPriorityQueue<T>::getItems() {
    return minHeap.getItems();
}

template <class T>
int MinPriorityQueue<T>::getSize() {
    return minHeap.getSize();
}


#endif