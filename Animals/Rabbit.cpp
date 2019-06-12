#include "Rabbit.h"

Rabbit::Rabbit(int id, std::vector<Grass*> &grass, Meadow &meadow, std::vector<Rabbit_Hole*> &rabbit_holes)
        : Animal(id, meadow), grass(grass), rabbit_holes(rabbit_holes) {}

void Rabbit::live() {
    meadow.synchronization.wait();

    do {
        eat();
        if (!alive) return;
        drink("Rabbit");
        if (!alive) return;
        think("Rabbit");
    } while (meadow.ready && alive);
}

void Rabbit::eat() {
    Grass* grass_to_eat = drawGrass();
    grass_to_eat->request();

    std::lock_guard<std::mutex> lock(grass_to_eat->mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    thread_local std::uniform_int_distribution<> wait(2, 4);
    if (alive) {
        Utils::threadSafeCout("Rabbit " + std::to_string(id) + " is eating grass");
        for (int time = wait(random_generator); time > 0 ; --time) {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }

    grass_to_eat->done_eating();
}

void Rabbit::hide() {
    Rabbit_Hole* rabbit_hole = drawRabbitHole();
    rabbit_hole->request(id);

    std::lock_guard<std::mutex> lock(rabbit_hole->mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    thread_local std::uniform_int_distribution<> wait(2, 4);
    if (alive) {
        Utils::threadSafeCout("Rabbit " + std::to_string(id) + " is hiding");
        for (int time = wait(random_generator); time > 0 ; --time) {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }

    rabbit_hole->done_hiding(id);
}

void Rabbit::request() {
    thread_local std::uniform_int_distribution<> chance(1, 10);
    if (chance(random_generator) > 5) {
        hide();
    } else {
        Utils::threadSafeCout("Rabbit " + std::to_string(id) + " was eaten");
        alive = false;
    }
}

Grass* Rabbit::drawGrass() {
    thread_local std::uniform_int_distribution<> index(0, grass.size() - 1);
    return grass.at(index(random_generator));
}

Rabbit_Hole* Rabbit::drawRabbitHole() {
    thread_local std::uniform_int_distribution<> index(0, rabbit_holes.size() - 1);
    return rabbit_holes.at(index(random_generator));
}