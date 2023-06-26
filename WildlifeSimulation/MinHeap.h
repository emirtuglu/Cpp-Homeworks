#ifndef __MINHEAP_H
#define __MINHEAP_H

#include <iostream>

using namespace std;

template <class T>
class MinHeap {
    private:
        T items[HEAP_CAPACITY];
        int size;
    public:
        MinHeap();
        T* getItems();
        int getSize() const;
        T getRoot();
        bool isEmpty() const;
        void insert(T item);
        void remove();
        void heapify(int rootIndex);
};

template <class T>
MinHeap<T>::MinHeap() {
    size = 0;
}

template <class T>
T* MinHeap<T>::getItems() {
    return items;
}

template <class T>
int MinHeap<T>::getSize() const {
    return size;
}

template <class T>
T MinHeap<T>::getRoot() {
    if (this->isEmpty()) {
        throw "Exception: Cannot peek from an empty heap";
    }
    return items[0];
}

template <class T>
bool MinHeap<T>::isEmpty() const {
    return size == 0;
}

template <class T>
void MinHeap<T>::insert(T item) {
    if (size == HEAP_CAPACITY) {
        throw "Exception: Cannot insert to a full heap";
    }

    items[size] = item;

    int childIndex = size;
    int parentIndex = (size - 1) / 2;

    while (items[parentIndex] > items[childIndex]) {
        T temp = items[parentIndex];
        items[parentIndex] = items[childIndex];
        items[childIndex] = temp;

        childIndex = parentIndex;
        parentIndex = (parentIndex - 1) / 2;
    }
    size++;
}

template <class T>
void MinHeap<T>::remove() {
    if (this->isEmpty()) {
        throw "Exception: Cannot remove from an empty heap";
    }

    items[0] = items[size - 1];
    size--;
    this->heapify(0);
}

template <class T>
void MinHeap<T>::heapify(int rootIndex) {
    int smallest = rootIndex;
    int leftChild = rootIndex * 2 + 1;
    int rightChild = rootIndex * 2 + 2;

    if (leftChild < size && items[smallest] > items[leftChild]) {
        smallest = leftChild;
    }
    if (rightChild < size && items[smallest] > items[rightChild]) {
        smallest = rightChild;
    }

    if (smallest != rootIndex) {
        T temp = items[rootIndex];
        items[rootIndex] = items[smallest];
        items[smallest] = temp;

        this->heapify(smallest);
    }
}

#endif