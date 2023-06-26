#ifndef __SNACK_H
#define __SNACK_H

#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;

class Snack {
    private:
        string name;
        LinkedList<Snack>* accompaniments;
    public:
        Snack();
        Snack(string aName);
        string getName();
        void addAccompaniment(Snack acc);
        void deleteAccompaniment(string name);
        void printAccompaniments();
};

#endif