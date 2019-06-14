#include "Rabbit.h"

Rabbit::Rabbit(int id, std::vector<Grass*> &grass, Meadow &meadow, std::vector<Rabbit_Hole*> &rabbit_holes)
        : Animal(id, meadow), grass(grass), rabbit_holes(rabbit_holes) {}

void Rabbit::live() {
    meadow.synchronization.setSleep(true);
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
    std::lock_guard<std::mutex> lock(grass_to_eat->mutex);
    grass_to_eat->request();

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    thread_local std::uniform_int_distribution<> wait(10, 14);

    if (alive) {
        status = "eating  ";
        Utils::thread_safe_cout("Rabbit " + std::to_string(id) + " is eating grass");
        int time = wait(random_generator);
        for (int i = time, counter = 0; i > 0; --i) {
            progress = Utils::get_percentage(counter, time);
            counter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        progress = 0;
    }

    grass_to_eat->done_eating();
}

void Rabbit::hide() {
    Rabbit_Hole* rabbit_hole = drawRabbitHole();
//    std::lock_guard<std::mutex> lock(rabbit_hole->mutex); // TODO - ask about mutex here vs in methods
    rabbit_hole->request(id);

    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    thread_local std::uniform_int_distribution<> wait(10, 14);
    if (alive) {
        status = "hiding  ";
        Utils::thread_safe_cout("Rabbit " + std::to_string(id) + " is hiding");
        int time = wait(random_generator);
        for (int i = time, counter = 0; i > 0; --i) {
            progress = Utils::get_percentage(counter, time);
            counter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        progress = 0;
    }

    rabbit_hole->done_hiding(id);
}

void Rabbit::request() {
    thread_local std::uniform_int_distribution<> chance(1, 10);
    if (chance(random_generator) > 5) {
        hide();
    } else {
        Utils::thread_safe_cout("Rabbit " + std::to_string(id) + " was eaten");
        alive = false;
        status = "eaten    ";
    }
}

Grass* Rabbit::drawGrass() {
    thread_local std::uniform_int_distribution<> index(0, grass.size() - 1);
    Grass* grass_to_eat;
    do {
        status = "waiting ";
        std::lock_guard<std::mutex> lock(mutex);
        grass_to_eat = grass.at(index(random_generator));
    } while (!grass_to_eat->getReady());
    return grass_to_eat;
}

Rabbit_Hole* Rabbit::drawRabbitHole() {
    thread_local std::uniform_int_distribution<> index(0, rabbit_holes.size() - 1);
    return rabbit_holes.at(index(random_generator));
}