#ifndef MEADOW_SIM_MEADOW_H
#define MEADOW_SIM_MEADOW_H

#include <atomic>
#include <thread>
#include "Synchronization.h"
#include "Pond.h"

struct Meadow {
    std::atomic<bool> ready{false};
    Synchronization synchronization;

    Pond *pond;
    explicit Meadow(Pond *pond);
};


#endif //MEADOW_SIM_MEADOW_H
