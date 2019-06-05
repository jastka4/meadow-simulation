#ifndef MEADOW_SIM_ANIMAL_H
#define MEADOW_SIM_ANIMAL_H

#include <string>
#include <thread>
#include <random>
#include "../Meadow.h"

class Animal {
protected:
    std::mt19937 random_generator{std::random_device{}()};

    int id;
    std::thread live_thread;
    Meadow &meadow;

public:
    Animal(int id, Meadow &meadow);
    virtual ~Animal();

    virtual void live() = 0;
};


#endif //MEADOW_SIM_ANIMAL_H
