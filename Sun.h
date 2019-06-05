#ifndef MEADOW_SIM_SUN_H
#define MEADOW_SIM_SUN_H

#include <random>
#include "Meadow.h"

class Sun {
    std::mt19937 random_generator{std::random_device{}()};

    void day();
    void night();
    void shine();
    Meadow &meadow;
    std::thread live_thread;
public:
    explicit Sun(Meadow &meadow);
    virtual ~Sun();

    std::atomic<bool> is_day{false};
};


#endif //MEADOW_SIM_SUN_H
