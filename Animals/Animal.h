#ifndef MEADOW_SIM_ANIMAL_H
#define MEADOW_SIM_ANIMAL_H

#include <string>
#include <thread>
#include "../Meadow.h"

class Animal {
    std::string name;
    std::thread live_thread;
    Meadow &meadow_thread;

public:
    Animal(const std::string &name, Meadow &meadow);

    void live();
};


#endif //MEADOW_SIM_ANIMAL_H
