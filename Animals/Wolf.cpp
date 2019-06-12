#include "Wolf.h"

Wolf::Wolf(int id, std::vector<Rabbit*> &rabbits, Meadow &meadow) : Animal(id, meadow), rabbits(rabbits) {}

void Wolf::live() {
    meadow.synchronization.wait();

    do {
        eat();
        drink();
        think();
    } while (meadow.ready);
}

void Wolf::eat() {
    /* rabbit.requestFood, wolf has a chance (random) to catch the requested rabbit. If it didn't then
     * it goes to the next step. Rabbits try to run to the rabbit hole when they are hunted buy wolves
     * (they have a chance to escape, random - rather small). Rabbits also try to reproduce (takes two
     * to create a new one).
     * */
    Rabbit* rabbit = drawRabbit();
    rabbit->request();

    std::lock_guard<std::mutex> lock(rabbit->mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    thread_local std::uniform_int_distribution<> wait(2, 4);

    Utils::threadSafeCout("Wolf " + std::to_string(id) + " is hunting rabbit");
    for (int time = wait(random_generator); time > 0 ; --time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

Rabbit* Wolf::drawRabbit() {
    thread_local std::uniform_int_distribution<> index(0, rabbits.size() - 1);
    return rabbits.at(index(random_generator));
}
