#include <iostream>
#include <string>
#include <fstream>
#include "MovieRentalSystem.h"
#include "Node.h"

using namespace std;

MovieRentalSystem::MovieRentalSystem( const string movieInfoFileName, const string subscriberInfoFileName ) {
   this->subscribers = new LinkedList<Subscriber>();
   this->movies = new LinkedList<Movie>();
    ifstream movieStream(movieInfoFileName);
    if (movieStream.is_open()) {
        int numMovies;
        movieStream >> numMovies;
        for (int i = 0; i < numMovies; i++) {
            int id, copies;
            movieStream >> id >> copies;
            Movie mov (id, copies);
            this->movies->add(mov);
        }
        movieStream.close();
    } else {
        cout << "Input file " << movieInfoFileName << " does not exist" << endl;
        return;
    }

    ifstream subscriberStream(subscriberInfoFileName);
    if (subscriberStream.is_open()) {
        int numSubscribers;
        subscriberStream >> numSubscribers;
        for (int i = 0; i < numSubscribers; i++) {
            int id;
            subscriberStream >> id;
            Subscriber sub (id);
            this->subscribers->add(sub);
        }
        subscriberStream.close();
    } else {
        cout << "Input file " << subscriberInfoFileName << " does not exist" << endl;
        return;
    }
    cout << this->subscribers->getLength() << " subscribers and " << this->movies->getLength() << " movies have been loaded" << endl;
}

MovieRentalSystem::~MovieRentalSystem() {
    delete this->subscribers;
    delete this->movies;
}

void MovieRentalSystem::removeMovie( const int movieId ) {
    // Check if movie exists
    Movie mov(movieId, 0);
    if (!this->movies->exists(mov)) {
        cout << "Movie " << movieId << " does not exist" << endl;
        return;
    }

    // Check if movie has any unreturned copy
    int subscriberNo = this->subscribers->getLength();
    for (int i = 0; i < subscriberNo; i++) {
        Transaction tr (movieId, this->subscribers->getNodeAt(i)->getData()->getId(), false);
        if (this->subscribers->getNodeAt(i)->getData()->getTransactions()->exists(tr)) {
            cout << "Movie " << movieId << " cannot be removed -- at least one copy has not been returned" << endl;
            return;
        }
    }

    // Remove movie
    int indexOfMovie = this->movies->indexOf(mov);
    this->movies->remove(indexOfMovie);
    cout << "Movie " << movieId << " has been removed" << endl;
}

void MovieRentalSystem::addMovie( const int movieId, const int numCopies)  {
    Movie mov (movieId, numCopies);
    if (this->movies->exists(mov)) {
        cout << "Movie " << movieId << " already exists" << endl;
        return;
    }
    this->movies->add(mov);
    cout << "Movie " << movieId << " has been added" << endl;
}

void MovieRentalSystem::removeSubscriber( const int subscriberId ) {
    Subscriber sub(subscriberId);
    // Check if subscriber exists
    if (!this->subscribers->exists(sub)) {
        cout << "Subscriber " << subscriberId << " does not exist" << endl;
        return;
    }

    // Check if subscriber has any unreturned copy
    int indexOfSubscriber = this->subscribers->indexOf(sub);
    Node<Transaction>* head = this->subscribers->getNodeAt(indexOfSubscriber)->getData()->getTransactions()->getHead();
    while (head != nullptr) {
        if (head->getData()->isReturned() == false) {
            cout << "Subscriber " << subscriberId << " cannot be removed -- at least one movie has not been returned" << endl;
            return;
        }
        head = head->next;
    }

    // Remove subscriber
    this->subscribers->remove(indexOfSubscriber);
    cout << "Subscriber " << subscriberId << " has been removed" << endl;
}


void MovieRentalSystem::rentMovie( const int subscriberId, const int movieId ) {
    Movie* mov = this->getMovieById(movieId);
    Subscriber* sub = this->getSubscriberById(subscriberId);

    if (mov == nullptr && sub == nullptr) {
        cout << "Subscriber " << subscriberId << " and movie " << movieId << " do not exist" << endl;
        return;
    }

    if (mov == nullptr) {
        cout << "Movie " << movieId << " does not exist" << endl;
        return;
    }

    if (sub == nullptr) {
        cout << "Subscriber " << subscriberId << " does not exist" << endl;
        return;
    }

    // Check if there is any available copy
    int copyNumber = mov->getCopyNumber();
    if (copyNumber < 1) {
        cout << "Movie " << movieId << " has no available copy for renting" << endl;
        return;
    } 

    // Rent movie
    Transaction tr (movieId, subscriberId, false);
    sub->addTransaction(tr);
    mov->decrementCopyNumber();
    cout << "Movie " << movieId << " has been rented by subscriber " << subscriberId << endl;
}

