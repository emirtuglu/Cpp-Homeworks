#include <iostream>
#include <string.h>
#include "Snack.h"
#include "Accompaniment.h"
#include "SnackHashing.h"
#include "AccompanimentHashing.h"

using namespace std;

int main (int argc, char* argv[]) {
    SnackHashing snackTable;
    AccompanimentHashing accompanimentTable;
    int argIndex = 1;
    bool done = false;
    if (argc < 2) {
        cout << "Incorrect input format. Please read readme.txt file." << endl;
        return 1;
    }
    while (!done) {
        if (!strcmp(argv[argIndex], "S")) {
            Snack snack(argv[argIndex + 1]);
            snackTable.insert(snack);
            cout << "Snack '" << argv[argIndex + 1] << "' created" << endl;
            argIndex += 2;
        }
        else if (!strcmp(argv[argIndex], "C")) {
            Snack* first = snackTable.find(argv[argIndex + 1]);
            Snack* second = snackTable.find(argv[argIndex + 2]);
            first->addAccompaniment(*second);
            second->addAccompaniment(*first);
            Accompaniment acc(first, second);
            accompanimentTable.insert(acc);
            argIndex += 3;
        }
        else if (!strcmp(argv[argIndex], "D")) {
            Snack* first = snackTable.find(argv[argIndex + 1]);
            Snack* second = snackTable.find(argv[argIndex + 2]);
            first->deleteAccompaniment(second->getName());
            second->deleteAccompaniment(first->getName());
            string accName = first->getName() + second->getName();
            string accName2 = second->getName() + first->getName();
            accompanimentTable.remove(accName);
            accompanimentTable.remove(accName2);
            argIndex += 3;
        }
        else if (!strcmp(argv[argIndex], "L")) {
            Snack* snack = snackTable.find(argv[argIndex + 1]);
            snack->printAccompaniments();
            argIndex += 2;
        }
        else if (!strcmp(argv[argIndex], "Q")) {
            Snack* first = snackTable.find(argv[argIndex + 1]);
            Snack* second = snackTable.find(argv[argIndex + 2]);
            string accName = first->getName() + second->getName();
            int index = accompanimentTable.find(accName);
            if (index == -1) {
                cout << "No" << endl;
            }
            else {
                cout << "Yes" << endl;
            }
            argIndex += 3;
        }
        else if (!strcmp(argv[argIndex], "X")) {
            done = true;
        }
        else {
            cout << "Incorrect input format. Please read readme.txt file." << endl;
            return 1;
        }
    }
}