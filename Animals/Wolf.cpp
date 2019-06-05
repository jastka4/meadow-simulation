#include "Wolf.h"

Wolf::Wolf(int id, Rabbit &rabbit, Meadow &meadow) : Animal(id, meadow), rabbit(rabbit) {}

void Wolf::live() {
    meadow.synchronization.wait();

    do {
        hunt();
        drink();
        think();
    } while (meadow.ready);
}

void Wolf::eat() {
    /* rabbit.requestFood, wolf has a chance (random) to catch the requested rabbit. If it didn't then
     * it goes to the next step. Rabbits try to run to the rabbit hole when they are hunted buy wolfs
     * (they have a chance to escape, random - rather small). Rabbits also try to reproduce (takes two
     * to create a new one).
     * */
    rabbit.request();

    std::lock_guard<std::mutex> lock(rabbit.mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    thread_local std::uniform_int_distribution<> wait(2, 4);

    Utils::threadSafeCout("Wolf " + std::to_string(id) + " is hunting rabbit");
    for (int time = wait(random_generator); time > 0 ; --time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void Wolf::hunt() {
    eat();
//    Utils::threadSafeCout("Wolf " + std::to_string(id) + " is not eating - rabbit escaped");
}
