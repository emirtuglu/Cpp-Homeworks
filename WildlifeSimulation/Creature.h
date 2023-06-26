#ifndef __CREATURE_H
#define __CREATURE_H

#include <iostream>
#include "Food.h"

using namespace std;

class Creature {
    private:
        int id;
        int health;
        double xCoordinate;
        double yCoordinate;
        bool alive;
        static Food bestFood;
    public:
        Creature(int id, int health, double x, double y); 
        int getId() const;
        int getHealth() const;
        bool isAlive() const;
        double x() const;
        double y() const;
        void setCoordinates(double x, double y);
        void setDead();
        static void setBestFood(Food bestFood);
        static Food getBestFood();
        void decrementHealth();
        void increaseHealth(int x);
        void moveTowardsBestFood();
        void print() const;
        friend bool operator< (Creature& lhs, Creature& rhs);
};

#endif