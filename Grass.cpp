#include "Grass.h"

Grass::Grass(const int grass_id, Sun &sun, Meadow &meadow) :
        id(grass_id), sun_thread(sun), meadow(meadow), ready(true), growth_counter(0), grow_thread(&Grass::grow, this) {}

Grass::~Grass() {
    grow_thread.join();
}

void Grass::request(int const owner_id)  {
    if (ready) {
        std::lock_guard<std::mutex> lock(mutex);
        ready = false;
        std::cout << "Grass not ready" << std::endl;
    } else {
        synchronization.wait();
    }
}

void Grass::done_eating() {
    growth_counter = 0;
}

void Grass::grow() {
    meadow.synchronization.wait();

    do {
        if (sun_thread.getIsDay()) {
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
