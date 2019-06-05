#include "Rabbit.h"

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

    std::cout << id << " is eating grass" << std::endl;
    for (int time = wait(random_generator); time > 0 ; --time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    grass.done_eating();
}

Rabbit::Rabbit(int id, Meadow &meadow, Grass &grass) : Animal(id, meadow), grass(grass) {}
