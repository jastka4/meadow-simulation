#ifndef MEADOW_SIM_WOLF_H
#define MEADOW_SIM_WOLF_H

#include "Animal.h"
#include "Rabbit.h"

class Wolf : public Animal {
    Rabbit &rabbit;

public:
    Wolf(int id, Rabbit &rabbit, Meadow &meadow);

private:
    void live() override;
    void eat() override;

    void hunt();
};


#endif //MEADOW_SIM_WOLF_H
