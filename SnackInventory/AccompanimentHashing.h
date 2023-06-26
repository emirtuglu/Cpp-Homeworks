#ifndef __ACCOMPANIMENTHASHING_H
#define __ACCOMPANIMENTHASHING_H

#include <iostream>
#include <string>
#include "Accompaniment.h"

using namespace std;

const int SIZE = 71;

class AccompanimentHashing {
    private:
        Accompaniment table[SIZE];
    public:
        AccompanimentHashing();
        void insert(Accompaniment key);
        int hash(string key);
        int find(string key);
        void remove(string key);
};

#endif