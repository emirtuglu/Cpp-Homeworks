#include "SnackHashing.h"

using namespace std;

void SnackHashing::insert(Snack key) {
    int index = hash(key.getName());
    table[index].add(key);
}

int SnackHashing::hash(string key) {
    int sum = 0;
    for (char letter : key) {
        sum += int(letter);
    }
    return sum % TABLE_SIZE;
}

Snack* SnackHashing::find(string key) {
    int listIndex = hash(key);
    Node<Snack>* curr = table[listIndex].getHead();
    while (curr != nullptr) {
        if (curr->data.getName() == key) {
            return &(curr->data);
        }
        curr = curr->next;
    }
    return nullptr;

}