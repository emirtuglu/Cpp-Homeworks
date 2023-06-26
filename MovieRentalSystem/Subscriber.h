#ifndef __SUBSCRIBER_H
#define __SUBSCRIBER_H

#include <iostream>
#include <string>
#include "Transaction.h"

using namespace std;

class Subscriber {
    private:
        int id;
        LinkedList<Transaction> transactions;
    public:
        Subscriber() {};
        Subscriber (int id) { this->id = id;}
        int getId() const { return this->id; }
        LinkedList<Transaction>* getTransactions() { return &(this->transactions); }
        void addTransaction(Transaction tr) { this->transactions.add(tr); }
        bool operator> (Subscriber other) { return this->id > other.getId(); }
        friend ostream& operator<<( ostream& out, const Subscriber& sub) {
            out << sub.getId() << endl;
            return out;
        }
        friend bool operator== (const Subscriber& lhs, const Subscriber& rhs) {
            return lhs.getId() == rhs.getId();
        }
};


#endif