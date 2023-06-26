#include "AccompanimentHashing.h"
#include <string>

using namespace std;

AccompanimentHashing::AccompanimentHashing() {
    
}

void AccompanimentHashing::insert(Accompaniment key) {
    int index = hash(key.getName());
    table[index] = key;
}

int AccompanimentHashing::hash(string key) {
    int sum = 0;
    for (char letter : key) {
        sum += int(letter);
    }
    int index = sum % SIZE;
    if (table[index].getName() == "null") {
        return index;
    }
    else {
        int i = 1;
        while (i < SIZE) {
            if (table[(index + i*i) % SIZE].getName() == "null") {
                return (index + i*i) % SIZE;
            }
            i++;
        }
    }
    return -1;
}

int AccompanimentHashing::find(string key) {
    int sum = 0;
    for (char letter : key) {
        sum += int(letter);
    }
    int index = sum % SIZE;
    if (table[index].getName() == key) {
        return index;
    }
    else {
        int i = 1;
        while (i < SIZE) {
            if (table[(index + i*i) % SIZE].getName() == key) {
                return (index + i*i) % SIZE;
            }
            i++;
        }
    }
    return -1;
}


void AccompanimentHashing::remove(string key) {
    int sum = 0;
    for (char letter : key) {
        sum += int(letter);
    }
    int index = sum % SIZE;
    if (table[index].getName() == key) {
        table[index].setName("null");
    }
    else {
        int i = 1;
        while (i < SIZE) {
            if (table[(index + i*i) % SIZE].getName() == key) {
                table[(index + i*i) % SIZE].setName("null");
            }
            i++;
        }
    }
}