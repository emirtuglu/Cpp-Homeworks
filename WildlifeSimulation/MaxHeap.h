#ifndef __MAXHEAP_H
#define __MAXHEAP_H

#include <iostream>

using namespace std;

const int HEAP_CAPACITY = 50;

template <class T>
class MaxHeap {
    private:
        T items[HEAP_CAPACITY];
        int size;
    public:
        MaxHeap();
        T* getItems();
        int getSize() const;
        T getRoot();
        bool isEmpty() const;
        void insert(T item);
        void remove();
        void heapify(int rootIndex);
};

template <class T>
MaxHeap<T>::MaxHeap() {
    size = 0;
}

template <class T>
T* MaxHeap<T>::getItems() {
    return items;
}

template <class T>
int MaxHeap<T>::getSize() const {
    return size;
}

template <class T>
T MaxHeap<T>::getRoot() {
    if (this->isEmpty()) {
        throw "Exception: Cannot peek from an empty heap";
    }
    return items[0];
}

template <class T>
bool MaxHeap<T>::isEmpty() const {
    return size == 0;
}

template <class T>
void MaxHeap<T>::insert(T item) {
    if (size == HEAP_CAPACITY) {
        throw "Exception: Cannot insert to a full heap";
    }

    items[size] = item;

    int childIndex = size;
    int parentIndex = (size - 1) / 2;

    while (items[parentIndex] < items[childIndex]) {
        T temp = items[parentIndex];
        items[parentIndex] = items[childIndex];
        items[childIndex] = temp;

        childIndex = parentIndex;
        parentIndex = (parentIndex - 1) / 2;
    }
    size++;
}

template <class T>
void MaxHeap<T>::remove() {
    if (this->isEmpty()) {
        throw "Exception: Cannot remove from an empty heap";
    }

    items[0] = items[size - 1];
    size--;
    this->heapify(0);
}

template <class T>
void MaxHeap<T>::heapify(int rootIndex) {
    int largest = rootIndex;
    int leftChild = rootIndex * 2 + 1;
    int rightChild = rootIndex * 2 + 2;

    if (leftChild < size && items[largest] < items[leftChild]) {
        largest = leftChild;
    }
    if (rightChild < size && items[largest] < items[rightChild]) {
        largest = rightChild;
    }

    if (largest != rootIndex) {
        T temp = items[rootIndex];
        items[rootIndex] = items[largest];
        items[largest] = temp;

        this->heapify(largest);
    }
}

#endif