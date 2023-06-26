#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Movie.h"
#include "Subscriber.h"
#include "Transaction.h"

using namespace std;

class MovieRentalSystem {
    private:
        LinkedList<Movie>* movies;
        LinkedList<Subscriber>* subscribers;
    public:
        MovieRentalSystem( const string movieInfoFileName,
        const string subscriberInfoFileName );
        ~MovieRentalSystem();
        void removeMovie( const int movieId );
        void addMovie( const int movieId, const int numCopies );
        void removeSubscriber( const int subscriberId );
        void rentMovie( const int subscriberId, const int movieId );
        void returnMovie( const int subscriberId, const int movieId );
        void showMoviesRentedBy( const int subscriberId ) const;
        void showSubscribersWhoRentedMovie( const int movieId ) const;
        void showAllMovies() const;
        void showAllSubscribers() const;
        Subscriber* getSubscriberById(int subscriberId) const;
        Movie* getMovieById(int movieId) const;
};