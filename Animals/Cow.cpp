#include "Cow.h"

Cow::Cow(int id, std::vector<Grass*> &grass, Meadow &meadow) : Animal(id, meadow), grass(grass) {}

void Cow::live() {
    meadow.synchronization.wait();

    do {
        eat();
        drink();
        think();
    } while (meadow.ready);
}

void Cow::eat() {
    Grass* grass_to_eat = drawGrass();
    grass_to_eat->request();

    std::lock_guard<std::mutex> lock(grass_to_eat->mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    thread_local std::uniform_int_distribution<> wait(2, 4);

    Utils::threadSafeCout("Cow " + std::to_string(id) + " is eating grass");
    for (int time = wait(random_generator); time > 0 ; --time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    grass_to_eat->done_eating();
}

Grass* Cow::drawGrass() {
    thread_local std::uniform_int_distribution<> index(0, grass.size() - 1);
    return grass.at(index(random_generator));
}
