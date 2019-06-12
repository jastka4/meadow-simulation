#ifndef MEADOW_SIM_ANIMAL_H
#define MEADOW_SIM_ANIMAL_H

#include <string>
#include <thread>
#include <random>
#include <utility>
#include <array>
#include <list>
#include <iostream>
#include "../Meadow.h"
#include "../Utils.h"

class Animal {
protected:
    std::mt19937 random_generator{std::random_device{}()};

    std::atomic<int> id;
    std::thread live_thread;
    Meadow &meadow;
    std::atomic<bool> alive;

public:
    Animal(int id, Meadow &meadow);
    virtual ~Animal();

    void think(std::string who);
    void drink(std::string who);
    virtual void live() = 0;
    virtual void eat() = 0;

    int getId() const;
    bool isAlive() const;
};


#endif //MEADOW_SIM_ANIMAL_H
