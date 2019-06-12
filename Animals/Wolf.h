#ifndef MEADOW_SIM_WOLF_H
#define MEADOW_SIM_WOLF_H

#include "Animal.h"
#include "Rabbit.h"

class Wolf : public Animal {
    std::vector<Rabbit*> &rabbits;
    Sun &sun;

public:
    Wolf(int id, std::vector<Rabbit*> &rabbits, Meadow &meadow, Sun &sun);

private:
    void live() override;
    void eat() override;

    Rabbit * drawRabbit();
};


#endif //MEADOW_SIM_WOLF_H
