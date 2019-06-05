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

public:
    bool ready;
    std::mutex mutex;
    Synchronization synchronization;

    Grass(const int fork_id, const int owner_id, Sun &sun, Meadow &meadow) :
            id(fork_id), owner(owner_id), sun_thread(sun), meadow(meadow), ready(true), growth_counter(0), grow_thread(&Grass::grow, this) {}

    virtual ~Grass() {
        grow_thread.join();
    }

    void request(int const owner_id) {
        if (ready) {
            std::lock_guard<std::mutex> lock(mutex);
            ready = false;
            std::cout << "Grass not ready" << std::endl;
        } else {
            synchronization.wait();
        }
    }

    void done_eating() {
        growth_counter = 0;
    }

    void grow() {
        meadow.synchronization.wait();

        do {
            if (sun_thread.is_day) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                growth_counter++;
                if (growth_counter == 5) {
                    ready = true;
                    std::cout << "Grass ready" << std::endl;
                    synchronization.notify_all();
                }
            }
        } while (meadow.ready);

        synchronization.notify_all();   // wake all sleeping threads after finish
    }

};


#endif //MEADOW_SIM_GRASS_H
