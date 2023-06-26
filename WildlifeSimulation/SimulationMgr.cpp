#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Creature.h"
#include "Food.h"
#include "MaxPriorityQueue.h"
#include "MinPriorityQueue.h"

using namespace std;

int main (int argc, char* argv[]) {
    vector<Creature> creatures;
    MinPriorityQueue<Food> foodsToBeSpawned;
    MaxPriorityQueue<Food> foods;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    else {
        ifstream file(argv[1]);

        if (file.is_open()) {
            string firstLine;
            getline(file, firstLine);
            int noOfCreatures = stoi(firstLine);
            
            int i = 0;
            string line;
            while (getline(file, line)) {
                if (i < noOfCreatures) {
                    stringstream ss(line);
                    string value;
                    vector<double> values;

                    while (getline(ss, value, ',')) {
                        values.push_back(stod(value));
                    }
                    Creature creature(values.at(0), values.at(3), values.at(1), values.at(2));
                    creatures.push_back(creature);
                }
                else {
                    stringstream ss(line);
                    string value;
                    vector<double> values;

                    while (getline(ss, value, ',')) {
                        values.push_back(stod(value));
                    }
                    Food food(values.at(0), values.at(3), values.at(4), values.at(1), values.at(2));
                    foodsToBeSpawned.insert(food);
                }
                i++;
            }
        }
    }
    sort(creatures.begin(), creatures.end());

    int clock = 0;
    bool allCreaturesDied = false;
    while (!allCreaturesDied) {
        // Print current locations of all creatures
        for (int i = 0; i < creatures.size(); i++) {
            creatures.at(i).print();
        }

        // Add new food resources if any
        while (!foodsToBeSpawned.isEmpty() && foodsToBeSpawned.getNext().getSpawnTime() == clock) {
            foods.insert(foodsToBeSpawned.getNext());
            foodsToBeSpawned.remove();
        }

        // Fights between creatures
        double distanceBtwCreatures;
        for (int i = 0; i < creatures.size(); i++) {
            if (!creatures.at(i).isAlive()) {
                continue;
            }
            for (int j = 0; j < creatures.size(); j++) {
                if (i == j || !creatures.at(j).isAlive()) {
                    continue;
                }
                distanceBtwCreatures = sqrt( pow( (creatures.at(i).y() - creatures.at(j).y()), 2 ) + pow( (creatures.at(i).x() - creatures.at(j).x()), 2));

                if (distanceBtwCreatures < 2 && creatures.at(i).getHealth() >= creatures.at(j).getHealth()) {
                    creatures.at(j).setDead();
                }
            }
        }

        // Consume the best food if nearby
        if (!foods.isEmpty()) {
            Creature::setBestFood(foods.getNext());
            for (int i = 0; i < creatures.size(); i++) {
                if (!creatures.at(i).isAlive()) {
                    continue;
                }

                // If distance between the best food and the creature < 1, consume the best food.
                if ( !foods.isEmpty() && sqrt ( pow( (creatures.at(i).y() - Creature::getBestFood().y()), 2) + pow ( (creatures.at(i).x() - Creature::getBestFood().x()), 2)) < 1) {
                    creatures.at(i).increaseHealth(Creature::getBestFood().getQuality());
                    foods.remove();
                    if (!foods.isEmpty()) {
                        Creature::setBestFood(foods.getNext());  // Set next best food
                    }
                    else {
                        Creature::getBestFood().setCoordinates(-1, -1);
                    }
                }
            }
        }

        // Move towards the best food
        for (int i = 0; i < creatures.size(); i++) {
            if (!creatures.at(i).isAlive()) {
                continue;
            }

            if (!foods.isEmpty()) {
                creatures.at(i).moveTowardsBestFood();
            }
        }

        // Decrement health of creatures
        for (int i = 0; i < creatures.size(); i++) {
            if (!creatures.at(i).isAlive()) {
                continue;
            }
            creatures.at(i).decrementHealth();
        }

        // Check if all creatures are dead
        allCreaturesDied = true;
        for (int i = 0; i < creatures.size(); i++) {
            if (creatures.at(i).isAlive()) {
                allCreaturesDied = false;
                break;
            }
        }
        clock++;
    }
}