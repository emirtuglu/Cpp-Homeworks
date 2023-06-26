#include <iostream>
#include "Creature.h"
#include <cmath>

using namespace std;
Food Creature::bestFood;

Creature::Creature(int id, int health, double x, double y) {
    this->id = id;
    this->health = health;
    this->xCoordinate = x;
    this->yCoordinate = y;
    this->alive = true;
}

int Creature::getId() const {
    return id;
}

int Creature::getHealth() const {
    return health;
}

bool Creature::isAlive() const {
    return alive;
}

double Creature::x() const {
    return xCoordinate;
}

double Creature::y() const {
    return yCoordinate;
}

void Creature::setCoordinates(double x, double y) {
    xCoordinate = x;
    yCoordinate = y;
}

void Creature::setDead() {
    health = 0;
    alive = false;
}

void Creature::setBestFood(Food food) {
    Creature::bestFood = food;
}

Food Creature::getBestFood() {
    return Creature::bestFood;
}

void Creature::decrementHealth() {
    health--;

    if (health <= 0) {
        this->setDead();
    }
}

void Creature::increaseHealth(int x) {
    health += x;
}

void Creature::moveTowardsBestFood() {
    double x = bestFood.x();
    double y = bestFood.y();
    if (x < 0 && y < 0) {
        return;
    }

    double velocity;
    if (health <= 10) {
        velocity = 1;
    }
    else {
        velocity = 10.0 / health;
    }

    double distance = sqrt ( pow((x - xCoordinate), 2) + pow((y - yCoordinate), 2) );
    double ratio = velocity / distance;  // Euclidian triangle algorithm

    xCoordinate = xCoordinate + (x - xCoordinate) * ratio;
    yCoordinate = yCoordinate + (y - yCoordinate) * ratio;
}

void Creature::print() const {
    printf("Creature %d: %.2f, %.2f\n", id, xCoordinate, yCoordinate);
}

bool operator< (Creature& lhs, Creature& rhs) {
    return lhs.getId() < rhs.getId();
}