#include <iostream>
#include <array>
#include "Sun.h"
#include "Animals/Animal.h"
#include "Resources/Grass.h"
#include "Animals/Cow.h"
#include "Resources/Rabbit_Hole.h"
#include "Animals/Rabbit.h"
#include "Animals/Wolf.h"

int main() {
    Pond *pond = new Pond(10);
    Meadow meadow(pond);
    Sun *sun = new Sun(meadow);

    std::vector<Grass*> grass;
    for (int i = 0; i < 3; i++) {
        grass.push_back(new Grass(i, *sun, meadow));
    }

    std::vector<Rabbit_Hole*> rabbit_holes;
    for (int i = 0; i < 3; i++) {
        rabbit_holes.push_back(new Rabbit_Hole(3));
    }

    std::vector<Cow*> cows;
    for (int i = 0; i < 3; ++i) {
        cows.push_back(new Cow(i, grass, meadow));
    }

    std::vector<Rabbit*> rabbits;
    for (int i = 0; i < 3; ++i) {
        rabbits.push_back(new Rabbit(i, grass, meadow, rabbit_holes));
    }

    std::vector<Wolf*> wolves;
    for (int i = 0; i < 3; ++i) {
        wolves.push_back(new Wolf(i, rabbits, meadow, *sun));
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    meadow.ready = true;
    meadow.synchronization.notify_all();

    std::this_thread::sleep_for(std::chrono::seconds(30));
    meadow.ready = false;

    Utils::threadSafeCout("===== FINISHING =====");
    Utils::threadSafeCout("Animals are going on holiday!");

    return 0;
}
