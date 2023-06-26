#ifndef __ACOOMPANIMENT_H
#define __ACOOMPANIMENT_H

#include <iostream>
#include <string>
#include "Snack.h"

using namespace std;

class Accompaniment {
    private:
        string name;
        Snack* firstSnack;
        Snack* secondSnack;
    public:
        Accompaniment();
        Accompaniment(Snack* first, Snack* second);
        string getName();
        void setName(string aName);
};

#endif