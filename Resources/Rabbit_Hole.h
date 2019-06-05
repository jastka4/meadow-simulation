#ifndef MEADOW_SIM_RABBIT_HOLE_H
#define MEADOW_SIM_RABBIT_HOLE_H


#include <vector>
#include <iostream>
#include "../Synchronization.h"
#include "../Utils.h"

class Rabbit_Hole {
    std::vector<int> rabbits;
    Synchronization synchronization;
    int capacity;
public:
    std::mutex mutex;

    Rabbit_Hole(int capacity);

    void request(int id);
    void done_hiding(int id);
};


#endif //MEADOW_SIM_RABBIT_HOLE_H
