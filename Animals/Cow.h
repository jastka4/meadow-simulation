#ifndef MEADOW_SIM_COW_H
#define MEADOW_SIM_COW_H

#include "Animal.h"
#include "../Grass.h"

class Cow : public Animal{
    Grass &grass;

    void live() override;
    void eat();
public:
    Cow(int id, Grass &grass, Meadow &meadowThread);

    void think();
};


#endif //MEADOW_SIM_COW_H
