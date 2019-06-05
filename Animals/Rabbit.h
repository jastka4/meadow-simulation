#ifndef MEADOW_SIM_RABBIT_H
#define MEADOW_SIM_RABBIT_H

#include "Animal.h"
#include "../Grass.h"

class Rabbit : public Animal {
    Grass &grass;
public:
    Rabbit(int id, Meadow &meadow, Grass &grass);

    void live() override;
    void eat() override ;
};


#endif //MEADOW_SIM_RABBIT_H
