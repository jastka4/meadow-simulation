#include <iostream>
#include "Sun.h"
#include "Utils/Utils.h"

Sun::Sun(Meadow &meadow) : meadow(meadow), live_thread(&Sun::shine, this), is_day(true), progress(0) {}

Sun::~Sun() {
    if (live_thread.joinable()) {
        live_thread.join();
    }
}

void Sun::day() {

    Utils::thread_safe_cout("===== DAY =====");
    is_day = true;

    thread_local std::uniform_int_distribution<> wait(10, 24);
    int time = wait(random_generator);
    for (int i = time, counter = 0; i > 0; --i) {
        progress = Utils::get_percentage(counter, time);
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    progress = 0;
}

void Sun::night() {
    thread_local std::uniform_int_distribution<> wait(10, 24);
    is_day = false;

    Utils::thread_safe_cout("==== NIGHT ====");
    int time = wait(random_generator);
    for (int i = time, counter = 0; i > 0; --i) {
        progress = Utils::get_percentage(counter, time);
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    progress = 0;
}

void Sun::shine() {
    meadow.synchronization.setSleep(true);
    meadow.synchronization.wait();

    do {
        day();
        night();
    } while (meadow.ready);

}

const std::atomic<bool> &Sun::getIsDay() const {
    return is_day;
}

const std::atomic_int &Sun::getProgress() const {
    return progress;
}

