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
    std::atomic<bool> is_day;
public:
    explicit Sun(Meadow &meadow);
    virtual ~Sun();

    const std::atomic<bool> &getIsDay() const;
};


#endif //MEADOW_SIM_SUN_H
