#ifndef MEADOW_SIM_RABBIT_H
#define MEADOW_SIM_RABBIT_H

#include "Animal.h"
#include "../Resources/Grass.h"
#include "../Resources/Rabbit_Hole.h"

class Rabbit : public Animal {
    std::vector<Grass*> &grass;
    std::vector<Rabbit_Hole*> &rabbit_holes;
    bool alive;

    void live() override;
    void eat() override ;
    void hide();
    Synchronization synchronization;
public:
    std::mutex mutex;

    Rabbit(int id, std::vector<Grass*> &grass, Meadow &meadow, std::vector<Rabbit_Hole*> &rabbit_holes);
    void request();
    Grass *drawGrass();

    Rabbit_Hole *drawRabbitHole();
};


#endif //MEADOW_SIM_RABBIT_H
