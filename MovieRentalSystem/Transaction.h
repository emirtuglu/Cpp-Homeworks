#ifndef __TRANSACTION_H
#define __TRANSACTION_H

#include <iostream>
#include <string>

using namespace std;

class Transaction {
    private:
        int movieId;
        int subscriberId;
        bool returned;
    public:
        Transaction() {};
        Transaction (int movieId, int subscriberId, bool returned = false) {
            this->movieId = movieId;
            this->subscriberId = subscriberId;
            this->returned = returned;
        }
        int getMovieId() const { return this->movieId; }
        int getSubscriberId() const {return this->subscriberId; }
        bool isReturned() const{ return this->returned; }
        void setReturned() { this->returned = true; }
        bool operator> (Transaction other) { 
            if (this->movieId > other.getMovieId()) {
                return true;
            } 
            else if (this->movieId == other.getMovieId()) {
                if ( this->subscriberId > other.getSubscriberId()) {
                    return true;
                }
                else if (this->subscriberId == other.getSubscriberId()) {
                    return !this->isReturned();
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        friend ostream& operator<<( ostream& out, const Transaction& tr) {
            out << tr.getMovieId() << (tr.isReturned()?" returned":" not returned") << endl;
            return out;
        }
        friend bool operator== (const Transaction& lhs, const Transaction& rhs) {
            return (lhs.getMovieId() == rhs.getMovieId() && lhs.getSubscriberId() == rhs.getSubscriberId() && lhs.isReturned() == rhs.isReturned());
        }

};

#endif