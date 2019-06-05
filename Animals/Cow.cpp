#include "Cow.h"

Cow::Cow(int id, Grass &grass, Meadow &meadow) : Animal(id, meadow), grass(grass) {}

void Cow::live() {
    meadow.synchronization.wait();

    do {
        eat();
        drink();
        think();
    } while (meadow.ready);
}

void Cow::eat() {
    grass.request();

    std::lock_guard<std::mutex> lock(grass.mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    thread_local std::uniform_int_distribution<> wait(2, 4);

    Utils::threadSafeCout("Cow " + std::to_string(id) + " is eating grass");
    for (int time = wait(random_generator); time > 0 ; --time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    grass.done_eating();
}
