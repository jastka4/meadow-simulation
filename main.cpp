#include <iostream>
#include <array>
#include "Sun.h"
#include "Resources/Grass.h"
#include "Animals/Cow.h"
#include "Resources/Rabbit_Hole.h"
#include "Animals/Rabbit.h"
#include "Animals/Wolf.h"
#include "Utils/Graphics.h"

static const int NUMBER_OF_GRASS = 15;
static const int NUMBER_OF_COWS = 10;
static const int NUMBER_OF_RABBITS = 10;
static const int NUMBER_OF_RABBIT_HOLES = 2;
static const int NUMBER_OF_WOLVES = 10;

int main() {
    Pond *pond = new Pond(5);
    Meadow meadow(pond);
    Sun *sun = new Sun(meadow);

    std::vector<Grass*> grass;
    for (int i = 0; i < NUMBER_OF_GRASS; i++) {
        grass.push_back(new Grass(i, *sun, meadow));
    }

    std::vector<Rabbit_Hole*> rabbit_holes;
    for (int i = 0; i < NUMBER_OF_RABBIT_HOLES; i++) {
        rabbit_holes.push_back(new Rabbit_Hole(3));
    }

    std::vector<Cow*> cows;
    for (int i = 0; i < NUMBER_OF_COWS; ++i) {
        cows.push_back(new Cow(i, grass, meadow));
    }

    std::vector<Rabbit*> rabbits;
    for (int i = 0; i < NUMBER_OF_RABBITS; ++i) {
        rabbits.push_back(new Rabbit(i, grass, meadow, rabbit_holes));
    }

    std::vector<Wolf*> wolves;
    for (int i = 0; i < NUMBER_OF_WOLVES; ++i) {
        wolves.push_back(new Wolf(i, rabbits, meadow, *sun));
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    meadow.ready = true;
    meadow.synchronization.setSleep(false);
    meadow.synchronization.notify_all();

    auto *graphics = new Graphics(cows, rabbits, rabbit_holes, wolves, meadow, *sun);
    graphics->init();

    std::this_thread::sleep_for(std::chrono::seconds(30));
    meadow.ready = false;

    Utils::thread_safe_cout("===== FINISHING =====");
    Utils::thread_safe_cout("Animals are going on holiday!");

    getch();
    endwin();
    return 0;
}
