#ifndef MEADOW_SIM_GRASS_H
#define MEADOW_SIM_GRASS_H

#include <iostream>
#include "Meadow.h"
#include "Sun.h"

class Grass {
    const int id;
    int owner;
    int growth_counter;
    Sun &sun_thread;
    Meadow &meadow;
    std::thread grow_thread;
    bool ready;

public:
    std::mutex mutex;
    Synchronization synchronization;

    Grass(int grass_id, int owner_id, Sun &sun, Meadow &meadow);
    virtual ~Grass();

    void request(int owner_id);
    void done_eating();
    void grow();

};


#endif //MEADOW_SIM_GRASS_H
