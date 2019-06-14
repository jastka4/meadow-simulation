#include "Cow.h"

Cow::Cow(int id, std::vector<Grass*> &grass, Meadow &meadow) : Animal(id, meadow), grass(grass) {}

void Cow::live() {
    meadow.synchronization.setSleep(true);
    meadow.synchronization.wait();

    do {
        eat();
        drink("Cow");
        think("Cow");
    } while (meadow.ready);
}

void Cow::eat() {
    Grass* grass_to_eat = drawGrass();
    std::lock_guard<std::mutex> lock(grass_to_eat->mutex);
    grass_to_eat->request();

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    thread_local std::uniform_int_distribution<> wait(10, 14);

    status = "eating  ";
    Utils::thread_safe_cout("Cow " + std::to_string(id) + " is eating grass");
    int time = wait(random_generator);
    for (int i = time, counter = 0; i > 0; --i) {
        progress = Utils::get_percentage(counter, time);
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    progress = 0;

    grass_to_eat->done_eating();
}

Grass* Cow::drawGrass() {
    thread_local std::uniform_int_distribution<> index(0, grass.size() - 1);
    Grass* grass_to_eat;
    do {
        status = "waiting ";
        std::lock_guard<std::mutex> lock(mutex);
        grass_to_eat = grass.at(index(random_generator)); // TODO - not sure how to use mutex here
    } while (!grass_to_eat->getReady());
    return grass_to_eat;
}
