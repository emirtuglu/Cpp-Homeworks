#include <iostream>
#include "Food.h"

using namespace std;

Food::Food() {

}

Food::Food(int id, int quality, int spawnTime, double x, double y) {
    this->id = id;
    this->quality = quality;
    this->spawnTime = spawnTime;
    this->xCoordinate = x;
    this->yCoordinate = y;
}

int Food::getId() const {
    return id;
}

int Food::getQuality() const {
    return quality;
}

int Food::getSpawnTime() const {
    return spawnTime;
}

double Food::x() const {
    return xCoordinate;
}

double Food::y() const {
    return yCoordinate;
}

void Food::setCoordinates(double x, double y) {
    this->xCoordinate = x;
    this->yCoordinate = y;
}

bool operator< (Food& lhs, Food& rhs) {
    if (lhs.getQuality() == rhs.getQuality()) {
        return lhs.getId() > rhs.getId();
    }
    else {
        return lhs.getQuality() < rhs.getQuality();
    }
}

bool operator> (Food& lhs, Food& rhs) {
    if (lhs.getSpawnTime() == rhs.getSpawnTime()) {
        return lhs.getId() > rhs.getId();
    }
    else {
        return lhs.getSpawnTime() > rhs.getSpawnTime();
    }
}
