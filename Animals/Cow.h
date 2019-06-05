#ifndef MEADOW_SIM_COW_H
#define MEADOW_SIM_COW_H

#include "Animal.h"
#include "../Grass.h"
#include "../Pond.h"

class Cow : public Animal{
    Grass &grass;
    Pond &pond;

    void live() override;
    void eat();
    void drink();
    void think();

public:
    Cow(int id, Grass &grass, Meadow &meadow, Pond &pond);
};


#endif //MEADOW_SIM_COW_H