void MovieRentalSystem::returnMovie( const int subscriberId, const int movieId ) {
    Transaction notReturnedTransaction (movieId, subscriberId, false);
    Subscriber* sub = this->getSubscriberById(subscriberId);
    Movie* mov = this->getMovieById(movieId);

    if (sub->getTransactions()->exists(notReturnedTransaction)) {
        cout << "Movie " << movieId << " has been returned by subscriber " << subscriberId << endl;
        Node<Transaction>* head =  sub->getTransactions()->getHead();
        while (head != nullptr) {
            if (head->data == notReturnedTransaction) {
                head->getData()->setReturned();
                mov->incrementCopyNumber();
                return;
            }
            head = head->next;
        }
    }
    else {
        cout << "No rental transaction for subscriber " << subscriberId << " and movie " << movieId << endl;
    }
}


void MovieRentalSystem::showMoviesRentedBy( const int subscriberId ) const {
    Subscriber* sub = this->getSubscriberById(subscriberId);
    if (sub == nullptr) {
        cout << "Subscriber " << subscriberId << " does not exist" << endl;
        return;
    }

    if (sub->getTransactions()->isEmpty()) {
        cout << "Subscriber " << subscriberId << " has not rented any movies" << endl;
        return;
    }

    cout << "Subscriber " << subscriberId << " has rented the following movies:" << endl;
    sub->getTransactions()->print();
}

void MovieRentalSystem::showSubscribersWhoRentedMovie( const int movieId ) const {
    Movie* mov = getMovieById(movieId);
    if (mov == nullptr) {
        cout << "Movie " << movieId << " does not exist" << endl;
        return;
    } 

    int rentedCounter = 0;
    int noOfSubscribers = this->subscribers->getLength();
    for (int i = 0; i < noOfSubscribers; i++) {
        int subscriberId = this->subscribers->getNodeAt(i)->getData()->getId();
        Transaction returnedTransaction (movieId, subscriberId, true);
        Transaction notReturnedTransaction (movieId, subscriberId, false);
        int noOfTransactions = this->subscribers->getNodeAt(i)->getData()->getTransactions()->getLength();

        for (int j = 0; j < noOfTransactions; j++) {
            Transaction tr = this->subscribers->getNodeAt(i)->getData()->getTransactions()->getNodeAt(j)->data;
            if ( returnedTransaction == tr) {
                if (rentedCounter == 0) {
                    cout << "Movie " << movieId << " has been rented by the following subscribers:" << endl;
                }
                cout << subscriberId << " returned" << endl;
                rentedCounter++;
            }
            if ( notReturnedTransaction == tr) {
                if (rentedCounter == 0) {
                    cout << "Movie " << movieId << " has been rented by the following subscribers:" << endl;
                }
                cout << subscriberId << " not returned" << endl;
                rentedCounter++;
            }
        }
    }
    if (rentedCounter == 0) {
        cout << "Movie " << movieId << " has not been rented by any subscriber" << endl;
    }
}



void MovieRentalSystem::showAllMovies() const {
    cout << "Movies in the movie rental system:" << endl;
    this->movies->print();
}

void MovieRentalSystem::showAllSubscribers() const {
    cout << "Subscribers in the movie rental system:" << endl;
    this->subscribers->print();
}

Subscriber* MovieRentalSystem::getSubscriberById(int subscriberId) const {
    Subscriber sub (subscriberId);
    if (!this->subscribers->exists(sub)) {
        return nullptr;
    }
    int index = this->subscribers->indexOf(sub);
    return this->subscribers->getNodeAt(index)->getData();
}

Movie* MovieRentalSystem::getMovieById(int movieId) const {
    Movie mov (movieId, 0);
    if (!this->movies->exists(mov)) {
        return nullptr;
    }
    int index = this->movies->indexOf(mov);
    return this->movies->getNodeAt(index)->getData();
}

