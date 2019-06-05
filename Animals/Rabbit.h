#ifndef MEADOW_SIM_RABBIT_H
#define MEADOW_SIM_RABBIT_H

#include "Animal.h"
#include "../Resources/Grass.h"
#include "../Resources/Rabbit_Hole.h"

class Rabbit : public Animal {
    Grass &grass;
    Rabbit_Hole &rabbit_hole;

    void live() override;
    void eat() override ;
    void hide();
    Synchronization synchronization;
public:
    std::mutex mutex;

    Rabbit(int id, Grass &grass, Meadow &meadow, Rabbit_Hole &rabbit_hole);

    void request();
};


#endif //MEADOW_SIM_RABBIT_H
