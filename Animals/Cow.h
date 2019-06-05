#ifndef MEADOW_SIM_COW_H
#define MEADOW_SIM_COW_H

#include "Animal.h"
#include "../Resources/Grass.h"
#include "../Resources/Pond.h"

class Cow : public Animal{
    Grass &grass;

    void live() override;
    void eat() override;

public:
    Cow(int id, Grass &grass, Meadow &meadow);
};


#endif //MEADOW_SIM_COW_H
