#ifndef MEADOW_SIM_RABBIT_HOLE_H
#define MEADOW_SIM_RABBIT_HOLE_H


#include <vector>
#include <iostream>
#include "../Utils/Synchronization.h"
#include "../Utils/Utils.h"

class Rabbit_Hole {
    std::vector<int> rabbits;
    Synchronization synchronization;
    std::atomic_int capacity;
public:
    std::mutex mutex;

    Rabbit_Hole(int capacity);

    void request(int id);
    void done_hiding(int id);
    int get_capacity() const;
    int get_number_of_animals();
};


#endif //MEADOW_SIM_RABBIT_HOLE_H
