#ifndef MEADOW_SIM_GRASS_H
#define MEADOW_SIM_GRASS_H

#include <iostream>
#include "Meadow.h"
#include "Sun.h"

class Grass {
    const int id;
    int growth_counter;
    Sun &sun_thread;
    Meadow &meadow;
    std::thread grow_thread;
    bool ready;

public:
    std::mutex mutex;
    Synchronization synchronization;

    Grass(int grass_id, Sun &sun, Meadow &meadow);
    virtual ~Grass();

    void request();
    void done_eating();
    void grow();
};


#endif //MEADOW_SIM_GRASS_H
