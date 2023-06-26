#include "Accompaniment.h"

using namespace std;

Accompaniment::Accompaniment() {
    this->name = "null";
}

Accompaniment::Accompaniment(Snack* first, Snack* second) {
    this->firstSnack = first;
    this->secondSnack = second;
    this->name = first->getName() + second->getName();
}

string Accompaniment::getName() {
    return this->name;
}

void Accompaniment::setName(string aName) {
    this->name = aName;
}