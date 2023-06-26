#ifndef __MOVIE_H
#define __MOVIE_H

#include <iostream>
#include <string>

using namespace std;

class Movie {
    private:
        int id;
        int copyNumber;
        int totalNumber; // Total number of copies
    public:
        Movie() {};
        Movie(int id, int copyNumber) { this->id = id; this->copyNumber = copyNumber; this->totalNumber = copyNumber; }
        int getId() const { return this->id; }
        int getCopyNumber() const { return this->copyNumber; }
        int getTotalNumber() const { return this->totalNumber; }
        void decrementCopyNumber() { this->copyNumber = this->getCopyNumber() - 1; }
        void incrementCopyNumber() { this->copyNumber = this->getCopyNumber() + 1; }
        bool operator> (Movie otherMovie) { return this->id > otherMovie.getId(); }
        friend ostream& operator<<( ostream& out, const Movie& mov) {
            out << mov.getId() << " " << mov.getTotalNumber() << endl;
            return out;
        }
        friend bool operator== (const Movie& lhs, const Movie& rhs) {
            return lhs.getId() == rhs.getId();
        }
};


#endif