#ifndef MEADOW_SIM_COW_H
#define MEADOW_SIM_COW_H

#include "Animal.h"
#include "../Resources/Grass.h"
#include "../Resources/Pond.h"

class Cow : public Animal{
    std::vector<Grass*> &grass;

    void live() override;
    void eat() override;

public:
    Cow(int id, std::vector<Grass*> &grass, Meadow &meadow);

    Grass *drawGrass();
};


#endif //MEADOW_SIM_COW_H
