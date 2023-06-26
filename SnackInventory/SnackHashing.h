#ifndef __SNACKHASHING_H
#define __SNACKHASHING_H

#include <iostream>
#include <string>
#include "Snack.h"

using namespace std;

const int TABLE_SIZE = 11;

class SnackHashing{
    private:
        LinkedList<Snack> table[TABLE_SIZE];
    public:
        void insert(Snack key);
        int hash(string key);
        Snack* find(string key);
};

#endif