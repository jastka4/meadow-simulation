#ifndef MEADOW_SIM_SUN_H
#define MEADOW_SIM_SUN_H

#include <random>
#include "Meadow.h"

class Sun {
    std::mt19937 random_generator{std::random_device{}()};

    void day();
    void night();
    Meadow &meadow_thread;
    std::thread live_thread;
public:
    Sun(Meadow &meadow);

    virtual ~Sun();

    void shine();
};


#endif //MEADOW_SIM_SUN_H
