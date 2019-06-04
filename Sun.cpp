#include <iostream>
#include "Sun.h"

Sun::Sun(Meadow &meadow) : meadow_thread(meadow), live_thread(&Sun::shine, this) {}

Sun::~Sun() {
    live_thread.join();
}

void Sun::day() {

    std::cout << "===== DAY =====" << std::endl;
    thread_local std::uniform_int_distribution<> wait(7, 13);

    for (int time = wait(random_generator); time > 0 ; --time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Sun::night() {
    thread_local std::uniform_int_distribution<> wait(11, 17);

    std::cout << "==== NIGHT ====" << std::endl;
    for (int time = wait(random_generator); time > 0 ; --time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Sun::shine() {
    meadow_thread.synchronization.wait();

    do {
        day();
        night();
    } while (meadow_thread.ready);

}
