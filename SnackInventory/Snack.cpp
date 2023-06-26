#include "Snack.h"

using namespace std;

Snack::Snack() {

}

Snack::Snack(string aName) {
    this->name = aName;
    this->accompaniments = new LinkedList<Snack>();
}

string Snack::getName() {
    return this->name;
}

void Snack::addAccompaniment(Snack acc) {
    if (acc.getName() == name) {
        return;
    }
    this->accompaniments->add(acc);
}

void Snack::deleteAccompaniment(string name) {
    Node<Snack>* curr = accompaniments->getHead();
    int index = 0;
    while (curr != nullptr) {
        if (curr->data.getName() == name) {
            accompaniments->remove(index);
            return;
        }
        index++;
        curr = curr->next;
    }
}

void Snack::printAccompaniments() {
    int size = this->accompaniments->getLength();
    if (size > 0) {
        cout << accompaniments->getNodeAt(0)->data.getName();
    }
    for (int i = 1; i < size; i++) {
        cout << " " << accompaniments->getNodeAt(i)->data.getName();
    }
    cout << endl;
}