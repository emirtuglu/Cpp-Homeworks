#ifndef __FOOD_H
#define __FOOD_H

#include <iostream>

using namespace std;

class Food {
    private:
        int id;
        int quality;
        int spawnTime;
        double xCoordinate;
        double yCoordinate;
    public:
        Food();
        Food(int id, int quality, int spawnTime, double x, double y);
        int getId() const;
        int getQuality() const;
        int getSpawnTime() const;
        double x() const;
        double y() const;
        void setCoordinates(double x, double y);
        friend bool operator< (Food& lhs, Food& rhs);
        friend bool operator> (Food& lhs, Food& rhs);
};

#endif