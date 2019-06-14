#include "Wolf.h"

Wolf::Wolf(int id, std::vector<Rabbit*> &rabbits, Meadow &meadow, Sun &sun) : Animal(id, meadow), rabbits(rabbits), sun(sun) {}

void Wolf::live() {
    meadow.synchronization.setSleep(true);
    meadow.synchronization.wait();

    do {
        if (!sun.getIsDay()) {
            eat();
        }
        drink("Wolf");
        think("Wolf");
    } while (meadow.ready);
}

void Wolf::eat() {
    /* rabbit.requestFood, wolf has a chance (random) to catch the requested rabbit. If it didn't then
     * it goes to the next step. Rabbits try to run to the rabbit hole when they are hunted buy wolves
     * (they have a chance to escape, random - rather small). Rabbits also try to reproduce (takes two
     * to create a new one).
     * */
    Rabbit* rabbit = drawRabbit();
    std::lock_guard<std::mutex> lock(rabbit->mutex);
    rabbit->request();

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    thread_local std::uniform_int_distribution<> wait(10, 14);

    status = "hunting ";
    Utils::thread_safe_cout("Wolf " + std::to_string(id) + " is hunting rabbit");
    int time = wait(random_generator);
    for (int i = time, counter = 0; i > 0; --i) {
        progress = Utils::get_percentage(counter, time);
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    progress = 0;
}

Rabbit* Wolf::drawRabbit() {
    thread_local std::uniform_int_distribution<> index(0, rabbits.size() - 1);
    Rabbit* rabbit;
    do {
        std::lock_guard<std::mutex> lock(mutex);
        rabbit = rabbits.at(index(random_generator));
    } while (!rabbit->isAlive());
    return rabbit;
}
