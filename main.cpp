#include <iostream>
#include "Sun.h"
#include "Animals/Animal.h"

int main() {
    Meadow meadow;
    Sun *sun = new Sun(meadow);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    meadow.ready = true;
    meadow.synchronization.notify_all();

    std::this_thread::sleep_for(std::chrono::seconds(30));
    meadow.ready = false;

    return 0;
}