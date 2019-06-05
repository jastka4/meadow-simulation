#include "Rabbit.h"

Rabbit::Rabbit(int id, Grass &grass, Meadow &meadow, Rabbit_Hole &rabbit_hole)
        : Animal(id, meadow), grass(grass), rabbit_hole(rabbit_hole) {}

void Rabbit::live() {
    meadow.synchronization.wait();

    do {
        eat();
        drink();
        think();
    } while (meadow.ready);
}

void Rabbit::eat() {
    grass.request();

    std::lock_guard<std::mutex> lock(grass.mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    thread_local std::uniform_int_distribution<> wait(2, 4);

    Utils::threadSafeCout("Rabbit " + std::to_string(id) + " is eating grass");
    for (int time = wait(random_generator); time > 0 ; --time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    grass.done_eating();
}

void Rabbit::hide() {
    rabbit_hole.request(id);

    std::lock_guard<std::mutex> lock(rabbit_hole.mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    thread_local std::uniform_int_distribution<> wait(2, 4);

    Utils::threadSafeCout("Rabbit " + std::to_string(id) + " is hiding");
    for (int time = wait(random_generator); time > 0 ; --time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    rabbit_hole.done_hiding(id);
}

void Rabbit::request() {
    thread_local std::uniform_int_distribution<> chance(1, 10);
    if (chance(random_generator) > 5) {
        hide();
//        synchronization.wait();
    } else {
        Utils::threadSafeCout("Rabbit " + std::to_string(id) + " was eaten");
//        this->~Rabbit(); // die
    }
}
